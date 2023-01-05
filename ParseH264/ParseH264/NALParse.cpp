#include "stdafx.h"
#include "SpecialVH264.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "NALParse.h"

typedef struct 
{
	int startcodeprefix_len;
	unsigned len;
	unsigned max_size;
	int forbidden_bit;
	int nal_reference_idc;
	int nal_unit_type;
	char* buf;
	unsigned short lost_packets;
	int data_offset;
}NALU_t;

FILE* bits = NULL;
static int FindStartCode2(unsigned char* Buf)
{
	if (Buf[0] != 0 || Buf[1] != 0 || Buf[2] != 1)
		return 0;
	else
		return 1;
}

static int FindStartCode3(unsigned char* Buf)
{
	if (Buf[0] != 0 || Buf[1] != 0 || Buf[2] != 0 || Buf[3]!=1)
		return 0;
	else
		return 1;
}

static int info2 = 0, info3 = 0;
CSpecialVH264Dlg* dlg;

// 这个函数输入一个 NAL 结构体，主要功能为得到一个完整的 NALU 并保存在 NALU_t 的 buf 中，获取长度，填充F,IDC,TYPE 位
// 并且返回两个开始字符之间间隔的字节数，即包含有前缀的 NALU 的长度
int GetAnnexbNALU(NALU_t* nalu)
{
	int pos = 0;
	int StartCodeFound, rewind;
	unsigned char* Buf;
	if ((Buf = (unsigned char*)calloc(nalu->max_size, sizeof(char))) == NULL)
	{
		printf("GetAnnexbNALU: Could not allocate Buf memory\n");
	}
	nalu->startcodeprefix_len = 3; // 初始化码流序列的开始字符为3个字节
	if (3 != fread(Buf, 1, 3, bits)) // 从码流中读取3个字节
	{
		free(Buf);
		return 0;
	}

	info2 = FindStartCode2(Buf);
	if (info2 != 1)
	{
		// 如果不是，在读一个字节
		if (1 != fread(Buf + 3, 1, 1, bits))
		{
			free(Buf);
			return 0;
		}
		info3 = FindStartCode3(Buf);
		if (info3 != 1)
		{
			free(Buf);
			return -1;
		}
		else
		{
			pos = 4;
			nalu->startcodeprefix_len = 4;
		}
	}
	else
	{
		pos = 3;
		nalu->startcodeprefix_len = 3;
	}

	StartCodeFound = 0;
	info2 = 0;
	info3 = 0;
	while (!StartCodeFound)
	{
		// 判断是否为文件尾
		if (feof(bits))
		{
			nalu->len = (pos - 1) - nalu->startcodeprefix_len;
			memcpy(nalu->buf, &Buf[nalu->startcodeprefix_len], nalu->len);
			nalu->forbidden_bit = nalu->buf[0] & 0x80;
			nalu->nal_reference_idc = nalu->buf[0] & 0x60;
			nalu->nal_unit_type = (nalu->buf[0]) & 0x1f;
			free(Buf);
			return pos - 1;
		}
		Buf[pos++] = fgetc(bits);
		info3 = FindStartCode3(&Buf[pos - 4]);
		if (info3 != 1)
			info2 = FindStartCode2(&Buf[pos - 3]);
		StartCodeFound = (info2 == 1 || info3 == 1);
	}

	rewind = (info3 == 1) ? -4 : -3;
	if (0 != fseek(bits, rewind, SEEK_CUR))
	{
		free(Buf);
		printf("GetAnnexbNALU: Cannot fseek in the bit stream file");
	}

	nalu->len = (pos + rewind) - nalu->startcodeprefix_len;
	memcpy(nalu->buf, &Buf[nalu->startcodeprefix_len], nalu->len);
	nalu->forbidden_bit = nalu->buf[0] & 0x80;
	nalu->nal_reference_idc = nalu->buf[0] & 0x60;
	nalu->nal_unit_type = (nalu->buf[0]) & 0x1f;
	free(Buf);

	return pos + rewind;
}

int h264_nal_parse(LPVOID lparam, char* fileurl)
{
	bits = fopen(fileurl, "r+b");
	if (bits == NULL)
	{
		AfxMessageBox(_T("Error open file"));
		return -1;
	}

	NALU_t* n;
	int buffersize = 800000;
	if ((n = (NALU_t*)calloc(1, sizeof(NALU_t))) == NULL)
	{
		AfxMessageBox(_T("Error AllocNALU: n"));
		return -1;
	}
	n->max_size = buffersize;
	if ((n->buf = (char*)calloc(buffersize, sizeof(char))) = NULL)
	{
		free(n);
		AfxMessageBox(_T("Error AllocNALU: n->buf"));
		return -1;
	}

	int data_offset = 0;
	dlg = (CSpecialVH264Dlg*)lparam;
	int nal_num = 0;

	while (!feof(bits))
	{
		int data_length;
		data_length = GetAnnexbNALU(n);
		n->data_offset = data_offset;
		data_offset = data_offset + data_length;
		int nal_referece_idc = n->nal_reference_idc >> 5;
		dlg->AppendNLInfo(nal_referece_idc, n->nal_unit_type, n->len, n->len + n->startcodeprefix_len, n->data_offset);

		if (dlg->m_vh264nallistmaxnum.GetCheck() == 1 && nal_num > 5000)
		{
			break;
		}
		nal_num++;
	}
	if (n)
	{
		if (n->buf)
		{
			free(n->buf);
			n->buf = NULL;
		}
		free(n);
	}
	return 0;
}

























