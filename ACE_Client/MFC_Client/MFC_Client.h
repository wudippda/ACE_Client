
// MFC_Client.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_ClientApp:
// �йش����ʵ�֣������ MFC_Client.cpp
//

class CMFC_ClientApp : public CWinApp
{
public:
	CMFC_ClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFC_ClientApp theApp;