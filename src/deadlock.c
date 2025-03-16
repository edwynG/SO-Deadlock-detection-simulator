#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "deadlock.h"

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
    int *work = state->availableResources;
    int *finish = (int *)malloc(state->numberProcesses * sizeof(int));

    for (int i = 0; i < state->numberProcesses; i++){
        if (getSumOfRow(state->allocatedResources[i], state->numberResources) != 0){
            finish[i] = 0;
        }
    }

    for (int i = 0; i < state->numberProcesses; i++)
    {
        
        if (finish[i] == 0 && getSumOfRow(state->request[i], state->numberResources) - getSumOfRow(state->allocatedResources[i], state->numberResources) < getSumOfRow(work)) // Ejecutar
        { 
            freeResources(work, state->allocatedResources[i], state->numberResources); // Liberar recursos
            emptyRequests(state->request[i], state->numberResources); // Eliminar aristas de solicitud
            finish[i] = 1;
        }
    }

    for (int i = 0; i < state->numberProcesses; i++)
    {
        if (finish[i] == 0)
            return 0;
    }

    return 1;
}

void freeResources(int *work, int *allocatedResources, int n){
    for (int i = 0; i < n; i++)
    {
        work[i] += allocatedResources[i];
    }
}

void emptyRequests(int *requestMatrix, int n)
{
    for(int j = 0; j < requestMatrix; j++)
    {
        requestMatrix[j] = 0; 
    }
}

int getSumOfRow(int *vector, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = vector[i];
    }
    return sum;
}