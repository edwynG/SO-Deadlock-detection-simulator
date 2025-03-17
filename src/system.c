#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "deadlock.h"
#include "utils.h"

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
        system->processes[i].neededResources = (int *)malloc(system->numberResources * sizeof(int));

        // Leer recursos asignados
        for (int j = 0; j < system->numberResources; j++)
        {
            fscanf(file, "%d", &system->processes[i].allocatedResources[j]);
        }
        fscanf(file, " |"); // Lee el pipe("|") para omitirlo

        // Leer recursos necesarios
        for (int j = 0; j < system->numberResources; j++)
        {
            fscanf(file, "%d", &system->processes[i].neededResources[j]);
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
        free(system->processes[i].neededResources);
    }
    free(system->processes);
    free(system->totalResources);
    free(system->availableResources);
}

void simulationResourcesRequest(System *system){
    State *state = getState(system);
    printSystem(system);  // Imprime el sistema
    printState(state);    // Imprime estado del sistema

    // Simulacion
    for (int i = 0; i < state->numberProcesses; i++)
    {
        printf("TOFIX: Simulando solicitud para el proceso %d:\n", i);
        
        // Obtener la petición del proceso
        int *Request = (int *)malloc(state->numberResources * sizeof(int));
        getDiffOfVectors(Request, state->neededResources[i], state->allocatedResources[i], state->numberResources);
        printVector("TOFIX: Petición del proceso", Request, state->numberResources);
        
        // Verificar si petición del proceso excede su necesidad declarada
        int *sum = (int *)malloc(state->numberResources * sizeof(int)); // Sum
        getSumOfVectors(sum, state->allocatedResources[i], Request, state->numberResources); // Sum = Allocation[i][] + Request
        if (!isLessEqualThanVector(sum, state->neededResources[i], state->numberResources)) // Sum > Need[i][]
        {
            fprintf(stderr, "Petición del proceso %d excede su necesidad declarada.\n", i);
            free(sum);
            continue; // Pasar al siguiente proceso
        }
        free(sum);

        // Verificar si recursos no están disponibles
        if (!isLessEqualThanVector(Request, state->availableResources, state->numberResources)) // Request > Available
        {
            fprintf(stderr, "Petición del proceso %d no está disponible.\n", i);
            continue; // Pasar al siguiente proceso
        }
        
        // Simular la asignación
        printf("TOFIX: Simular la asignación\n");
        State *simulatedState = getCopyOfState(state);
        getDiffOfVectors(simulatedState->availableResources, state->availableResources, Request, state->numberResources); // Available = Available - Request
        getSumOfVectors(simulatedState->allocatedResources[i], state->allocatedResources[i], Request, state->numberResources); // Allocation[i][] = Allocation[i][] + Request

        if (isStateSafe(simulatedState)) // Llevar a cabo la asignación en el estado real
        {
            printf("TOFIX: Llevar a cabo la asignación en el estado real\n");
            getDiffOfVectors(state->availableResources, state->availableResources, Request, state->numberResources); // Available = Available - Request
            getSumOfVectors(state->allocatedResources[i], state->allocatedResources[i], Request, state->numberResources); // Allocation[i][] = Allocation[i][] + Request
        }
        else
        {
            printf("La asignación al proceso %d llevaría a un estado inseguro. Petición rechazada.\n", i);
            // Suspender proceso P_i 
        }

        // Liberar la memoria del estado simulado
        printf("TOFIX: free\n");
        free(simulatedState->availableResources);
        for (int i = 0; i < state->numberResources; i++) {
            free(simulatedState->allocatedResources[i]);
        }
        free(simulatedState->allocatedResources);

        printState(state);
    }
    isStateSafe(state);
}