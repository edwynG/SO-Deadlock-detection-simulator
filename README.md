# Simulador de detección de interbloqueo

El propósito de este proyecto es desarrollar un simulador implementado en **C** que implemente un algoritmo de detección de interbloqueo (deadlock). Un algoritmo usual para la detección del interbloqueo es el que se describe en [COFF71].

> **NOTA**: El algoritmo se puede encontrar con más detalle en el libro de William Stallings en la página 275 
> aproximadamente o el Silberschatz en la página 233 aproximadamente.

## Objetivos específicos

1. Entender y explicar el funcionamiento del algoritmo de detección de interbloqueo.
2. Diseñar y programar un simulador que permita visualizar el proceso de detección de interbloqueo.
3. Probar el simulador con diferentes escenarios para verificar su correcto funcionamiento.
4. Documentar el diseño y el uso del simulador.

## Estructura del proyecto

La estructura del proyecto es la siguiente:

```{html}
mi_proyecto/
├── src/                # Código fuente
│   ├── main.c          # Punto de entrada del programa
│   └── ...             # Otros módulos
├── include/            # Archivos de cabecera
│   └── ...             # Declaraciones de funciones y estructuras
├── tests/              # Archivos de pruebas
│   └── ...             # Pruebas unitarias
├── obj/                # Archivos objeto(se genera en el build)
├── bin/                # Ejecutables(build)
├── Makefile            # Archivo makefile
└── README.md           # Este archivo
```

## Colaboradores

- **Samantha Ramirez**
- **Edwyn Guzmán**