#include "stdafx.h"  
//#include "RecvTask.h"  
//#include "ServerConnector.h" 
//
//int RecvTask::svc(void)  
//{  
//    while(true)  
//    {  
//        ServerConnector::getInstance()->recvMessage();  
//        ACE_OS::sleep(ACE_Time_Value(0,5000));  
//    }  
//}  
//  
//int RecvTask::open(void* p)  
//{  
//    activate();  
//    return 0;  
//}  
//  
//int RecvTask::close(u_long)  
//{  
//    return 0;  
//}  
//  
//RecvTask::RecvTask(){}