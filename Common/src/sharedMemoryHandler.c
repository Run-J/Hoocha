#include "../inc/sharedMemoryHandler.h"

key_t generateSharedMemoryKey()
{
    key_t key = ftok(SHM_KEY_PATH, SHM_PROJ_ID);
    if (key == -1)
    {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }
    return key;
}


int createSharedMemory(key_t shmKey)
{
    int shmID = shmget(shmKey, sizeof(MasterList), 0666 | IPC_CREAT);
    if (shmID == -1)
    {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    LogDREvent(0, 0, 0, "Shared memory created");
    return shmID;
}


int connectSharedMemory(key_t shmKey)
{
    int shmID = shmget(shmKey, sizeof(MasterList), 0666);
    while (shmID == -1)
    {
        // printf("Debug: DX: the sharedMemory is not exist now, wait 3s...\n");
        LogDREvent(0, 0, 0, "Shared memory created");
        sleep(3);
    }

    return shmID;
}


MasterList* attachSharedMemory(int shmID)
{
    MasterList* masterList = (MasterList*) shmat(shmID, NULL, 0);
    if (masterList == (void*) -1)
    {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    LogDREvent(0, 0, 0, "Shared memory attached");
    return masterList;
}


void initializeMasterList(MasterList* masterList, int msgID)
{
    if (masterList == NULL)
    {
        fprintf(stderr, "Error: masterList is NULL\n");
        return;
    }
    masterList->msgQueueID = msgID;
    masterList->numberOfDCs = 0;
    memset(masterList->dc, 0, sizeof(masterList->dc));
}


void releaseSharedMemory(int shmID, MasterList* masterList)
{
    if (shmdt(masterList) == -1)
    {
        perror("shmdt failed");
    }

    if (shmctl(shmID, IPC_RMID, NULL) == -1)
    {
        // printf("Debug: Releasing shared memory with shmID: %d\n", shmID);
        perror("shmctl failed");
    }
    else
    {
        LogDREvent(0, 0, 0, "Shared memory released");
    }
}
