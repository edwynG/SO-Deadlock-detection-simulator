#include <stdio.h>
#include "system.h"

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
        printf("Process %d:\n", i);
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
}