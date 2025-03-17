#include <stdio.h>
#include "process.h"
#include "deadlock.h"
#include "utils.h"


void stopProcess(Process *process, char state)
{
    if (process == NULL)
    {
        return;
    }
    process->state = state;
    getDiffOfVectors(process->allocatedResources, process->allocatedResources, process->allocatedResources, process->numberResources);
    getDiffOfVectors(process->neededResources, process->neededResources, process->neededResources, process->numberResources);
}