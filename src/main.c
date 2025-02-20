#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "system.h"
#include "utils.h"

// Variable global para almacenar la ruta del archivo
char *filePath = NULL;

// Obtiene los argumentos de la linea de comandos y los valida para que sean correctos
// @param argc Cantidad de argumentos
// @param argv Arreglo de argumentos
void getArguments(int argc, char *argv[])
{
    // Verifica que los argumentos sean correctos
    if (argc == 4 && strcmp(argv[1], "-m") == 0 && strcmp(argv[2], "d") == 0)
    {
        filePath = argv[3]; // Obtiene el nombre del archivo
        printf("El nombre del archivo es: %s\n", filePath);
    }
    else
    {
        // Si los argumentos no son válidos, imprime el formato correcto y termina el programa
        fprintf(stderr, "Error: Formato incorrecto.\nFormato correcto: ./deteccion -m d <nombre del archivo>\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    getArguments(argc, argv);
    // carga datos del sistemas desde un archivo
    System *system = initializeSystem();
    loadSystemFromFile(system, filePath);
    printSystem(system);    // Imprime el sistema
    freeUpMemory(system);   // Libera recursos
    return 0;
}
