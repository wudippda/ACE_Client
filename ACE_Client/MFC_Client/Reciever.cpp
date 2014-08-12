#pragma once
#include "StdAfx.h"
#include "Reciever.h"

#pragma comment(lib,"ACEd.lib")

Reciever::Reciever()
{
	;
}

Reciever::~Reciever()
{  
	if(handler != NULL)
		delete handler;
	if(dispatcher != NULL)
		delete dispatcher;

    if (this->handle () != ACE_INVALID_HANDLE)  
        ACE_OS::closesocket (this->handle ());  
}

void Reciever::open (ACE_HANDLE h, ACE_Message_Block&)  
{  
	//ACE_DEBUG LOG here,print ip,port,establish time

	//client_address.addr_to_string(peer_name, sizeof(peer_name) / sizeof(ACE_TCHAR));
	//ACE_DEBUG((LM_DEBUG, "%s", "\nOne User has established a connection.\n"));
	//ACE_DEBUG((LM_DEBUG,ACE_TEXT("IP Address:%s \n"),peer_name));
	ACE_OS::printf("One User has established a connection.\n");
	ACE_OS::printf("Current time:%s",this->curTime());

	//get remote ip and port
	/*ACE_INET_Addr addr;
	ACE_SOCK_SEQPACK_Association ass = ACE_SOCK_SEQPACK_Association(h); 
	size_t addr_size = 1; 
	ass.get_local_addrs(&addr,addr_size);*/

    this->handle(h);
    if (this->reader_.open(*this) != 0 )  
        {  
            delete this;  
            return;  
        }  
        if (this->writer_.open(*this) != 0 )  
        {  
            delete this;  
            return;  
		}

        ACE_Message_Block *mb = new ACE_Message_Block(buffer,MAX_MSG_LEN);  
        if (this->reader_.read (*mb, mb->space()) != 0)  
        {  
            //ACE_OS::printf("Begin read failed!\n");  
            delete this;  
            return;
        }
        return;  
}  
      
void Reciever::handle_read_stream (const ACE_Asynch_Read_Stream::Result &result)
{  
    ACE_Message_Block &mb = result.message_block ();

    //if the connection is failed£¬release the connection resource to the client
    if (!result.success () || result.bytes_transferred () == 0)  
    {  
        mb.release ();  
        delete this;  
        return;  
    }

	dispatcher = new MessageDispatcher();
	dispatcher->dispatchMessage(mb);
	handler = new MessageHandler();
	ACE_UINT32 cmd = dispatcher->getCmd();
	ACE_Message_Block* smb;

	//ACE_Message_Block* smb;

	//case CONNECTION_ACK
	//------------------------------------------------------------------------//
	if(cmd == COM::CONNECTION_ACK)
	{
		handler->handleMoveSuccessClient();
	}

	//case MOVE_SUCCESS_ACK
	//------------------------------------------------------------------------//
	else if(cmd == COM::MOVE_SUCCESS_ACK)
	{
		handler->handleMoveSuccessClient();
	}

	//case CHAT_SUCCESS_ACK
	//------------------------------------------------------------------------//

	//case UPDATA_NEIGHBOUR
	//------------------------------------------------------------------------//

	dispatcher->setMB_NULL();
	mb.release();
	ACE_OS::printf("\nMMB data:%s\n",smb->rd_ptr());
	if (this->writer_.write(*smb,smb->length()) != 0)  
	{  
		ACE_OS::printf("Write Failed!");
		//MessageConstructor::getInstance()->setMB_NULL();
		smb->release();
		delete this; 
		return;
	}

	MessageConstructor::getInstance()->setMB_NULL();

	if(handler != NULL)
		delete handler;
	if(dispatcher != NULL)
		delete dispatcher;

	smb->release();
}
  
void Reciever::handle_write_dgram(const ACE_Asynch_Write_Stream::Result &result)  
{  
    ACE_Message_Block &mb = result.message_block ();  
    mb.release();  
    return;  
}

char* Reciever::curTime()
{
	time_t now = ACE_OS::gettimeofday().sec();
    char *time = ctime(&now);
	return time;
}