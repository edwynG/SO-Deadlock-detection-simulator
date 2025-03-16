#include "system.h"
#ifndef UTILS_H
#define UTILS_H

// Cabeceras de las funciones y estructuras de utilidades

// Función para imprimir el sistema
void printSystem(System *system);

// Función para imprimir el estado del sistema
void printState(State *state);

// Función para imprimir una matriz en forma de tabla
void printMatrix(const char *name, int **matrix, int rows, int cols);

// Función para imprimir un vector en formato [x1, x2, ..., xn]
void printVector(const char *name, int *vector, int size);

// Función para comparar cada entrada de dos vectores fila
int isLessThanVector(int *vectorA, int *vectorB, int n);

// Función para obtener un vector que sea la suma entre dos vectores
void getSumOfVectors(int *vectorSum, int *vectorA, int *vectorB, int n);

// Función para obtener un vector que sea la diferencia entre dos vectores
void getDiffOfVectors(int *vectorDiff, int *vectorA, int *vectorB, int n);

// Función para obtener la suma de todas las entradas de un vector fila
int getSumOfRow(int *vector, int n);
#endif
