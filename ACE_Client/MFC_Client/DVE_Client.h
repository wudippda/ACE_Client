#pragma once
#include "StdAfx.h"
#include "Reciever.h"
#include "Sender.h"
#include "ACE_Connector.h"

class DVE_Client
{
public:

	DVE_Client();
	//bool connectToClient(ACE_INET_Addr addr,ACE_UINT16 cmd);

	ACE_Asynch_Acceptor<Reciever> acceptor;
	ACE_Connector connector;
};
