#pragma once
#include "stdafx.h"

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"

class CSpecialVH264App :public CWinApp
{
public:
	CSpecialVH264App();
public:
	virtual BOOL InitInstance();
	void LoadLanguage();
	DECLARE_MESSAGE_MAP()
};

extern CSpecialVH264App theApp;

