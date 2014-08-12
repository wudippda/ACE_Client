//#pragma once
//
//#include "COM.h"
//#include "stdafx.h"
//#include "resource.h"
//#include "ACE_headers.h"
//#include "MessageHandler.h"
//#include "MessageDispatcher.h"
//#include "RecvTask.h"
//#include "MFC_ClientDlg.h"
//#include "CanvasFrame.h"
//
//class Client
//{
//public:
//	int xPos,yPos;
//	int speed;
//};
//
//class ServerConnector  
//{  
//public:  
//
//	~ServerConnector();
//    int connect(int port,char* localhost);  
//    static ServerConnector* getInstance();  
//    int sendMessage(char* msg);  
//    int close();  
//      
//    void recvMessage();
//	void getLocalAddr();
//	void holdWindowInstance(CanvasFrame* Dlgptr);
//  
//private:  
//    ServerConnector();
//	ACE_INET_Addr local_addr;
//    ACE_SOCK_Connector connector;  
//    ACE_Thread_Mutex mutex;
//	ACE_SOCK_Stream stream;    
//    RecvTask* recvTask;  
//	CanvasFrame* Dlgptr;
//	MessageHandler* handler;
//	MessageDispatcher* dispatcher;
//
//	static ServerConnector* CSingleton;
//	Client avatar;
//};  
//  