# Simulador de prevención de interbloqueo

El propósito de este proyecto es desarrollar un simulador implementado en **C** que implemente un algoritmo de prevención de interbloqueo (deadlock). Un algoritmo usual para la prevención del interbloqueo es el del banquero.

> **NOTA**: El algoritmo se puede encontrar con más detalle en el libro de William Stallings en la página 269 
> aproximadamente o el Silberschatz en la página 229 aproximadamente.

## Objetivos específicos

1. Entender y explicar el funcionamiento del algoritmo de detección de interbloqueo.
2. Diseñar y programar un simulador que permita visualizar el proceso de prevención de interbloqueo.
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
│   └── ...             # Casos de prueba
├── obj/                # Archivos objeto(se genera en el build)
├── bin/                # Ejecutables(build)
├── Makefile            # Archivo makefile
└── README.md           # Este archivo
```

## Colaboradores

- **Samantha Ramirez**
- **Edwyn Guzmán**