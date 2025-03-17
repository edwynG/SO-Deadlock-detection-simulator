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

// State *getCopyOfState(State *originalState)
// {
//     if (originalState == NULL)
//     {
//         return NULL;
//     }

//     State *newState = (State *)malloc(sizeof(State));
//     if (newState == NULL)
//     {
//         perror("Error al asignar memoria para newState");
//         return NULL;
//     }

//     // Copiar miembros simples
//     newState->numberProcesses = originalState->numberProcesses;
//     newState->numberResources = originalState->numberResources;
//     newState->processes = originalState->processes;

//     // Copiar arrays de enteros
//     newState->totalResources = (int *)malloc(originalState->numberResources * sizeof(int));
//     if (newState->totalResources == NULL)
//     {
//         perror("Error al asignar memoria para totalResources");
//         free(newState);
//         return NULL;
//     }
//     memcpy(newState->totalResources, originalState->totalResources, originalState->numberResources * sizeof(int));

//     newState->availableResources = (int *)malloc(originalState->numberResources * sizeof(int));
//     if (newState->availableResources == NULL)
//     {
//         perror("Error al asignar memoria para availableResources");
//         free(newState->totalResources);
//         free(newState);
//         return NULL;
//     }
//     memcpy(newState->availableResources, originalState->availableResources, originalState->numberResources * sizeof(int));

//     // Copiar matrices de enteros
//     newState->allocatedResources = (int **)malloc(originalState->numberProcesses * sizeof(int *));
//     if (newState->allocatedResources == NULL)
//     {
//         perror("Error al asignar memoria para allocatedResources");
//         free(newState->totalResources);
//         free(newState->availableResources);
//         free(newState);
//         return NULL;
//     }
//     for (int i = 0; i < originalState->numberProcesses; i++)
//     {
//         newState->allocatedResources[i] = (int *)malloc(originalState->numberResources * sizeof(int));
//         if (newState->allocatedResources[i] == NULL)
//         {
//             perror("Error al asignar memoria para allocatedResources[i]");
//             // Limpiar la memoria asignada previamente
//             for (int j = 0; j < i; j++)
//             {
//                 free(newState->allocatedResources[j]);
//             }
//             free(newState->allocatedResources);
//             free(newState->totalResources);
//             free(newState->availableResources);
//             free(newState);
//             return NULL;
//         }
//         memcpy(newState->allocatedResources[i], originalState->allocatedResources[i], originalState->numberResources * sizeof(int));
//     }

//     newState->neededResources = (int **)malloc(originalState->numberProcesses * sizeof(int *));
//     if (newState->neededResources == NULL)
//     {
//         perror("Error al asignar memoria para neededResources");
//         // Limpiar la memoria asignada previamente
//         for (int i = 0; i < originalState->numberProcesses; i++)
//         {
//             free(newState->allocatedResources[i]);
//         }
//         free(newState->allocatedResources);
//         free(newState->totalResources);
//         free(newState->availableResources);
//         free(newState);
//         return NULL;
//     }
//     for (int i = 0; i < originalState->numberProcesses; i++)
//     {
//         newState->neededResources[i] = (int *)malloc(originalState->numberResources * sizeof(int));
//         if (newState->neededResources[i] == NULL)
//         {
//             perror("Error al asignar memoria para neededResources[i]");
//             // Limpiar la memoria asignada previamente
//             for (int j = 0; j < i; j++)
//             {
//                 free(newState->neededResources[j]);
//             }
//             for (int j = 0; j < originalState->numberProcesses; j++)
//             {
//                 free(newState->allocatedResources[j]);
//             }
//             free(newState->allocatedResources);
//             free(newState->neededResources);
//             free(newState->totalResources);
//             free(newState->availableResources);
//             free(newState);
//             return NULL;
//         }
//         memcpy(newState->neededResources[i], originalState->neededResources[i], originalState->numberResources * sizeof(int));
//     }

//     return newState;
// }

// void freeState(State *state)
// {
//     if (state == NULL)
//     {
//         return;
//     }

//     free(state->totalResources);
//     free(state->availableResources);

//     for (int i = 0; i < state->numberProcesses; i++)
//     {
//         free(state->allocatedResources[i]);
//         free(state->neededResources[i]);
//     }

//     free(state->allocatedResources);
//     free(state->neededResources);
//     free(state);
// }

int findProcess(int *finish, int **neededResources, int **allocatedResources, int *work, int row, int col)
{
    printf("TOFIX: find\n");
    printVector("Finalizados", finish, row);
    printVector("Disponible", work, col);
    for (int i = 0; i < row; i++)
    {
        int *diff = (int *)malloc(col * sizeof(int));

        getDiffOfVectors(diff, neededResources[i], allocatedResources[i], col); // Diff = Need[i][] - Allocation[i][]
        printVector("proceso", diff, col);
        if (finish[i] == 0 && isLessEqualThanVector(diff, work, col)) // Diff <= Work
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
            printf("%d\n", foundProcess);
            if (foundProcess >= 0)
            {
                printf("TOFIX: foundProcess\n");
                getSumOfVectors(work, work, state->allocatedResources[foundProcess], state->numberResources); // Work = Work + Allocation[i][]
                finish[foundProcess] = 1;
                stopProcess(&state->processes[foundProcess], 'f'); // Finalizar proceso
                if (secuence != NULL)
                {
                    // orden de ejecución
                    secuence[count] = foundProcess;
                    count++;
                }
            }
            else
            {
                posible = 0;
            }
        }

        if (all(finish, state->numberProcesses)) // Verifica si los procesos finaizaron
        {
            break;
        }

        printf("TOFIX: Estado inseguro\n");

        for (int i = 0; i < state->numberResources; i++)
        {
            if (finish[i] == 1)
            {
                printf("%d\n", i);
            }
        }

        int select = handlerDeadlock(state);
        getSumOfVectors(work, work, state->allocatedResources[select], state->numberResources); // Work = Work + Allocation[i][]
        stopProcess(&state->processes[select], 't');

        finish[select] = 1;
        printf("P%d %c\n", select, state->processes[select].state);
        if (secuence != NULL)
        {
            // orden de ejecución
            secuence[count] = select;
            count++;
        }
        isSafe = 0;
    } while (1);

    printf("TOFIX: Estado seguro\n");
    printState(state);
    return isSafe; // Estado seguro
}

int handlerDeadlock(State *state)
{

    printf("Es un estado inseguro\n");
    printf("Procesos involucrados ");
    for (int i = 0; i < state->numberProcesses; i++)
    {
        if (state->processes[i].state == 'a')
        {
            printf("%d ", i);
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
    } while (option != 1 && option != 2);

    return -1;
}