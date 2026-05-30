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

## 5. Casos de Prueba
| Entrada | Acción | Salida Esperada |
| :--- | :--- | :--- |
| `Enter` | Robar una carta del mazo. | Se ejecuta `drawCard`. La carta en la posición `cardsDrawn` del mazo pasa a la mano. El contador de "Cartas en mano" aumenta (ej: de 1/5 a 2/5). |

## 6. Instrucciones de Compilación y Ejecución
Para probar el programa, siga estos pasos en su terminal:
1.  Navegar a la carpeta del proyecto: `cd src/`
2.  Compilar: `g++ main.cpp Jugador.cpp Mazo.cpp Carta.cpp -o Ardillatro`
3.  Ejecutar: `./Ardillatro`

## 7. Próximos Pasos (Hito 2)
* Implementar efectos de "Jokers" que modifiquen las estadísticas.
* Crear un sistema de "Tienda" para comprar mejoras entre rondas.
* Refinar la interfaz de usuario para una mejor experiencia de juego.
