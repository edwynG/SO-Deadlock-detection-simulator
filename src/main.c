#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "system.h"
#include "deadlock.h"
#include "utils.h"

// Variable global para almacenar la ruta del archivo
char *filePath = NULL;

// Obtiene los argumentos de la linea de comandos y los valida para que sean correctos
// @param argc Cantidad de argumentos
// @param argv Arreglo de argumentos
void getArguments(int argc, char *argv[])
{
    // Verifica que los argumentos sean correctos
    if (argc == 2)
    {
        filePath = argv[1]; // Obtiene el nombre del archivo
        printf("El nombre del archivo es: %s\n", filePath);
        return;
    }

    // Si los argumentos no son válidos, imprime el formato correcto y termina el programa
    fprintf(stderr, "Error: Formato incorrecto.\nFormato correcto: %s <nombre del archivo>\n", argv[0]);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    getArguments(argc, argv);

    // Carga datos del sistemas desde un archivo
    System *system = initializeSystem();
    loadSystemFromFile(system, filePath);
    // Inicia simulacion
    simulationResourcesRequest(system);
    freeUpMemory(system); // Libera recursos
    return 0;
}