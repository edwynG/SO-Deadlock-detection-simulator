#include <stdio.h>
#include <stdlib.h>
#include "deadlock.h"

State *getState(System *system)
{
    State *currentState = (State *)malloc(sizeof(State));
    if (currentState == NULL)
    {
        fprintf(stderr, "Error: No se pudo asignar memoria para el estado actual del sistema.\n");
        exit(EXIT_FAILURE);
    }

    currentState->resourcesVector = system->totalResources;
    currentState->availableVector = system->availableResources;
    currentState->numberProcesses = system->numberProcesses;
    currentState->numberResources = system->numberResources;

    currentState->AllocationMatrix = (int **)malloc(system->numberProcesses * sizeof(int *));
    currentState->needMatrix = (int **)malloc(system->numberProcesses * sizeof(int *));

    for (int i = 0; i < system->numberProcesses; i++)
    {
        currentState->AllocationMatrix[i] = system->processes[i].allocatedResources;
        currentState->needMatrix[i] = system->processes[i].requiredResources;
    }

    return currentState;
}