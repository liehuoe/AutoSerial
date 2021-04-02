// serialClient.h : main header file for the SERIALCLIENT application
//

#if !defined(AFX_SERIALCLIENT_H__89FA5AB2_328F_4663_9829_4CBD5321D22A__INCLUDED_)
#define AFX_SERIALCLIENT_H__89FA5AB2_328F_4663_9829_4CBD5321D22A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSerialClientApp:
// See serialClient.cpp for the implementation of this class
//

class CSerialClientApp : public CWinApp
{
public:
	CSerialClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSerialClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALCLIENT_H__89FA5AB2_328F_4663_9829_4CBD5321D22A__INCLUDED_)
