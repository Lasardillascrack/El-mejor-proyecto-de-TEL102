# Proyecto (TEL-102)

Este proyecto consiste en el desarrollo de un juego de cartas inspirado en la mecánica de "Balatro", implementado en lenguaje C. El juego utiliza lógica matemática para el cálculo de puntajes basados en manos de póker y multiplicadores dinámicos.

## 1. Problemática
El desarrollo de juegos de azar y estrategia requiere una gestión precisa de la probabilidad y la estructura de datos. El problema abordado es la creación de un motor que reconozca combinaciones de cartas (manos) y aplique reglas matemáticas de puntuación de forma eficiente en un entorno de consola, permitiendo al usuario tomar decisiones estratégicas de descarte y juego.

## 2. Objetivos
* **Objetivo General:** Desarrollar una versión funcional de un de juego de cartas en C que procese jugadas y calcule puntajes mediante una lógica de multiplicadores.
* **Objetivos Específicos:**
    * Implementar un sistema de mazo y manos utilizando estructuras (`struct`) y punteros.
    * Diseñar algoritmos de barajado y reparto de cartas que aseguren aleatoriedad.
    * Validar jugadas básicas (Par, Trío, Color) y asignarles un puntaje matemático.

## 3. Integrantes y Roles
* **         ** Desarrollador.
* **         ** Desarrollador.
* **         ** Scrum Master.
* **         ** Product Owner.

## 4. Funcionalidades Implementadas (Hito 1)
* Estructura de datos para Cartas y Mazos.
* Función de inicialización y barajado de mazo de 52 cartas.
* Reparto de mano inicial (8 cartas) y visualización en consola.
* Selección de cartas por el usuario para jugar o descartar.

## 5. Casos de Prueba
| Entrada | Acción | Salida Esperada |
| :--- | :--- | :--- |
| `1` | Seleccionar carta 1 | La carta se marca como seleccionada para la mano actual. |
| `Jugar` | Ejecutar jugada de un Par | El sistema identifica el "Par" y otorga puntaje base x 2. |
| `Barajar` | Reiniciar mazo | El mazo se vuelve a generar en un orden aleatorio diferente. |

## 6. Instrucciones de Compilación y Ejecución
Para probar el programa, siga estos pasos en su terminal:
1.  Navegar a la carpeta del proyecto: `cd src/`
2.  Compilar: `gcc main.c -o game`
3.  Ejecutar: `./game`

## 7. Próximos Pasos (Hito 2)
* Implementar efectos de "Jokers" que modifiquen las estadísticas.
* Crear un sistema de "Tienda" para comprar mejoras entre rondas.
* Refinar la interfaz de usuario para una mejor experiencia de juego.
