#pragma once
#include "Resource.h"
#include "stdafx.h"
#include "NALParse.h"
#include "h264_analyze.h"
#include <vector>

using std::vector;

class CSpecialVH264Dlg :public CDialogEx
{
public:
	CSpecialVH264Dlg(CWnd* pPareng = NULL);

	// 对话框数据
	enum {IDD = IDD_SPECIAL_V_H264};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMFCEditBrowseCtrl m_vh264inputurl;
	CListCtrl m_vh264nallist;
	CButton m_vh264nallistmaxnum;
	afx_msg void OnBnClickedVH264InputurlOpen();
	void OnCustomdrawMyList(NMHDR* pNMHDR, LRESULT* pResult);
	int nl_index;
	int AppendNLInfo(int nal_reference_idc, int nal_unit_type, int len, int data_length, int data_offset);
	char fileurl[MAX_URL_LENGTH];
	void SystemClear();
	afx_msg void OnBnClickedVH264About();
	CEdit m_vh264nalinfo;
	typedef struct NALInfo {
		int data_offset;
		int data_length;
	}NALInfo;
	vector<NALInfo> n1_infovector;
	afx_msg void OnDropFiles(HDROP hDropInfo);

	CString text;
	CComboBox m_vh264lang;
	afx_msg void OnSelchangeVH264Lang();
	afx_msg void OnItemchangedVH264Nallist(NMHDR* pNMHDR, LRESULT* pResult);


};
