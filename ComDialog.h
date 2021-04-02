#if !defined(AFX_COMDIALOG_H__E52D2359_D4C9_4D41_9588_44623731985A__INCLUDED_)
#define AFX_COMDIALOG_H__E52D2359_D4C9_4D41_9588_44623731985A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComDialog dialog

class CComDialog : public CDialog
{
// Construction
public:
	CComDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CComDialog)
	enum { IDD = IDD_COM_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CComDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bExit;
	void InitCom();
public:
	CString m_com;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMDIALOG_H__E52D2359_D4C9_4D41_9588_44623731985A__INCLUDED_)
