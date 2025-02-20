#include "process.h"

// Cabeceras de las funciones y estructuras del sistema
#ifndef SYSTEM_H
#define SYSTEM_H
// Estructura para representar el sistema
typedef struct {
    int numberResources;        // Numero de recursos
    int *totalResources;        // Vector recursos totales
    int *availableResources;    // Vector recursos disponibles
    int numberProcesses;        // Numero de procesos
    Process *processes;         // Vector de procesos
} System;

// Funcion para cargar un sistema desde un archivo
// @param system  Puntero a la estructura de un sistema
// @param pathFile  Ruta del archivo a cargar
void loadSystemFromFile(System *system,char *pathFile);

// Funcion para inicializar un sistema
// @return  Puntero aun sistama inicializado
System* initializeSystem();

// Funcion para liberar los recursos reservados por un sistema
// @param system  Puntero a la estructura de un sistema
void freeUpMemory(System *system);

#endif