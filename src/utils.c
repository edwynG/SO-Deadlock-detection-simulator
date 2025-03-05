#include <stdio.h>
#include "deadlock.h"
#include "system.h"
#include "utils.h"

void printSystem(System *system)
{
    if (system == NULL)
        return;

    // Imprimir los datos leídos (para verificar)
    printf("Numero de recursos: %d\n", system->numberResources);
    printf("Total recursos: ");
    for (int i = 0; i < system->numberResources; i++)
    {
        printf("%d ", system->totalResources[i]);
    }
    printf("\nRecursos asignados: ");
    for (int i = 0; i < system->numberResources; i++)
    {
        printf("%d ", system->availableResources[i]);
    }
    printf("\nNumero procesos: %d\n", system->numberProcesses);

    for (int i = 0; i < system->numberProcesses; i++)
    {
        printf("\nProcess %d:\n", i);
        printf("Estado: %c\n", system->processes[i].state);
        printf("  Recursos asignados: ");
        for (int j = 0; j < system->numberResources; j++)
        {
            printf("%d ", system->processes[i].allocatedResources[j]);
        }
        printf("\n  Recursos necesarios: ");
        for (int j = 0; j < system->numberResources; j++)
        {
            printf("%d ", system->processes[i].requiredResources[j]);
        }
        printf("\n  Prioridad: %d\n", system->processes[i].priority);
    }
    printf("\n");
}

void printVector(const char *name, int *vector, int size)
{
    if (vector == NULL || size == 0 || name == NULL)
    {
        return;
    }
    
    printf("%s: [", name);
    for (int i = 0; i < size; i++)
    {
        printf("%d", vector[i]);
        if (i < size - 1)
        {
            printf(", "); // Separador entre elementos
        }
    }
    printf("]\n");
}

void printMatrix(const char *name, int **matrix, int rows, int cols)
{
    if (matrix == NULL || rows == 0 || cols == 0 || name == NULL)
    {
        return;
    }
    
    printf("%s:\n", name);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", matrix[i][j]); // Imprime cada elemento de la matriz
        }
        printf("\n"); // Salto de línea al final de cada fila
    }
    printf("\n"); // Salto de línea adicional para separar matrices
}

void printState(State *state)
{
    if (state == NULL)
    {
        return;
    }
    printf("Estado del sistema:\n");
    // Imprimir el vector de recursos totales
    printVector("Vector de Recursos Totales", state->resourcesVector, state->numberResources);

    // Imprimir el vector de recursos disponibles
    printVector("Vector de Recursos Disponibles", state->availableVector, state->numberResources);

    printf("\n");
    // Imprimir la matriz de asignación
    printMatrix("Matriz de Asignación", state->AllocationMatrix, state->numberProcesses, state->numberResources);

    // Imprimir la matriz de necesidad
    printMatrix("Matriz de Necesidad", state->needMatrix, state->numberProcesses, state->numberResources);
}