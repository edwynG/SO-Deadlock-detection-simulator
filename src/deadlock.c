#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        currentState->neededResources[i] = system->processes[i].neededResources;
    }

    return currentState;
}

State *getCopyOfState(State *originalState) {
    if (originalState == NULL) {
        return NULL;
    }

    State *newState = (State *)malloc(sizeof(State));
    if (newState == NULL) {
        perror("Error al asignar memoria para newState");
        return NULL;
    }

    // Copiar miembros simples
    newState->numberProcesses = originalState->numberProcesses;
    newState->numberResources = originalState->numberResources;

    // Copiar arrays de enteros
    newState->totalResources = (int *)malloc(originalState->numberResources * sizeof(int));
    if (newState->totalResources == NULL) {
        perror("Error al asignar memoria para totalResources");
        free(newState);
        return NULL;
    }
    memcpy(newState->totalResources, originalState->totalResources, originalState->numberResources * sizeof(int));

    newState->availableResources = (int *)malloc(originalState->numberResources * sizeof(int));
    if (newState->availableResources == NULL) {
        perror("Error al asignar memoria para availableResources");
        free(newState->totalResources);
        free(newState);
        return NULL;
    }
    memcpy(newState->availableResources, originalState->availableResources, originalState->numberResources * sizeof(int));

    // Copiar matrices de enteros
    newState->allocatedResources = (int **)malloc(originalState->numberProcesses * sizeof(int *));
    if (newState->allocatedResources == NULL) {
        perror("Error al asignar memoria para allocatedResources");
        free(newState->totalResources);
        free(newState->availableResources);
        free(newState);
        return NULL;
    }
    for (int i = 0; i < originalState->numberProcesses; i++) {
        newState->allocatedResources[i] = (int *)malloc(originalState->numberResources * sizeof(int));
        if (newState->allocatedResources[i] == NULL) {
            perror("Error al asignar memoria para allocatedResources[i]");
            // Limpiar la memoria asignada previamente
            for (int j = 0; j < i; j++) {
                free(newState->allocatedResources[j]);
            }
            free(newState->allocatedResources);
            free(newState->totalResources);
            free(newState->availableResources);
            free(newState);
            return NULL;
        }
        memcpy(newState->allocatedResources[i], originalState->allocatedResources[i], originalState->numberResources * sizeof(int));
    }

    newState->neededResources = (int **)malloc(originalState->numberProcesses * sizeof(int *));
    if (newState->neededResources == NULL) {
        perror("Error al asignar memoria para neededResources");
        // Limpiar la memoria asignada previamente
        for (int i = 0; i < originalState->numberProcesses; i++) {
            free(newState->allocatedResources[i]);
        }
        free(newState->allocatedResources);
        free(newState->totalResources);
        free(newState->availableResources);
        free(newState);
        return NULL;
    }
    for (int i = 0; i < originalState->numberProcesses; i++) {
        newState->neededResources[i] = (int *)malloc(originalState->numberResources * sizeof(int));
        if (newState->neededResources[i] == NULL) {
            perror("Error al asignar memoria para neededResources[i]");
            // Limpiar la memoria asignada previamente
            for (int j = 0; j < i; j++) {
                free(newState->neededResources[j]);
            }
            for (int j = 0; j < originalState->numberProcesses; j++) {
                free(newState->allocatedResources[j]);
            }
            free(newState->allocatedResources);
            free(newState->neededResources);
            free(newState->totalResources);
            free(newState->availableResources);
            free(newState);
            return NULL;
        }
        memcpy(newState->neededResources[i], originalState->neededResources[i], originalState->numberResources * sizeof(int));
    }

    return newState;
}


int findProcess(int *finish, int **neededResources, int **allocatedResources, int *work, int n)
{
    printf("TOFIX: find\n");
    for (int i = 0; i < n; i++)
    {
        int *diff = (int *)malloc(n * sizeof(int)); // Diff
        getDiffOfVectors(diff, neededResources[i], allocatedResources[i], n); // Diff = Need[i][] - Allocation[i][]
        if(finish[i] == 0 && isLessEqualThanVector(diff, work, n)) // Diff <= Work
        {
            return i;
        }
    }
    return -1;
}

int isStateSafe(State *state)
{

    int *work = (int *)malloc(state->numberResources * sizeof(int));
    work = state->availableResources;

    int *finish = (int *)malloc(state->numberProcesses * sizeof(int));

    // No finalizados
    for (int i = 0; i < state->numberProcesses; i++)
    {
        if (getSumOfRow(state->allocatedResources[i], state->numberResources) != 0){
            finish[i] = 0;
        }
    }

    int posible = 1;
    while (posible)
    {
        int foundProcess = findProcess(finish, state->neededResources, state->allocatedResources, work, state->numberResources);
        if(foundProcess >= 0)
        {
            printf("TOFIX: foundProcess\n");
            getSumOfVectors(work, work, state->allocatedResources[foundProcess], state->numberResources); // Work = Work + Allocation[i][]
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
        { 
            printf("TOFIX: Estado inseguro\n");
            return 0; // Estado inseguro
        }
    }

    free(work);
    printf("TOFIX: Estado seguro\n");
    return 1; // Estado seguro
}