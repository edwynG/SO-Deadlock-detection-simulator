#include "system.h"
// Cabeceras para las funciones y estructuras relaciondas con la prevención de interbloqueo
#ifndef DEADLOCK
#define DEADLOCK
// Estructura para reprensetar el estado del sistema forma de vectores y matrices
typedef struct
{
    int *resourcesVector;   // Vector de recursos totales
    int *availableVector;   // Vector de recursos disponibles
    int **AllocationMatrix; // Matriz de asignacion
    int **needMatrix;       // Matriz de necesidad
    int numberProcesses;    // cantidad de procesos
    int numberResources;    // cantidad de recursos
} State;

// Funcion para obtener rreferencia del estado actual del sistema en forma de matrices y vectores
// @param system  Puntero a la estructura de un sistema
// @return  Puntero al estado actual del sistema
State *getState(System *system);

// Funcion para verificar si el estado actual del sistema es seguro
// @param state  Puntero al estado actual del sistema
// @return  1 si es seguro, 0 si no lo es
int isStateSegure(State *state);

#endif