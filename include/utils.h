#include "system.h"
// Cabeceras de las funciones y estructuras de utilidades
#ifndef UTILS_H
#define UTILS_H

// Función para imprimir el sistema
void printSystem(System *system);

// Función para imprimir el estado del sistema
void printState(State *state);

// Función para imprimir una matriz en forma de tabla
void printMatrix(const char *name, int **matrix, int rows, int cols);

// Función para imprimir un vector en formato [x1, x2, ..., xn]
void printVector(const char *name, int *vector, int size);
#endif
