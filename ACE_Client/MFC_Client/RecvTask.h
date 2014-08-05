#ifndef RECVTASK_H  
#define RECVTASK_H  
#endif 

#pragma once
#include "ACE_headers.h"

#define MSG_LEN_BYTES 128  
#define TIME_OUT_VALUE 1000000    
  
class RecvTask: public ACE_Task<ACE_MT_SYNCH>  
{  
public:  
    RecvTask();  
    int open(void* p);  
    int close(u_long);  
    //���շ���������Ϣ  
    int svc(void);  
};  
 