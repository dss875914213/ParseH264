#include "stdafx.h"
#include "SpecialVH264.h"
#include "SpecialVH264Dlg.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CSpecialVH264App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CSpecialVH264App::CSpecialVH264App()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

CSpecialVH264App theApp;

BOOL CSpecialVH264App::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	AfxEnableControlContainer();
	CShellManager* pShellManager = new CShellManager;

	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	LoadLanguage();

	CSpecialVH264Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{

	}
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}
	return FALSE;
}

void CSpecialVH264App::LoadLanguage()
{
	char conf_path[300] = { 0 };
	GetModuleFileNameA(NULL, (LPSTR)conf_path, 300);
	strrchr(conf_path, '\\')[0] = '\0';
	printf("%s", conf_path);
	strcat(conf_path, "\\configure.ini");
	char conf_val[300] = { 0 };
	if ((_access(conf_path, 0)) == -1)
	{
		return;
	}
	else
	{
		GetPrivateProfileStringA("Settings", "language", NULL, conf_val, 300, conf_path);
		if (strcmp(conf_val, "Chinese") == 0)
		{
			SetThreadUILanguage(MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_DEFAULT));
		}
		else if (strcmp(conf_val, "English") == 0)
		{
			SetThreadUILanguage(MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT));
		}
		return;
	}
}