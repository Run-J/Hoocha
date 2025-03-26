#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include "../../Common/inc/masterList.h"
#include "../../Common/inc/sharedMemoryHandler.h"
#include "../../Common/inc/logger.h"


int messageQueueExists(int msgQueueID);
void deleteMessageQueue(int msgQueueID);
void killDc(MasterList *masterList, int dcIndex);


int main(void)
{
    // 1: Connect to the sharedMemory
    // 1.1: Get correct shared memory key
    key_t shmKey = generateSharedMemoryKey();

    // 1.2: Try to connect with sharedMemory
    int shmID = connectSharedMemory(shmKey);
    // printf("Debug: DX: Successfully connect with the sharedMemory\n");
    LogDXEvent("DX: Successfully connected to shared memory");


    // 1.3: Addtach the sharedMemory to masterList
    MasterList* masterList = attachSharedMemory(shmID);



    // 2: Mian loop
    int retries = 0;
    while (1)
    {
        // Random wait 10-30 seconds
        int sleepTime = (rand() % 21) + 10;
        sleep(sleepTime);

        // Check if the message queue exists
        if (!messageQueueExists(masterList->msgQueueID))
        {
            LogDXEvent("DX detected that msgQ is gone – assuming DR/DCs done");
            break;
        }

        // Select WOD Disruptive Behavior
        int action = rand() % 21;  // 0 - 20
        if (action == 0 || action == 8 || action == 19)
        {
            LogDXEvent("DX: WOD Action – No action taken this round.");
        }
        else if (action == 10 || action == 17)
        {
            deleteMessageQueue(masterList->msgQueueID);
            break;
        }
        else
        {
            int targetIndex = (action % masterList->numberOfDCs); // choose a DC
            if (masterList->numberOfDCs > 0)
            {
                killDc(masterList, targetIndex);
            }
        }
    }


    // 3. Disconnect with the sharedMemory and release the memory before exit
    releaseSharedMemory(shmID, masterList);

    return 0;
}


int messageQueueExists(int msgQueueID)
{
    struct msqid_ds buf;
    return msgctl(msgQueueID, IPC_STAT, &buf) == 0;
}


void deleteMessageQueue(int msgQueueID)
{
    if (msgctl(msgQueueID, IPC_RMID, NULL) == 0)
    {
        LogDXEvent("DX deleted the msgQ – the DR/DCs can’t talk anymore - exiting");
    }
    else
    {
        perror("DX: Failed to delete message queue");
    }
}


void killDc(MasterList *masterList, int dcIndex)
{
    if (dcIndex >= masterList->numberOfDCs) return;

    pid_t targetPID = masterList->dc[dcIndex].dcProcessID;
    if (kill(targetPID, SIGHUP) == 0)
    {
        LogDXEvent("WOD Action – DC-%02d [%d] TERMINATED", dcIndex + 1, targetPID);
    }
    else
    {
        if (errno == ESRCH)
        {
            LogDXEvent("DX: Target DC process no longer exists.");
        }
        else
        {
            perror("DX: kill failed");
        }
    }
}
