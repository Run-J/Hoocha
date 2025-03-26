#include "../inc/masterListHandler.h"

// Find DC in MasterList
int findDcIndex(MasterList *masterList, pid_t dcPID)
{
    for (int i = 0; i < masterList->numberOfDCs; i++)
    {
        if (masterList->dc[i].dcProcessID == dcPID)
            return i;
    }

    return -1;  // didn't found
}


// Add a new DC
void addDc(MasterList *masterList, pid_t dcPID)
{
    if (masterList->numberOfDCs < MAX_DC_ROLES)
    {
        int idx = masterList->numberOfDCs;
        masterList->dc[idx].dcProcessID = dcPID;
        masterList->dc[idx].lastTimeHeardFrom = time(NULL);
        masterList->numberOfDCs++;

        LogDREvent(idx + 1, dcPID, 0, "added to master list – NEW DC – Status 0 (Everything is OKAY)");
    }
}


// Remove a DC
void removeDc(MasterList *masterList, int idx)
{
    if (idx >= masterList->numberOfDCs) return;

    pid_t removedPID = masterList->dc[idx].dcProcessID;

    LogDREvent(idx + 1, removedPID, 0, "removed from master list – NON-RESPONSIVE");


    // Remove and adjust masterList
    for (int i = idx; i < masterList->numberOfDCs - 1; i++)
    {
        masterList->dc[i] = masterList->dc[i + 1];
    }
    masterList->numberOfDCs--;
}


int terminateIfNoDCs(MasterList *masterList)
{
    if (masterList->numberOfDCs == 0)
    {
        LogDREvent(0, 0, 0, "All DCs have gone offline or terminated – DR TERMINATING");
        // printf("Debug: All DCs offline – DR is terminating...\n");
        return 0;
    }

    return -1;
}
