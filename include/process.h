#ifndef PROCESS_H
#define PROCESS_H

// Cabeceras de las funciones y estructuras de procesos

// Estructura para representar un proceso
typedef struct
{
    int numberResources;     // Numero de recursos
    int *allocatedResources; // Vector de recursos asignados
    int *neededResources;    // Vector de recursos necesitados
    int priority;            // Prioridad del proceso
    char state;              // 'a' activo | 't' terminado | 'f' finalizado
} Process;

// Función para detener un proceso
// @param process Puntero al proceso
// @param state Estado del proceso 't' terminado | 'f' finalizado
void stopProcess(Process *process, char state);

#endif