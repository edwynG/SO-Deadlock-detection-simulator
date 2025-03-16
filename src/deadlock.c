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
    int *work = (int *)malloc(state->numberResources * sizeof(int));
    work = state->availableResources;

    int *finish = (int *)malloc(state->numberProcesses * sizeof(int));

    for (int i = 0; i < state->numberProcesses; i++){
        if (getSumOfRow(state->allocatedResources[i], state->numberResources) != 0){
            finish[i] = 0;
        }
    }

    int posible = 1;
    while (posible)
    {
        int foundProcess = findProcess(finish, state->neededResources, state->allocatedResources, state->numberProcesses, work);
        if(foundProcess >= 0)
        {
            // Ejecutar
            getSumOfVectors(work, state->allocatedResources[foundProcess], state->numberResources); // Liberar recursos
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
        int *diff = (int *)malloc(n * sizeof(int)); 
        getDiffOfVectors(diff, neededResources[i], allocatedResources[i], n); // Need[i][] - Allocation[i][]

        if(finish[i] == 0 && isLessVector(diff, work, n)) // Diff <= Work
        {
            return i;
        }
    }
    return -1;
}

int isLessVector(int *vectorA, int *vectorB, int n)
{
    for (int i = 0; i < n; i++)
    {
        if(vectorA[i] >= vectorB[i])
        {
            return 0;
        }
    }
    return 1; // vectorA[i] < vectorB[i] para todo i
}

void getSumOfVectors(int *vectorA, int *vectorB, int n){
    for (int i = 0; i < n; i++)
    {
        vectorA[i] += vectorB[i];
    }
}

void getDiffOfVectors(int *vectorR, int *vectorA, int *vectorB, int n){
    for (int i = 0; i < n; i++)
    {
        vectorR[i] = vectorA[i] - vectorB[i];
    }
}

int getSumOfRow(int *vector, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += vector[i];
    }
    return sum;
}