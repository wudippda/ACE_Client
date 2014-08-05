#include "stdafx.h"  
#include "RecvTask.h"  
#include "ServerConnector.h"
#include "MessageConstructor.h"

ServerConnector::~ServerConnector()  
{  
    if (recvTask != NULL)  
    {  
        delete recvTask;  
        recvTask = NULL;  
    }  
}  

ServerConnector* ServerConnector::getInstance()  
{  
    if(CSingleton == NULL)
    {  
        static ServerConnector tmpInstance;
        CSingleton = &tmpInstance;  
    }  
    return CSingleton;  
}

int ServerConnector::connect(int port,char* localhost)  
{  
    recvTask = new RecvTask();   
    ACE_INET_Addr remote_addr(port,localhost);  
    int result = connector.connect(stream, remote_addr);  
    if (result == 0)  
    {  
        recvTask->open(0);
		this->getLocalAddr();
    }
	else
	{  
        recvTask->close(0);  
        delete recvTask;  
    }  
    return result;  
}  
int ServerConnector::sendMessage(char* msg)  
{  
    return stream.send_n(msg,ACE_OS::strlen(msg));  
}

void ServerConnector::recvMessage()  
{  
    size_t recv_len;
	ACE_Message_Block mb;  
    char sLen[MSG_LEN_BYTES];  
      
    ACE_Time_Value t(0, TIME_OUT_VALUE / 2);  
    stream.recv_n(sLen, MSG_LEN_BYTES, &t, &recv_len);  

	this->dispatcher = new MessageDispatcher();
	this->handler = new MessageHandler();

    if (recv_len != 0)  
    {  
		mb.copy(sLen);
		dispatcher->dispatchMessage(mb);

		ACE_UINT32 cmd = dispatcher->getCmd();
		//ACE_Message_Block* smb;

		//case CONNECTION_ACK
		//------------------------------------------------------------------------//
		if(cmd = COM::CONNECTION_ACK)
		{
			handler->handleMoveSuccessClient();
		}

		//case MOVE_SUCCESS_ACK
		//------------------------------------------------------------------------//
		else if(cmd = COM::MOVE_SUCCESS_ACK)
		{
			handler->handleMoveSuccessClient();
		}

		//case CHAT_SUCCESS_ACK
		//------------------------------------------------------------------------//

		//case UPDATA_NEIGHBOUR
		//------------------------------------------------------------------------//

		dispatcher->setMB_NULL();

		//CString str;
        //sLen[recv_len] = '\0';
		//str.Format(_T("%s"), sLen);
		//AfxMessageBox(str);
    }  

	mb.release();
	if(handler != NULL)
		delete handler;
	if(dispatcher != NULL)
		delete dispatcher;
}

void ServerConnector::holdWindowInstance(CanvasFrame* Dlgptr)
{
	this->Dlgptr = Dlgptr;
}

int ServerConnector::close()  
{  
    recvTask->close(0);  
    stream.close();  
    return 0;  
}  

void ServerConnector::getLocalAddr()
{
	ACE_SOCK_SEQPACK_Association sock_association(this->stream.get_handle());
	size_t addr_size = 1;
	sock_association.get_local_addrs(&(this->local_addr),addr_size);

	AfxMessageBox(this->local_addr.get_host_addr());
	//set local address to Message Constructor
	MessageConstructor::getInstance()->setAddress(this->local_addr);
}
  
ServerConnector::ServerConnector()  
{  
	;
}