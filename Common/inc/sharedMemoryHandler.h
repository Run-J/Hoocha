#ifndef SHARED_MEMORY_HANDLER_H
#define SHARED_MEMORY_HANDLER_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include "../../Common/inc/masterList.h"
#include "../inc/logger.h"

// Unique key of sharedMemory
#define SHM_KEY_PATH "."
#define SHM_PROJ_ID 16535

// Prototypes
key_t generateSharedMemoryKey();
int createSharedMemory(key_t shmKey);
int connectSharedMemory(key_t shmKey);
MasterList* attachSharedMemory(int shmID);
void initializeMasterList(MasterList* masterList, int msgID);
void releaseSharedMemory(int shmID, MasterList* masterList);

#endif // SHARED_MEMORY_HANDLER_H
