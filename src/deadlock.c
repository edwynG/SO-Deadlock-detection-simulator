#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "deadlock.h"
#include "utils.h"

State *getState(System *system)
{
    State *currentState = (State *)malloc(sizeof(State));
    if (currentState == NULL)
    {
        fprintf(stderr, "Error: No se pudo asignar memoria para el estado actual del sistema.\n");
        exit(EXIT_FAILURE);
    }

    currentState->totalResources = system->totalResources;
    currentState->availableResources = system->availableResources;
    currentState->numberProcesses = system->numberProcesses;
    currentState->numberResources = system->numberResources;

    currentState->allocatedResources = (int **)malloc(system->numberProcesses * sizeof(int *));
    currentState->neededResources = (int **)malloc(system->numberProcesses * sizeof(int *));

    for (int i = 0; i < system->numberProcesses; i++)
    {
        currentState->allocatedResources[i] = system->processes[i].allocatedResources;
        currentState->neededResources[i] = system->processes[i].requestedResources;
    }

    return currentState;
}

int isStateSafe(State *state)
{
    int *work = (int *)malloc(state->numberResources * sizeof(int));
    work = state->availableResources;

    int *finish = (int *)malloc(state->numberProcesses * sizeof(int));

    for (int i = 0; i < state->numberProcesses; i++)
    {
        if (getSumOfRow(state->allocatedResources[i], state->numberResources) != 0){
            finish[i] = 0;
        }
    }

    int posible = 1;
    while (posible)
    {
        int foundProcess = findProcess(finish, state->neededResources, state->allocatedResources, state->numberResources, work);
        if(foundProcess >= 0)
        {
            // Work = Work + Allocation[i][]
            getSumOfVectors(work, work, state->allocatedResources[foundProcess], state->numberResources); // Liberar recursos
            // Finish[i] = false
            finish[foundProcess] = 1; // Finalizar proceso
        }
        else
        {
            posible = 0;
        }
    }

    for (int i = 0; i < state->numberProcesses; i++)
    {
        if (finish[i] == 0) // Proceso no finalizado
            return 0; // Estado inseguro
    }

    free(work);
    return 1; // Estado seguro
}

int findProcess(int *finish, int **neededResources, int **allocatedResources, int *work, int n)
{
    
    for (int i = 0; i < n; i++)
    {
        int *diff = (int *)malloc(n * sizeof(int)); // Diff
        getDiffOfVectors(diff, neededResources[i], allocatedResources[i], n); // Diff = Need[i][] - Allocation[i][]

        if(finish[i] == 0 && isLessThanVector(diff, work, n)) // Diff <= Work
        {
            return i;
        }
    }
    return -1;
}