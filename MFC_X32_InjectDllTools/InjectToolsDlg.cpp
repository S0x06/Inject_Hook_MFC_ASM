// InjectToolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InjectTools.h"
#include "InjectToolsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInjectToolsDlg dialog

CInjectToolsDlg::CInjectToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInjectToolsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInjectToolsDlg)
	m_strDllPath = _T("");
	m_strDstName = _T("ɨ��");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    m_bIsGetPath = FALSE;
}

void CInjectToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInjectToolsDlg)
	DDX_Control(pDX, IDC_BTN_INJECT, m_InjectCtl);
	DDX_Control(pDX, IDC_BTN_GETDLLPATH, m_BtnGetDllPathCtl);
	DDX_Control(pDX, IDC_EDIT_DLLPATH, m_DllPathCtl);
	DDX_Text(pDX, IDC_EDIT_DLLPATH, m_strDllPath);
	DDX_Text(pDX, IDC_EDIT_DST_NAME, m_strDstName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInjectToolsDlg, CDialog)
	//{{AFX_MSG_MAP(CInjectToolsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_GETDLLPATH, OnBtnGetdllpath)
	ON_BN_CLICKED(IDC_BTN_INJECT, OnBtnInject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInjectToolsDlg message handlers

BOOL CInjectToolsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInjectToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInjectToolsDlg::OnPaint() 
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
HCURSOR CInjectToolsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInjectToolsDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CInjectToolsDlg::OnBtnGetdllpath() 
{
	m_strDllPath = TEXT("");
    m_bIsGetPath = TRUE;
    
	CFileDialog FileDlg(TRUE);
    if(FileDlg.DoModal() == IDOK)
    {
        m_strDllPath = FileDlg.GetPathName();
        if(m_strDllPath.IsEmpty())
        {
            AfxMessageBox(TEXT("��ѡ��һ����ע���DLL��"));
            m_bIsGetPath = FALSE;
            return;
        }
        UpdateData(FALSE);
        m_DllPathCtl.EnableWindow(FALSE);
        m_BtnGetDllPathCtl.EnableWindow(FALSE);
        m_InjectCtl.EnableWindow(TRUE);
    }
}

void CInjectToolsDlg::OnBtnInject() 
{

    //1 ���Ҵ���
    //2 ת��PID
    //3 �򿪽���
    //4 Զ������ռ�
    //5 д������
    //6 ��ȡLoadLibrary
    //7 Զ��ִ���߳�
    //8 �ȴ�Զ���߳̽�������ȡ������
    //9 �ͷſռ�

    DWORD dwPid = 0;
    if(!FindDlgAndGetPID(dwPid))
    {
        //check
        return;
    }

    LPVOID pBuf = NULL;
    HANDLE hProcess = NULL;
    if(!OpenProcessAndAllocBuf(dwPid, hProcess, pBuf))
    {
        return;
    }

    HANDLE hThread = INVALID_HANDLE_VALUE;

    if(!WriteDataAndStartThread(hThread, hProcess, pBuf))
    {
        return;
    }
    
    WaitForSingleObject(hThread, INFINITE);
    DWORD dwExitCode = 0;
    GetExitCodeThread(hThread, &dwExitCode);
    
    //�ͷſռ�
    if(!VirtualFreeEx(hProcess, pBuf, 0, MEM_RELEASE))
    {
        AfxMessageBox(TEXT("OnBtnInject���ͷ�Զ���ڴ�ʧ�ܣ�"));
        return;
    }
}

BOOL CInjectToolsDlg::FindDlgAndGetPID(DWORD& dwOutPid)
{
    HWND hWnd = ::FindWindow(NULL, m_strDstName);
    if(hWnd == NULL)
    {
        AfxMessageBox(TEXT("FindDlgAndGetPID�����Ҵ���ʧ�ܣ�"));
        return FALSE;
    }
    
    DWORD dwRet = GetWindowThreadProcessId(hWnd, &dwOutPid);

    return TRUE;
}

BOOL CInjectToolsDlg::OpenProcessAndAllocBuf(DWORD dwPid, HANDLE& hOutProcess, LPVOID& pOutBuf)
{
    hOutProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
    if (hOutProcess == NULL)
    {
        AfxMessageBox(TEXT("OpenProcessAndAllocBuf���򿪽���ʧ�ܣ�"));
        return FALSE;
    }

    pOutBuf = VirtualAllocEx(hOutProcess, NULL, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if(pOutBuf == NULL)
    {
        AfxMessageBox(TEXT("OpenProcessAndAllocBuf������Զ�̿ռ�ʧ�ܣ�"));
        return FALSE;
    }
    return TRUE;
}

typedef
HMODULE
(WINAPI
 *PFN_LoadLibraryA)(
 LPCSTR lpLibFileName
    );

BOOL CInjectToolsDlg::WriteDataAndStartThread(HANDLE& hOutThread, HANDLE& hProcess, LPVOID& lpBuf)
{
    DWORD dwRetByte = 0;
    BOOL bRet = WriteProcessMemory(hProcess, 
                                   lpBuf,
                                   (LPVOID)(LPCTSTR)m_strDllPath,
                                   m_strDllPath.GetLength() + 1,
                                   &dwRetByte);
    if(!bRet)
    {
        AfxMessageBox(TEXT("WriteDataAndStartThread��д��Զ���ڴ�ʧ�ܣ�"));
        return FALSE;
    }
    if(dwRetByte != (DWORD)(m_strDllPath.GetLength() + 1))
    {
        AfxMessageBox(TEXT("WriteDataAndStartThread��·��д�벻������"));
        return FALSE;
    }

    PFN_LoadLibraryA pfn_LoadLibraryA = (PFN_LoadLibraryA)GetProcAddress(LoadLibrary(TEXT("kernel32.dll")), TEXT("LoadLibraryA"));
    if(pfn_LoadLibraryA == NULL)
    {
        AfxMessageBox(TEXT("WriteDataAndStartThread����ȡLoadLibraryʧ�ܣ�"));
        return FALSE;
    }

    hOutThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pfn_LoadLibraryA, lpBuf, 0, NULL);
    if(hOutThread == NULL)
    {
        AfxMessageBox(TEXT("WriteDataAndStartThread������Զ���߳�ʧ�ܣ�"));
        return FALSE;
    }

    return TRUE;
}
