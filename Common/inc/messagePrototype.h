#ifndef MESSAGEPROTOTYPE_H
#define MESSAGEPROTOTYPE_H


#include <sys/types.h>


// DC possible states
#define STATUS_OK 0
#define STATUS_HYDRAULIC_FAILURE 1
#define STATUS_SAFETY_FAILURE 2
#define STATUS_NO_MATERIAL 3
#define STATUS_TEMP_OUT 4
#define STATUS_OPERATOR_ERROR 5
#define STATUS_OFFLINE 6


// The format of the message sent by DC
typedef struct
{
    long msgType;   // message queue type (1)
    pid_t dcProcessID;  // PID of the DC
    int statusCode;  // status code (0-6)
    char statusText[50];  // Status description text
} DCMessage;


#endif