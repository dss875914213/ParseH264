#pragma once
#include "stdafx.h"

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
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

