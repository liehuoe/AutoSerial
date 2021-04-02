// ComDialog.cpp : implementation file
//

#include "stdafx.h"
#include "serialClient.h"
#include "ComDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComDialog dialog


CComDialog::CComDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CComDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bExit = FALSE;
}


void CComDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComDialog, CDialog)
	//{{AFX_MSG_MAP(CComDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComDialog message handlers

BOOL CComDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	InitCom();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CComDialog::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CComDialog::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CComDialog::OnOK()
{
	CComboBox* pItem = (CComboBox*)GetDlgItem(IDC_CMB_COM);
	pItem->GetWindowText(m_com);
	if (m_com.IsEmpty())
	{
		MessageBox("请选择一个COM口进行登录", "系统信息");
		return;
	}
	CDialog::OnOK();
}

void CComDialog::OnClose() 
{
	int res = MessageBox("确定要取消串口登录？", "系统信息", MB_YESNO);
	if (res == IDYES)
	{
		m_bExit = TRUE;
	}
	
	OnCancel();
}

void CComDialog::OnCancel()
{
	if (!m_bExit) { return; }
	CDialog::OnCancel();
}

void CComDialog::OnBtnExit() 
{
	OnClose();
}

void CComDialog::InitCom()
{
	HKEY hKey;
	LONG ret;
	
	ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Hardware\\DeviceMap\\SerialComm", NULL, KEY_READ, &hKey);
	if (ret != ERROR_SUCCESS ) { return; }

	CComboBox* pItem = (CComboBox*)GetDlgItem(IDC_CMB_COM);

	char portName[256], comName[256];
	DWORD dwPort, dwCom;
	int i = 0;
	do
	{
		dwPort = dwCom = 256;
		ret = RegEnumValue(hKey, i, portName, &dwPort, NULL, NULL, (PUCHAR)comName, &dwCom);
		if (ret == ERROR_NO_MORE_ITEMS)
		{
			break;
		}
		pItem->AddString(comName);
	} while (++i);

	RegCloseKey(hKey);
}
