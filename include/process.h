// Cabeceras de las funciones y estructuras de procesos
#ifndef PROCESS_H
#define PROCESS_H
// Estructura para representar un proceso
typedef struct {
    int *allocatedResources;    // vector de recursos asignados
    int *requiredResources;     // vector de recursos necesarios para la ejecucion
    int priority;               // Prioridad del proceso
} Process;

#endif