#pragma once
#include "StdAfx.h"
#include "ACE_headers.h"

class MessageHandler
{
public:
	
	MessageHandler();
	~MessageHandler();

	void handleMoveSuccessClient();
	void handleConnetionSuccessClient();

private:

	//ClientManager* m_ClientManager;
};