#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include "../../Common/inc/sharedMemoryHandler.h"
#include "../../Common/inc/messageQueueHandler.h"

#include "../../Common/inc/masterList.h"
#include "../../Common/inc/messagePrototype.h"



int main(void)
{
    // 0: Create MessageQueue if not exists
    key_t mqKey = generateMessageQueueKey();
    int msgQueueID = createMessageQueueIfNotExists(mqKey);

    LogDREvent(0, 0, 0, "Message queue created or connected");

    // 1: SetUp the sharedMemory things
    // 1.1: Generate a unique key
    key_t shmKey = generateSharedMemoryKey();

    // 1.2: Create a sharedMemory
    int shmID = createSharedMemory(shmKey);
    // printf("Debug DR: SharedMemoryID %d\n", shmID);
    LogDREvent(0, 0, 0, "Shared memory created");


    // 1.3: Addtach the sharedMemory to masterList
    MasterList* masterList = attachSharedMemory(shmID);


    // 2. Setup the masterList
    initializeMasterList(masterList, msgQueueID);

    // printf("Debug: DR: MasterList finish the initialization\n");
    LogDREvent(0, 0, 0, "MasterList initialized");



    // 3. Main process runnning
    DCMessage msg;
    while (1)
    {
        if (receiveMessage(msgQueueID, &msg) > 0)
        {
            // Record incoming messages
            LogDREvent(msg.dcProcessID, msg.dcProcessID, msg.statusCode, msg.statusText);

            handleDCMessage(masterList, &msg);
        }
        checkDCStatus(masterList);

        if (terminateIfNoDCs(masterList) == 0)
        {
            LogDREvent(0, 0, 0, "All DCs have disconnected. DR terminating.");

            break; // Terminate DR if all DCs are disconnected
        }

        sleep(1.5);
    }


    // 4. Release the memory before exit
    releaseSharedMemory(shmID, masterList);
    removeMessageQueue(msgQueueID);

    return 0;
}
