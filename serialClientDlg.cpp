// serialClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "serialClient.h"
#include "serialClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerialClientDlg dialog

CSerialClientDlg::CSerialClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSerialClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSerialClientDlg)
	m_output = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bExit = FALSE;
}

void CSerialClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSerialClientDlg)
	DDX_Text(pDX, IDC_TXT_OUTPUT, m_output);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSerialClientDlg, CDialog)
	//{{AFX_MSG_MAP(CSerialClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialClientDlg message handlers

BOOL CSerialClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// auto login
	Output("等待串口响应...\r\n");
	AfxBeginThread((AFX_THREADPROC)LoginThread, (PVOID)this);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSerialClientDlg::OnPaint()
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSerialClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSerialClientDlg::OnOK()
{
}

void CSerialClientDlg::OnClose()
{
	int res = MessageBox("确定要关闭串口登录？", "系统信息", MB_YESNO);
	if (res == IDYES)
	{
		m_bExit = TRUE;
	}

	CDialog::OnClose();
}

void CSerialClientDlg::OnCancel()
{
	if (!m_bExit) { return; }
	m_plink.Release();
	CDialog::OnCancel();
}

void CSerialClientDlg::Exit()
{
	m_bExit = TRUE;
	OnCancel();
}

void CSerialClientDlg::Output(LPCTSTR text)
{
	CEdit *pItem = (CEdit*)GetDlgItem(IDC_TXT_OUTPUT);
	int len = pItem->GetWindowTextLength();
	if (len > 1024 * 1024)
	{
		m_output = "";
		UpdateData(FALSE);
	}
	else
	{
		pItem->SetSel(len, len);
		pItem->ReplaceSel(text);
		UpdateData(TRUE);
	}
}

// -serial -sercfg 115200,8,n,1,X COM5 -uusername -ppassword
void CSerialClientDlg::GetCommandLine()
{
	for (int i = 1; i < __argc; ++i)
	{
		LPCSTR arg = __argv[i];
		if (strlen(arg) >= 2)
		{
			if (arg[0] == '-' && arg[1] == 'u')
			{
				m_username = arg + 2;
				continue;
			}
			else if (arg[0] == '-' && arg[1] == 'p')
			{
				m_password = arg + 2;
				continue;
			}
			else if (arg[0] == '-' && arg[1] == 'c')
			{
				m_com = arg + 2;
				continue;
			}
		}
		m_plinkArg += ' ';
		m_plinkArg += arg;
	}
}

void CSerialClientDlg::RunPutty()
{
	m_plink.Kill();
	m_plink.IsLive(2000);
	// ShellExecute(m_hWnd, "open", PUTTY, m_plinkArg, NULL, SW_SHOW);
	STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);
    if (CreateProcess(PUTTY, (LPSTR)(LPCSTR)m_plinkArg, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
    }
	else
	{
		MessageBox("启动串口程序出错", "系统信息");
	}
	ExitProcess(0);
}

DWORD WINAPI CSerialClientDlg::LoginThread(PVOID param)
{
	CSerialClientDlg *pDlg;

	pDlg = (CSerialClientDlg*)param;
	Process &plink = pDlg->m_plink;
    {
        if (!plink.Create((LPSTR)(LPCSTR)(PLINK" " + pDlg->m_plinkArg)))
		{
			pDlg->MessageBox("打开程序出错", "系统信息");
			pDlg->Exit();
			return -1;
		}
    }
	Status stat = UNKNOWN;
	while (plink.IsLive())
    {
		std::string text;

		Sleep(1000);

        if (!plink.Peek())
		{
			plink.Write("\r\n");
		}
		plink.Read(text);
		pDlg->Output(text.c_str());

		stat = pDlg->CheckStatus();
		if (stat == LOGIN)
		{
			pDlg->RunPutty();
		}
		else if (stat == USERNAME)
		{
			plink.Write(pDlg->m_username + "\r\n");
		}
		else if (stat == PASSWORD)
		{
			plink.Write(pDlg->m_password + "\r\n");
		}
    }

    return 0;
}

CString CSerialClientDlg::GetLastLine(CString &src)
{
	CString dst;
	int pos = src.ReverseFind('\n');
	if (pos == -1)
	{
		dst = src;
		src = "";
	}
	else
	{
		dst = src.Right(src.GetLength() - pos + 1);
		if (pos > 0)
		{
			src = src.Left(pos);
			if (src[pos - 1] == '\r')
			{
				src.Delete(pos - 1);
			}
		}
		else
		{
			src = "";
		}
	}
	return dst;
}

Status CSerialClientDlg::CheckStatus()
{
	CString data = m_output;
	// split lines
	CString line1 = GetLastLine(data);
	line1.TrimRight();
	char c = line1[line1.GetLength() - 1];
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ':')
	{
		while((c < 'a' || c > 'z') && (c < 'A' || c > 'Z'))
		{
			line1.Delete(line1.GetLength() - 1);
			if (line1.GetLength() == 0) { break; }
			c = line1[line1.GetLength() - 1];
		}

		LPCSTR token;
		int len;
		// username
		token = "user";
		len = strlen(token);
		if (line1.GetLength() >= len)
		{
			CString dst = line1.Right(len);
			dst.MakeLower();
			if (dst == token)
			{
				return USERNAME;
			}
		}
		token = "username";
		len = strlen(token);
		if (line1.GetLength() >= len)
		{
			CString dst = line1.Right(len);
			dst.MakeLower();
			if (dst == token)
			{
				return USERNAME;
			}
		}
		token = "login";
		len = strlen(token);
		if (line1.GetLength() >= len)
		{
			CString dst = line1.Right(len);
			dst.MakeLower();
			if (dst == token)
			{
				return USERNAME;
			}
		}
		token = "login as";
		len = strlen(token);
		if (line1.GetLength() >= len)
		{
			CString dst = line1.Right(len);
			dst.MakeLower();
			if (dst == token)
			{
				return USERNAME;
			}
		}
		// password
		token = "password";
		len = strlen(token);
		if (line1.GetLength() >= len)
		{
			CString dst = line1.Right(len);
			dst.MakeLower();
			if (dst == token)
			{
				return PASSWORD;
			}
		}
		token = "passwords";
		len = strlen(token);
		if (line1.GetLength() >= len)
		{
			CString dst = line1.Right(len);
			dst.MakeLower();
			if (dst == token)
			{
				return PASSWORD;
			}
		}
		token = "pw";
		len = strlen(token);
		if (line1.GetLength() >= len)
		{
			CString dst = line1.Right(len);
			dst.MakeLower();
			if (dst == token)
			{
				return PASSWORD;
			}
		}
	}
	else if (!line1.IsEmpty())
	{
		// login status
		CString line2 = GetLastLine(data);
		line2.TrimRight();
		if (line1 == line2)
		{
			return LOGIN;
		}
	}
	return UNKNOWN;
}
