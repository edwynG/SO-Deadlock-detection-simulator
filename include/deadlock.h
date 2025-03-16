#include "system.h"
#ifndef DEADLOCK
#define DEADLOCK

// Cabeceras para las funciones y estructuras relaciondas con la prevención de interbloqueo

// Estructura para representar el estado del sistema forma de vectores y matrices
typedef struct
{
    int numberProcesses;    // Cantidad de procesos
    int numberResources;    // Cantidad de recursos
    int *totalResources;   // Vector de recursos totales
    int *availableResources;   // Vector de recursos disponibles
    int **neededResources;       // Matriz de necesidad (cantidad máxima de un recurso que cada proceso pueda necesitar)
    int **allocatedResources; // Matriz de asignacion
} State;

// Funcion para obtener referencia del estado actual del sistema en forma de matrices y vectores
// @param system Puntero a la estructura de un sistema
// @return Puntero al estado actual del sistema
State *getState(System *system);

// Funcion para verificar si el estado actual del sistema es seguro
// @param state Puntero al estado actual del sistema
// @return 1 si es seguro, 0 si no lo es
int isStateSafe(State *state);

#endif