
#include <cstring>


#include "config.h"


typedef struct {
    char name[MAX_LABEL_LENGTH];
    int offset;
} LabelEntry_t;

static LabelEntry_t labelList[MAX_NUM_LABELS];

static int lastEntryIdx = 0;

bool addLabelToList(char* name, int offset)
{
    if (lastEntryIdx < MAX_NUM_LABELS)
    {
        strncpy(labelList[lastEntryIdx].name, name, MAX_LABEL_LENGTH);
        labelList[lastEntryIdx].name[MAX_LABEL_LENGTH-1] = '\0';
        labelList[lastEntryIdx].offset = offset;
        
        lastEntryIdx++;

        return true;
    } else {
        return false;
    }
}

int getLabelOffset(char* name)
{
    int idx;
    for (idx = 0; idx < lastEntryIdx; idx++)
    {
        if (strcmp(labelList[idx].name, name) == 0)
        {
            return labelList[idx].offset;
        }
    }

    return -1;
}


