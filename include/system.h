#include "process.h"
#ifndef SYSTEM_H
#define SYSTEM_H

// Cabeceras de las funciones y estructuras del sistema

// Estructura para representar el sistema
typedef struct {
    Process *processes;         // Vector de procesos
    int numberProcesses;        // Numero de procesos
    int numberResources;        // Numero de recursos
    int *totalResources;        // Vector de recursos totales
    int *availableResources;    // Vector de recursos disponibles
} System;

// Función para cargar un sistema desde un archivo
// @param system Puntero a la estructura de un sistema
// @param pathFile Ruta del archivo a cargar
void loadSystemFromFile(System *system,char *pathFile);

// Función para inicializar un sistema
// @return Puntero aun sistama inicializado
System* initializeSystem();

// Función para liberar los recursos reservados por un sistema
// @param system Puntero a la estructura de un sistema
void freeUpMemory(System *system);

// Función para simular que un proceso hace una solicitud de recursos
// @param system Puntero a la estructura de un sistema
void simulationResourcesRequest(System* system);

#endif