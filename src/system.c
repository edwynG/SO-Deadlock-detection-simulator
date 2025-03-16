#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "deadlock.h"

void loadSystemFromFile(System *system, char *pathFile)
{
    if (system == NULL || pathFile == NULL)
    {
        fprintf(stderr, "Error: Referencias nulas al cargar el sistema.\n"); // Indica mensaje de error
        exit(EXIT_FAILURE); // Detiene el programa
    }

    FILE *file = fopen(pathFile, "r");
    // En caso de que no se pueda abrir el archivo se detiene el programa
    if (file == NULL)
    {
        fprintf(stderr, "Error: No se pudo abrir el archivo.\n"); // Indica mensaje de error
        exit(EXIT_FAILURE);                                     // Detiene el programa
    }

    // Leer número de recursos (N)
    fscanf(file, "%d", &system->numberResources);

    // Reservar memoria para los vectores de recursos
    system->totalResources = (int *)malloc(system->numberResources * sizeof(int));
    system->availableResources = (int *)malloc(system->numberResources * sizeof(int));

    // Leer vector de recursos totales
    for (int i = 0; i < system->numberResources; i++)
    {
        fscanf(file, "%d", &system->totalResources[i]);
    }

    // Leer vector de recursos disponibles
    for (int i = 0; i < system->numberResources; i++)
    {
        fscanf(file, "%d", &system->availableResources[i]);
    }

    // Leer número de procesos (M)
    fscanf(file, "%d", &system->numberProcesses);

    // Reservar memoria para los procesos
    system->processes = (Process *)malloc(system->numberProcesses * sizeof(Process));

    // Leer datos de cada proceso
    for (int i = 0; i < system->numberProcesses; i++)
    {
        system->processes[i].allocatedResources = (int *)malloc(system->numberResources * sizeof(int));
        system->processes[i].requestedResources = (int *)malloc(system->numberResources * sizeof(int));

        // Leer recursos asignados
        for (int j = 0; j < system->numberResources; j++)
        {
            fscanf(file, "%d", &system->processes[i].allocatedResources[j]);
        }
        fscanf(file, " |"); // Lee el pipe("|") para omitirlo

        // Leer recursos necesarios
        for (int j = 0; j < system->numberResources; j++)
        {
            fscanf(file, "%d", &system->processes[i].requestedResources[j]);
        }

        fscanf(file, " |"); // Lee el pipe("|") para omitirlo

        // Leer prioridad
        fscanf(file, "%d", &system->processes[i].priority);
        system->processes[i].state = 'a'; // Inicializa el estado del proceso como activo
    }

    fclose(file);
}

System *initializeSystem()
{
    // Asigna memoria para inicializar sistema
    System *system = (System *)malloc(sizeof(System));
    if (system == NULL)
    {
        fprintf(stderr, "Error: No se pudo asignar memoria para el sistema.\n");
        exit(EXIT_FAILURE);
    }
    system->numberProcesses = 0;
    system->numberResources = 0;
    system->processes = NULL;
    system->totalResources = NULL;
    system->availableResources = NULL;

    return system;
}

void freeUpMemory(System *system)
{
    if (system == NULL)
        return;

    for (int i = 0; i < system->numberProcesses; i++)
    {
        free(system->processes[i].allocatedResources);
        free(system->processes[i].requestedResources);
    }
    free(system->processes);
    free(system->totalResources);
    free(system->availableResources);
}

void simulationResourcesRequest(System* system){
    State* state = getState(system);
    printSystem(system);  // Imprime el sistema
    printState(state);    // Imprimer estado del sistema
    isStateSafe(state);

    // if Request[i][] > Need[i][]:
    //     error()
    // elif Request[i][] > Work:
    //     suspenderProceso()
    // else: 
    //     # Simulacion
    //     nuevoEstado = {
    //             Work = Work - Request[i][] # Asignar recursos
    //             Allocation[i][] = Allocation[i][] + Request[i][]
    //     }
    // if esSeguro(nuevoEstado):
    //         asignacionReal()
    // else:
    //         restaurarEstadoOriginal()
    //         suspenderProceso()
}