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
    currentState->processes = system->processes;

    currentState->allocatedResources = (int **)malloc(system->numberProcesses * sizeof(int *));
    currentState->neededResources = (int **)malloc(system->numberProcesses * sizeof(int *));

    for (int i = 0; i < system->numberProcesses; i++)
    {
        currentState->allocatedResources[i] = system->processes[i].allocatedResources;
        currentState->neededResources[i] = system->processes[i].neededResources;
    }

    return currentState;
}

int findProcess(int *finish, int **neededResources, int **allocatedResources, int *work, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        int *diff = (int *)malloc(col * sizeof(int));
        getDiffOfVectors(diff, neededResources[i], allocatedResources[i], col); // Diff = Need[i][] - Allocation[i][]
        if (finish[i] == 0 && isLessEqualThanVector(diff, work, col))           // Diff <= Work
        {
            return i;
        }
    }
    return -1;
}

int isStateSafe(State *state, int *secuence)
{
    int isSafe = 1;
    int count = 0;
    int *work = state->availableResources;
    int *finish = (int *)malloc(state->numberProcesses * sizeof(int));

    // No finalizados
    for (int i = 0; i < state->numberProcesses; i++)
    {
        finish[i] = 0;
    }

    do
    {
        int posible = 1;
        while (posible)
        {
            // Busca proceso que se pueda satisfacer
            int foundProcess = findProcess(finish, state->neededResources, state->allocatedResources, work, state->numberProcesses, state->numberResources);
            if (foundProcess >= 0)
            {
                getSumOfVectors(work, work, state->allocatedResources[foundProcess], state->numberResources); // Work = Work + Allocation[i][]
                stopProcess(&state->processes[foundProcess], 'f');                                            // Finalizar proceso
                finish[foundProcess] = 1;

                if (secuence != NULL)
                {
                    // Orden de ejecución
                    secuence[count] = foundProcess;
                    count++;
                }
            }
            else
            {
                posible = 0;
            }
        }

        if (all(finish, state->numberProcesses)) // Verifica si todos los procesos finalizaron
        {
            break;
        }

        // Permite al usuario gestionar el interbloqueo
        int select = handlerDeadlock(state);
        getSumOfVectors(work, work, state->allocatedResources[select], state->numberResources); // Work = Work + Allocation[i][]
        stopProcess(&state->processes[select], 't');
        finish[select] = 1; // Indica que se detuvo
        if (secuence != NULL)
        {
            // Orden de ejecución
            secuence[count] = select;
            count++;
        }
        isSafe = 0; // Indica que el estado ha sido inseguro
    } while (1);

    return isSafe;
}

int handlerDeadlock(State *state)
{

    printf("Es un estado inseguro\n");
    printf("Procesos involucrados ");
    for (int i = 0; i < state->numberProcesses; i++)
    {
        if (state->processes[i].state == 'a')
        {
            printf("P%d ", i);
        }
    }
    printf("\n");
    printf("Recursos disponibles ");
    for (int i = 0; i < state->numberResources; i++)
    {
        printf("%d ", state->availableResources[i]);
    }
    printf("\n");

    char option;
    do
    {
        printf("1: Finalizar simulación\n");
        printf("2: Terminar proceso con menor prioridad\n");
        scanf("%c", &option);
        getchar();
        switch (option)
        {
        case '1':
            exit(EXIT_SUCCESS);
            break;
        case '2':
            int minPriority = -1;
            int minPriorityIndex = -1;
            for (int i = 0; i < state->numberProcesses; i++)
            {
                if (state->processes[i].state == 'a' && state->processes[i].priority > minPriority)
                {
                    minPriority = state->processes[i].priority;
                    minPriorityIndex = i;
                }
            }
            return minPriorityIndex;
        default:
            break;
        }
    } while (option != '1' && option != '2');

    return -1;
}