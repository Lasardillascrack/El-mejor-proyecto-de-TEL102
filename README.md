# Ardillatro - Hito 3

## 1. Problemática y Objetivos
**Problemática:** Tradicionalmente, el desarrollo del pensamiento lógico-matemático en la educación técnica se ha visto limitado por métodos de enseñanza basados en la memorización de fórmulas y procedimientos mecánicos. Esta desconexión entre la teoría y la práctica impide que los estudiantes comprendan la estructura subyacente de los problemas, dificultando el análisis crítico y la toma de decisiones basada en datos.


**Objetivo General:** Implementar una versión funcional de Ardillatro con interfaz gráfica en C++ (Qt), logrando el desacoplamiento entre vista y dominio.

**Objetivos Específicos:**
* Refactorizar mediante punteros polimórficos.
* Parametrizar jugadas desde la interfaz.
* Integrar Signals y Slots de Qt.

## 2. Roles del Equipo
* **Scrum Master:** Gabriel Urbina
* **Product Owner:** Trinidad Silva
* **Developers:** Ignacio Espíndola, Antonia Flores

## 3. Evolución del Proyecto (Hito 1 a Hito 3)
* **Hito 1:** Desarrollo en C estructurado con arreglos estáticos y terminal lineal.
* **Hito 2:** Migración a C++ Orientado a Objetos (paso por valor).
* **Hito 3:** Implementación de herencia polimórfica (`carta` y `carta_normal`), gestión dinámica de memoria y despliegue de GUI con Qt.

## 4. Arquitectura y Separación Lógica-Interfaz
El proyecto cumple con el Principio de Responsabilidad Única. La Capa de Dominio (C++) procesa la matemática de los puntajes, mientras que la Capa de Interfaz (Qt) es completamente pasiva. La comunicación ocurre estrictamente mediante el patrón **Signals y Slots**.

## 5. Instrucciones de Ejecución y Pruebas
Ejemplo de uso:
1. Abrir la aplicación.
2. Seleccionar cartas haciendo clic en la interfaz.
3. Presionar "Jugar Mano".

## 6. Capturas de la Interfaz
<img width="1600" height="1092" alt="image" src="https://github.com/user-attachments/assets/dc22bca2-79fc-41aa-9674-f14110a24781" />
<img width="1600" height="1092" alt="image" src="https://github.com/user-attachments/assets/69fee47d-fb60-4b34-938e-2c47f21dbe3c" />



## 7. Dificultades y Conclusiones
* **Dificultades:** Lidiar con Memory Leaks al cambiar a punteros dinámicos y sincronizar los vectores de C++ con el `QTableWidget` de Qt.
* **Conclusiones:** Logramos aislar la interfaz del motor matemático, obteniendo un software robusto, interactivo y listo para futuras expansiones.
