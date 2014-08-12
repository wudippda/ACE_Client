#pragma once
#include "StdAfx.h"
#include "MessageConstructor.h"

MessageConstructor::MessageConstructor()
{
	;
}

MessageConstructor* MessageConstructor::MCsingleton = NULL;

MessageConstructor::~MessageConstructor()
{
	;
}

ACE_Message_Block* MessageConstructor::createConnection()
{
	cdrOut << ACE_CDR::UShort(COM::CONNECT_SERVER);
	this->writeAddressInfo();
	this->writeTimeStamp();
	this->mb = cdrOut.begin()->duplicate();
	return mb;
}

ACE_Message_Block* MessageConstructor::createClientMoveMessage(bool direction ,ACE_CDR::Short move,ACE_CDR::UShort speed)
{
	cdrOut << ACE_CDR::UShort(COM::CLIENT_MOVE);
	this->writeAddressInfo();
	this->writeTimeStamp();
	cdrOut << ACE_CDR::Boolean(direction);
	cdrOut << ACE_CDR::Short(move);
	cdrOut << ACE_CDR::UShort(speed);
	this->mb = cdrOut.begin()->duplicate();
	return mb;
}

ACE_Message_Block* MessageConstructor::createClientQuitMessage()
{
	cdrOut << ACE_CDR::UShort(COM::CLIENT_QUIT);
	this->writeAddressInfo();
	this->writeTimeStamp();
	this->mb = cdrOut.begin()->duplicate();
	return mb;
}

//ACE_Message_Block* MessageConstructor::createConnectionAck(bool verified)
//{
//	cdrOut << ACE_CDR::UShort(COM::CONNECTION_ACK);
//	this->writeAddressInfo();
//	this->writeTimeStamp();
//	cdrOut << ACE_CDR::Boolean(verified);
//	ACE_Message_Block* mb = cdrOut.begin()->duplicate();
//	return mb;
//}
//
//ACE_Message_Block* MessageConstructor::createConnectionAck(bool verified)
//{
//	cdrOut << ACE_CDR::UShort(COM::CONNECTION_ACK);
//	this->writeAddressInfo();
//	this->writeTimeStamp();
//	cdrOut << ACE_CDR::Boolean(verified);
//	ACE_Message_Block* mb = cdrOut.begin()->duplicate();
//	return mb;
//}
