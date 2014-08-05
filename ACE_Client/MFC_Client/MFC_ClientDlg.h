
// MFC_ClientDlg.h : 头文件
//

#pragma once


// CMFC_ClientDlg 对话框
class CMFC_ClientDlg : public CDialogEx
{
// 构造
public:
	CMFC_ClientDlg(CWnd* pParent = NULL);	// 标准构造函数
	void sendClientMessage(char* msg);

// 对话框数据
	enum { IDD = IDD_MFC_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit1();
	CString m_send;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton3();
};
