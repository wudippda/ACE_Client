#pragma once
#include "resource.h"
#include "MFC_ClientDlg.h"

// CanvasFrame �Ի���

class CanvasFrame : public CDialogEx
{
	DECLARE_DYNAMIC(CanvasFrame)

public:
	
	// ��׼���캯��
	CanvasFrame(CWnd* pParent = NULL);
	virtual ~CanvasFrame();
// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void DrawBackground(HDC hdc,CRect rect);
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	
	DECLARE_MESSAGE_MAP()

private:
	CRect client_rect;
	HDC hdc;
	CMFC_ClientDlg* Parent;
	int xPos,yPos;

public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	char* Init();
	void setParent(CMFC_ClientDlg* Parent);
	void setPos(int x,int y);
	void DrawClient();
	void addYPos(int direct);
	void addXPos(int direct);
};
