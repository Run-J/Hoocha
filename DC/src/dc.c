#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "../../Common/inc/messagePrototype.h"
#include "../../Common/inc/messageQueueHandler.h"

const char *getStatusText(int status);
int getRandomStatus(void);

int main(void)
{
    // 0. Initialize some things
    int msgID = 0;
    DCMessage msg;
    pid_t myPID = getpid();
    srand(time(NULL) ^ myPID);  // Initialize random number seed with time + process ID
    key_t mqKey = generateMessageQueueKey();


    // 1. Connect to message queue, wait if not present
    while ((msgID = msgget(mqKey, 0666)) < 0)
    {
        // printf("DC [%d]: Message queue does not exist, wait 10s...\n", myPID);
        sleep(10);
    }

    // printf("DC [%d]: Successful connection to message queue.\n", myPID);
    LogDCEvent(myPID, STATUS_OK, "Connected to message queue");

    // 2. Send the first “Everything is OKAY” message.
    msg.msgType = 1;
    msg.dcProcessID = myPID;
    msg.statusCode = STATUS_OK;
    strcpy(msg.statusText, getStatusText(STATUS_OK));

    if (msgsnd(msgID, &msg, sizeof(DCMessage) - sizeof(long), 0) == 0)
    {
        LogDCEvent(myPID, STATUS_OK, msg.statusText);
    }


    // 3. Enter the main loop and send random status messages
    while (1)
    {
        int sleepTime = (rand() % 21) + 10; // 10-30 second intervals
        sleep(sleepTime);

        msg.statusCode = getRandomStatus();
        strcpy(msg.statusText, getStatusText(msg.statusCode));

        if (msgsnd(msgID, &msg, sizeof(DCMessage) - sizeof(long), 0) == 0) {
            LogDCEvent(myPID, msg.statusCode, msg.statusText);
        }

        // If the status is “Machine is Off-line”, exit the
        if (msg.statusCode == STATUS_OFFLINE)
        {
            // printf("DC [%d]: Send an offline message to exit.\n", myPID);
            LogDCEvent(myPID, STATUS_OFFLINE, "Machine is Off-line, exiting.");
            exit(0);
        }
    }

    return 0;
}


const char *getStatusText(int status)
{
    switch (status)
    {
        case STATUS_OK: return "Everything is OKAY";
        case STATUS_HYDRAULIC_FAILURE: return "Hydraulic Pressure Failure";
        case STATUS_SAFETY_FAILURE: return "Safety Button Failure";
        case STATUS_NO_MATERIAL: return "No Raw Material in the Process";
        case STATUS_TEMP_OUT: return "Operating Temperature Out of Range";
        case STATUS_OPERATOR_ERROR: return "Operator Error";
        case STATUS_OFFLINE: return "Machine is Off-line";
        default: return "Unknown Status";
    }
}


int getRandomStatus(void)
{
    return rand() % 7;  // Generate a random number between 0 and 6
}
