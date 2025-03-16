#ifndef PROCESS_H
#define PROCESS_H

// Cabeceras de las funciones y estructuras de procesos

// Estructura para representar un proceso
typedef struct {
    int *allocatedResources;    // Vector de recursos asignados
    int *neededResources;     // Vector de recursos necesitados
    int priority;               // Prioridad del proceso
    char state;                 // 'a' activo | 't' terminado | 'f' finalizado  
} Process;

#endif