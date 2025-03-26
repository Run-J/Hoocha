#ifndef MASTERLIST_H
#define MASTERLIST_H

#include <sys/types.h>
#include <time.h>


#define MAX_DC_ROLES 10 // Our DR(data reader) can support to maintain upto 10 DC(data creator)


// Single DC Info
typedef struct
{
    pid_t     dcProcessID;
    time_t    lastTimeHeardFrom;
}DCInfo;


// Shared Memory Struct of MasterList
typedef struct
{
    int    msgQueueID;
    int    numberOfDCs;    // the number of currently online DC
    DCInfo dc[MAX_DC_ROLES];
}MasterList;



#endif