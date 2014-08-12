#pragma once
#include "ACE_headers.h"
#include "Sender.h"

class ACE_Connector : public ACE_Asynch_Connector<Sender>
{
public:

	ACE_Connector();
	
	static Sender* sender_handler;
    void free_handler( Sender* service );
	Sender* getHandler(){return this->make_handler();}
 
private:
    virtual Sender *make_handler(void)
	{
		if(sender_handler == NULL)
			sender_handler = new Sender();
		return sender_handler;
	}
    void init_handlers();
};