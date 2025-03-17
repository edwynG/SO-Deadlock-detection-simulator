#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "deadlock.h"
#include "process.h"
#include "utils.h"

void loadSystemFromFile(System *system, char *pathFile)
{
    if (system == NULL || pathFile == NULL)
    {
        fprintf(stderr, "Error: Referencias nulas al cargar el sistema.\n"); // Indica mensaje de error
        exit(EXIT_FAILURE);                                                  // Detiene el programa
    }

    FILE *file = fopen(pathFile, "r");
    // En caso de que no se pueda abrir el archivo se detiene el programa
    if (file == NULL)
    {
        fprintf(stderr, "Error: No se pudo abrir el archivo.\n"); // Indica mensaje de error
        exit(EXIT_FAILURE);                                       // Detiene el programa
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
        system->processes[i].numberResources = system->numberResources;
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

void simulationResourcesRequest(System *system)
{
    State *state = getState(system);
    printState(state);
    // Este arreglo va a tener el orden de los procesos que se van a ejecutar
    int *secuence = (int *)malloc(sizeof(int) * state->numberProcesses);
    for (int i = 0; i < state->numberProcesses; i++)
    {
        secuence[i] = -1;
    }
    // Simulacion
    int isSafe = isStateSafe(state, secuence);
    
    for (int i = 0; i < state->numberProcesses; i++)
    {
        printf("%d\n", secuence[i]);
    }

    printf("%s\n", isSafe == 1 ? "Es un estado es seguro" : "Hubo un estado inseguro");
    printf("Estado de los procesos:\n");
    for (int i = 0; i < state->numberProcesses; i++)
    {
        if (state->processes[secuence[i]].state == 'f')
        {
            printf("P%d Finalizado\n", secuence[i]);
        }

        if (state->processes[secuence[i]].state == 't')
        {
            printf("P%d Terminado\n", secuence[i]);
        }
    }
    printf("Orden de asignación de recursos:\n");
    for (int i = 0; i < state->numberProcesses; i++)
    {
        if (state->processes[secuence[i]].state == 'f')
        {
            printf("P%d", secuence[i]);
        }

        if (state->processes[secuence[i]].state == 't')
        {
            printf("P%d Terminado", secuence[i]);
        }

        if (i != state->numberProcesses - 1)
        {
            printf(", ");
        }
    }
    printf("\n");
    free(secuence);
}