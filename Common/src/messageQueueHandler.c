#include "../inc/messageQueueHandler.h"


// Generate message queue key
key_t generateMessageQueueKey()
{
    key_t key = ftok(MSG_KEY_PATH, MSG_PROJ_ID);
    if (key == -1)
    {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }
    return key;
}


// Create a message queue
int createMessageQueueIfNotExists(key_t mqKey)
{
    // printf("Debug: (mqKey: %d)\n", mqKey);

    // Try to get a message queue that already exists
    int msgID = msgget(mqKey, 0);
    // printf("Debug: msgget() returned: %d\n", msgID);

    if (msgID >= 0)
    {
        // printf("Debug: Message queue already exists (msgID: %d)\n", msgID);
        LogDREvent(0, 0, 0, "Message queue already exists");
        return msgID;
    }

    // Create a message queue if not exists
    if (msgID == -1)
    {
        msgID = msgget(mqKey, IPC_CREAT | 0666);
        if (msgID < 0)
        {
            perror("msgget (creating queue) failed");
            exit(EXIT_FAILURE);
        }
    }

    // printf("Debug: Created new message queue (msgID: %d)\n", msgID);
    LogDREvent(0, 0, 0, "Message queue created");
    return msgID;
}


// Create a message queue
int connectMessageQueue(key_t mqKey)
{
    int msgID = msgget(mqKey, 0666);
    return msgID;
    // printf("Debug: Message queue already exists (msgID: %d)\n", msgID);
}


// Listen to the message queue
int receiveMessage(int msgQueueID, DCMessage *msg)
{
    return msgrcv(msgQueueID, msg, sizeof(DCMessage) - sizeof(long), 1, 0);
}


// Process DC messages
void handleDCMessage(MasterList *masterList, DCMessage *msg)
{
    // check if this is new dc machine
    int idx = findDcIndex(masterList, msg->dcProcessID);

    if (idx == -1) // didn't found
    {
        addDc(masterList, msg->dcProcessID);
    } else
    {
        masterList->dc[idx].lastTimeHeardFrom = time(NULL); // Update the latest showup time
    }

    // Processing DC Offline
    if (msg->statusCode == STATUS_OFFLINE)
    {
        // printf("DC [%d] is offline, removing from list...\n", msg->dcProcessID);
        LogDREvent(idx + 1, msg->dcProcessID, 6, "DC is offline, removing from list...");
        removeDc(masterList, idx);
    }
}


// Check for DC timeout
void checkDCStatus(MasterList *masterList)
{
    time_t now = time(NULL);
    for (int i = 0; i < masterList->numberOfDCs; i++)
    {
        if (now - masterList->dc[i].lastTimeHeardFrom > 35)
        {
            // printf("Debug DR: DC [%d] has been non-responsive for 35 seconds, removing...\n", masterList->dc[i].dcProcessID);
            LogDREvent(i + 1, masterList->dc[i].dcProcessID, 0, "marked as non-responsive – removing...");
            removeDc(masterList, i);
            i--;  // Recheck the list to avoid skipping elements
        }
    }
}


// Delete the message queue
void removeMessageQueue(int msgQueueID)
{
    if (msgctl(msgQueueID, IPC_RMID, NULL) == -1)
    {
        perror("msgctl failed");
    }
    else
    {
        LogDREvent(0, 0, 0, "Message queue removed");
    }
}