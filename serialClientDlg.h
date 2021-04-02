// serialClientDlg.h : header file
//

#if !defined(AFX_SERIALCLIENTDLG_H__4B73FEA8_7C29_4E9C_B463_C97630A330D5__INCLUDED_)
#define AFX_SERIALCLIENTDLG_H__4B73FEA8_7C29_4E9C_B463_C97630A330D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSerialClientDlg dialog

class CSerialClientDlg : public CDialog
{
// Construction
public:
	CSerialClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSerialClientDlg)
	enum { IDD = IDD_SERIALCLIENT_DIALOG };
	CString	m_output;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSerialClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bExit;
	static DWORD WINAPI LoginThread(PVOID param);
	Status CheckStatus();
	CString GetLastLine(CString &src);
public:
	void Exit();
	void Output(LPCTSTR text);
	void RunPutty();
public:
	Process m_plink;
	CString m_username;
	CString m_password;
	CString m_com;
	CString m_plinkArg;
	void GetCommandLine();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALCLIENTDLG_H__4B73FEA8_7C29_4E9C_B463_C97630A330D5__INCLUDED_)
