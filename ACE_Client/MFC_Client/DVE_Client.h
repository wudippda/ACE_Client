#pragma once
#include "StdAfx.h"
#include "Reciever.h"
#include "Sender.h"

#define LISTEN_PORT 20003
#define REMOTE_SERVER_PORT 20002
#define REMOTE_CLIENT_PORT 20003

class DVE_Server
{
public:

	DVE_Server();
	bool connectToClient(ACE_INET_Addr addr,ACE_UINT16 cmd);

	ACE_Asynch_Acceptor<Reciever> acceptor;
	ACE_Asynch_Connector<Sender> connector;
};
