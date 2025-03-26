#ifndef MESSAGE_QUEUE_HANDLER_H
#define MESSAGE_QUEUE_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>
#include "../inc/masterList.h"
#include "../inc/masterListHandler.h"
#include "../inc/messagePrototype.h"

// Define the message queue Key
#define MSG_KEY_PATH "/tmp"
#define MSG_PROJ_ID 12345

// Message queue initialization & release
key_t generateMessageQueueKey();
int createMessageQueueIfNotExists(key_t mqKey);
int connectMessageQueue(key_t mqKey);
void removeMessageQueue(int msgQueueID);

// Message handling
int receiveMessage(int msgQueueID, DCMessage *msg);
void handleDCMessage(MasterList *masterList, DCMessage *msg);
void checkDCStatus(MasterList *masterList);

#endif // MESSAGE_QUEUE_HANDLER_H

