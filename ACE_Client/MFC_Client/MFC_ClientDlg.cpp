
// MFC_ClientDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "MFC_Client.h"
#include "MFC_ClientDlg.h"
#include "afxdialogex.h"
#include "ACE_headers.h"
#include "ServerConnector.h"
#include <afxpriv.h>
#include "CanvasFrame.h"
#include "DVE_Client.h"
#include "PARA_DEFINE.h"
#include "MessageConstructor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CanvasFrame *pdlg;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_ClientDlg 对话框




CMFC_ClientDlg::CMFC_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_ClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_send = _T("");
}

void CMFC_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_send);
	DDV_MaxChars(pDX, m_send, 128);
}

BEGIN_MESSAGE_MAP(CMFC_ClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFC_ClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC_ClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC_ClientDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CMFC_ClientDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDCANCEL, &CMFC_ClientDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC_ClientDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFC_ClientDlg 消息处理程序

BOOL CMFC_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC_ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC_ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFC_ClientDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CMFC_ClientDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	ACE::init();

	DVE_Client client;
    //listen on specific port
	ACE_INET_Addr addr(REMOTE_HOST_PORT,REMOTE_HOST_IP);
	client.connector.open();
	if(client.connector.connect(addr) == -1)
	{
		AfxMessageBox(_T("Connectin Failed!"));  
	}
	else
	{
		AfxMessageBox(_T("Connection Successful!"));
		
		//use Sender handler to send message
		client.connector.getHandler()->wirteMessage(COM::CONNECT_SERVER);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
		GetDlgItem(IDC_STATICMessage)->SetWindowText(_T("Connected"));
	}

	if (client.acceptor.open(ACE_INET_Addr(LOCAL_LISTEN_PORT)) == -1)  
		AfxMessageBox(_T("Port Listening Failed!")); 
	else
	{
		AfxMessageBox(_T("Port Listening Successful!")); 
	}
    //Wait 4 client Connection
    ACE_Proactor::instance()->proactor_run_event_loop();
	//Release dll resource
	ACE::fini();
   /* if(ServerConnector::getInstance()->connect(REMOTE_HOST_PORT,REMOTE_HOST_IP) == 0)  
    {  
        AfxMessageBox(_T("Connection Successful!"));
    }
	else
	{  
        AfxMessageBox(_T("Connectin Failed!"));  
    }*/
}

void CMFC_ClientDlg::sendClientMessage(char* msg)
{
	//ServerConnector::getInstance()->sendMessage(msg);
}


void CMFC_ClientDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(true);
	//USES_CONVERSION;
	//LPSTR str = T2A(m_send);
	//Client::getInstance()->sendMessage("s");
	GetDlgItem(IDC_EDIT1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);

	pdlg = new CanvasFrame();
	pdlg->Create(IDD_DIALOG1,this);
	pdlg->ShowWindow(SW_SHOW); 
	pdlg->Init();
	//pdlg->DrawClient();
	pdlg->setParent(this);
	//Client::getInstance()->holdWindowInstance(pdlg);
}


void CMFC_ClientDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFC_ClientDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//ServerConnector::getInstance()->close();  
	ACE::fini();
	CDialog::OnCancel();  
}


void CMFC_ClientDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(true);
	//char* chat_msg = (LPSTR)(LPCTSTR)m_send;
	//char buf[128];
	//if(chat_msg != "")
	//{
	//	buf[0] = CHAT;
	//	buf[1] = '\0';
	//	strcat(buf,chat_msg);
	//}
	//ServerConnector::getInstance()->sendMessage(buf);
	////delete chat_msg;
	//GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
}
