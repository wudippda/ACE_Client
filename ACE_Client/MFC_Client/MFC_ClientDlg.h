
// MFC_ClientDlg.h : ͷ�ļ�
//

#pragma once


// CMFC_ClientDlg �Ի���
class CMFC_ClientDlg : public CDialogEx
{
// ����
public:
	CMFC_ClientDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void sendClientMessage(char* msg);

// �Ի�������
	enum { IDD = IDD_MFC_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
