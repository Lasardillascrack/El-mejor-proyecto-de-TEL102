# Ardillatro

Este proyecto consiste en el desarrollo de un juego de cartas inspirado en la mecánica de "Balatro", refactorizado íntegramente a **C++** utilizando el paradigma de **Programación Orientada a Objetos (POO)** para el Hito 2.

## 1. Problemática
Tradicionalmente, el desarrollo del pensamiento lógico-matemático en la educación técnica se ha visto limitado por métodos de enseñanza basados en la memorización de fórmulas y procedimientos mecánicos. Esta desconexión entre la teoría y la práctica impide que los estudiantes comprendan la estructura subyacente de los problemas, dificultando el análisis crítico y la toma de decisiones basada en datos.

## 2. Objetivos
* **Objetivo General:** Desarrollar una versión funcional y orientada a objetos de un juego de cartas interactivo en C++ que procese jugadas, calcule puntajes mediante una lógica combinatoria de multiplicadores y evalúe el progreso a través de niveles de dificultad escalares.
* **Objetivos Específicos:**
    * Migrar la arquitectura de datos estructurada a un diseño POO para garantizar el encapsulamiento.
    * Diseñar algoritmos combinatorios para detectar con precisión jerarquías matemáticas de póker.
    * Implementar un sistema de control de recursos limitados (manos y descartes máximos por nivel).

## 3. Integrantes y Roles
* **Ignacio Espindola** Desarrollador.
* **Antonia Flores** Desarrollador.
* **Gabriel Urbina** Scrum Master.
* **Trinidad Silva** Product Owner.

## 4. Funcionalidades Implementadas (Hito 2)
* Estructura de datos en clases independientes.
* Uso de librería estandar para manejar una memoria de forma automática y revisar que no haya cartas repetidas. 
* Reparto de mano inicial de 8 cartas.
* Selección libre de hasta 5 cartas de la mano para ser jugadas o descartadas.
* Sistema de cálculo del puntaje que permite mantener la mayor puntuación.
* Límite de 3 intentos para lograr un objetivo
* Un total de 5 niveles para superar puntajes y mejorar habilidades.

  ## 5. Cambios estructurales 
* De arreglos fijos a vectores dinámicos.
* De struct a clases
* De variables globales a encapsulamiento.
* Mapeo de datos.
* Flujo de consola limpios.

## 6. Clases creadas y sus relaciones 
* Carta: Representa un naipe que contiene atributos privados (pinta, valor y puntos) y funciones públicas para consultar datos.
* Mazo: Administra el conjunto de 52 cartas que contiene un vector privado de objeto tipo carta. Tiene la función de barajar y entregar cartas de una en una.
* Jugador: Administra la mano actual y el estado del juego. Contiene un vector privado que almacena un máximo de 8 cartas.
* Se utiliza una relación de composición, el mazo se compone de objetos Carta y el Jugador se compone de un conjunto dinámico de cartas en su mano. El archivo main.ccp coordina y comunica al mazo con el jugador.

## 7. Casos de Prueba
| Acción | Entrada del Usuario | Resultado del Sistema |
| :--- | :--- | :--- |
| Descarte | `d` -> `1` -> Enter | El sistema valida la entrada, invoca `descartarPorIndice()`, remueve la carta del `Jugador`, roba una del `Mazo` y reduce el contador de descartes. |
| Jugar Mano | `j` -> índices (ej: 0,1,2,3,4) | Se invoca `evaluarJugadaExacta()`. El motor detecta la combinación matemática, multiplica fichas base e imprime el puntaje acumulado. |

**Ejemplo de Salida en Terminal:**
```
================ RESULTADO =====================
Jugada Detectada: Color
Puntos de las Cartas: +45 fichas
Matemática: 80 Fichas x 4 Mult
PUNTAJE DE ESTA MANO: 320
================================================
>>> ¡NIVEL 1 COMPLETADO! <<<
```
## 8. Instrucciones de Compilación y Ejecución
Para probar el programa, siga estos pasos en su terminal:
1.  Navegar a la carpeta del proyecto: `cd src/`
2.  Compilar: `g++ main.cpp Jugador.cpp Mazo.cpp Carta.cpp -o Ardillatro`
3.  Ejecutar: `./Ardillatro`
   
## 9. Dificultades
* ​La mayor dificultad algorítmica apareció al programar la eliminación consecutiva de cartas en un mismo turno dentro de un vector dinámico.
Si el usuario seleccionaba borrar las cartas de los índices 1 y 3, y el código borraba primero el índice 1, todas las cartas restantes de la mano se movían de inmediato una posición hacia la izquierda. Esto provocaba que la carta que originalmente estaba en el índice 3 pasara al índice 2, por lo que al ejecutar el segundo borrado eliminábamos una carta equivocada.
​Solución: Modificamos la función en la clase Jugador para guardar los índices seleccionados en un vector temporal. Aplicamos el comando std::sort junto con std::greater para ordenar esos números obligatoriamente de mayor a menor. Al borrar las cartas empezando desde el índice más alto hacia el más bajo, las posiciones de las cartas de la izquierda no sufren alteraciones, resolviendo el problema por completo.

## 10. Próximos Pasos (Hito 3)
* 
## 11. Anexos y Referencias
