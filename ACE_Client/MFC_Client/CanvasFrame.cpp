// CanvasFrame.cpp : 实现文件
//
#pragma once
#include "stdafx.h"
#include "MFC_Client.h"
#include "CanvasFrame.h"
#include "afxdialogex.h"
#include "ServerConnector.h"


// CanvasFrame 对话框

//Timer 1
UINT ID_TIMER1 = 1;

IMPLEMENT_DYNAMIC(CanvasFrame, CDialogEx)

CanvasFrame::CanvasFrame(CWnd* pParent /*=NULL*/)
	: CDialogEx(CanvasFrame::IDD, pParent)
{
	
}

CanvasFrame::~CanvasFrame()
{
}

char* CanvasFrame::Init()
{
	this->GetClientRect(&this->client_rect);
	//this->client_rect.bottom - 100;
	char x[8];
	char y[8];
	char dot[2] = ",";
	itoa(client_rect.BottomRight().x - client_rect.TopLeft().x,x,10);
	itoa(client_rect.BottomRight().y - client_rect.TopLeft().y,y,10);

	//CString str;
	//str.Format(_T("%s"), Client::getInstance()->makeCommand(x,DECLARE_SIZE));
	//AfxMessageBox(str);

	char msg[10];
	msg[0] = DECLARE_SIZE;
	msg[1] = '\0';
	strcat(msg,x);
	strcat(msg,dot);
	strcat(msg,y);

	//Client::getInstance()->sendMessage(msg);

	SetTimer(ID_TIMER1,50,NULL);
	this->hdc = GetDC()->GetSafeHdc();
	this->DrawBackground(hdc,client_rect);
	return msg;
}

void CanvasFrame::setParent(CMFC_ClientDlg* Parent)
{
	this->Parent = Parent;
}

void CanvasFrame::setPos(int x, int y)
{
	this->xPos = x;
	this->yPos = y;
	this->DrawClient();
}

void CanvasFrame::DrawClient()
{
	HDC dcBuffer;
	HBITMAP memBM;
	DrawBackground(hdc,this->client_rect);
	dcBuffer = CreateCompatibleDC(hdc);
	memBM = CreateCompatibleBitmap(hdc, client_rect.right - client_rect.left, client_rect.bottom - client_rect.top); // 创建内存图像
	SelectObject(dcBuffer, memBM);
	this->DrawBackground(dcBuffer,client_rect);
	SetBkMode(dcBuffer, TRANSPARENT);

	HPEN hPen = CreatePen (PS_SOLID, 0, RGB(255,0,255));
	HBRUSH hBrush = CreateSolidBrush(RGB(255,0,255));
	SelectObject(dcBuffer,hBrush);
	SelectObject(dcBuffer,hPen);
	
	Ellipse(dcBuffer, xPos - 5, yPos + 5, xPos + 5 ,yPos - 5);
	DeleteObject(hPen);
	DeleteObject(hBrush);

	BitBlt(hdc, 0, 0, client_rect.right - client_rect.left, client_rect.bottom - client_rect.top, dcBuffer, 0, 0, SRCCOPY); // 复制内存图像到屏幕
	DeleteObject(memBM);
	DeleteDC(dcBuffer);
}

void CanvasFrame::DrawBackground(HDC hdc,CRect rect)
{
	HPEN hPen = CreatePen (PS_SOLID, 0, RGB(150,150,150));
	SelectObject(hdc,hPen);
	FillRect(hdc, &client_rect, (HBRUSH)(COLOR_WINDOW + 1));
	for(int ix = 0;ix < rect.right;ix += 30) 
	{ 
		MoveToEx(hdc, ix, 0, NULL) ; 
		LineTo(hdc, ix, rect.bottom) ; 
	}
	for(int iy = 0;iy < rect.bottom;iy += 30) 
	{ 
		MoveToEx(hdc, 0, iy, NULL) ; 
		LineTo(hdc, rect.right, iy) ; 
	}
	DeleteObject(hPen);
	//UpdateData(true);
}

void CanvasFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CanvasFrame, CDialogEx)
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CanvasFrame 消息处理程序
BOOL CanvasFrame::PreTranslateMessage(MSG *pMsg)    
{  
    SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);   
    return CDialog::PreTranslateMessage(pMsg);  
}  

void CanvasFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	char buf[5];
	buf[0] = MOVE;

	switch(nChar)
	{
	case VK_UP:
		
		buf[1] = 'U';
		//this->setPos(this->xPos,this->yPos - 5);
		break;
	case VK_DOWN:
		buf[1] = 'D';
		//this->setPos(this->xPos,this->yPos + 5);
		break;
	case VK_LEFT:
		buf[1] = 'L';
		//this->setPos(this->xPos - 5,this->yPos);
		break;
	case VK_RIGHT:
		buf[1] = 'R';
		//this->setPos(this->xPos + 5,this->yPos);
		break;
	}

	buf[2] = '\0';
	Client::getInstance()->sendMessage(buf);

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
	
    //AfxMessageBox(str);   
    //CDialog::OnKeyDown(nChar,nRepCnt,nFlags);
}


void CanvasFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	
}

void CanvasFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}

void CanvasFrame::addYPos(int direct)
{
	this->yPos += (direct * 5);
	this->DrawClient();
}

void CanvasFrame::addXPos(int direct)
{
	this->xPos += (direct * 5);
	this->DrawClient();
}
