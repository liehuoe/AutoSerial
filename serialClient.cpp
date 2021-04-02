// serialClient.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "serialClient.h"
#include "serialClientDlg.h"
#include "ComDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerialClientApp

BEGIN_MESSAGE_MAP(CSerialClientApp, CWinApp)
	//{{AFX_MSG_MAP(CSerialClientApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialClientApp construction

CSerialClientApp::CSerialClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSerialClientApp object

CSerialClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSerialClientApp initialization

static void InitWorkDir()
{
    char path[256];

    GetModuleFileName(NULL, path, sizeof(path));
    {
        char *p;
        p = strrchr(path, '\\');
        if (p != NULL) { *p = '\0'; }
    }
    SetCurrentDirectory(path);
}

BOOL CSerialClientApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	InitWorkDir();

	CSerialClientDlg dlg;
	dlg.GetCommandLine();
	if (dlg.m_com.IsEmpty())
	{
		CComDialog comDlg;
		m_pMainWnd = &comDlg;
		int ret = comDlg.DoModal();
		if (ret != IDOK)
		{
			return FALSE;
		}
		dlg.m_com = comDlg.m_com;
		dlg.m_plinkArg += " " + dlg.m_com;
	}
	if (dlg.m_username.IsEmpty() && dlg.m_password.IsEmpty())
	{
		dlg.RunPutty();
		return FALSE;
	}
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
