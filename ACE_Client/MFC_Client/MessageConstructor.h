#pragma once
#include "StdAfx.h"
#include "COM.h"
#include "type.h"
#include "ACE_headers.h"

class MessageConstructor
{
private:

	MessageConstructor();
	~MessageConstructor();

	ACE_OutputCDR cdrOut;
	ACE_INET_Addr m_address;
	ACE_Message_Block *mb;
	static MessageConstructor* MCsingleton;

	void writeAddressInfo()
	{
		this->cdrOut << ACE_CDR::ULong(this->m_address.get_ip_address());
		this->cdrOut << ACE_CDR::UShort(this->m_address.get_port_number());
	}

	void writeTimeStamp()
	{
		this->cdrOut << ACE_CDR::LongLong(time(0));
	}

public:

	static MessageConstructor* getInstance()
	{
		if(MCsingleton == NULL)
		{
			static MessageConstructor instance;
			MCsingleton = &instance;
		}
		return MCsingleton;
	}

	void setAddress(ACE_INET_Addr addr){this->m_address = addr;}
	void setMB_NULL(){this->mb = NULL;}

public:

	ACE_Message_Block* createConnection();
	ACE_Message_Block* createClientMoveMessage(bool direction ,ACE_CDR::Short move,ACE_CDR::UShort speed);
	ACE_Message_Block* createClientQuitMessage();
	/*ACE_Message_Block* createUpdataNeighborMessage(char* data);
	ACE_Message_Block* createUpdataNeighborMessage(char* data);
	ACE_Message_Block* createUpdataNeighborMessage(char* data);
	ACE_Message_Block* createUpdataNeighborMessage(char* data);
	ACE_Message_Block* createUpdataNeighborMessage(char* data);
	ACE_Message_Block* createUpdataNeighborMessage(char* data);*/
};