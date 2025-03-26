#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "masterList.h"
#include "logger.h"

int findDcIndex(MasterList *masterList, pid_t dcPID);
void addDc(MasterList *masterList, pid_t dcPID);
void removeDc(MasterList *masterList, int idx);
int terminateIfNoDCs(MasterList *masterList);