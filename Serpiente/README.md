# Proyecto: Juego de la Serpiente (Snake)

Este proyecto recrea el legendario juego **Snake** utilizando una **Matriz de LEDs 8x8** y un **Joystick**. El objetivo es controlar la serpiente para comer los puntos de "alimento" que aparecen aleatoriamente, lo que hace que la serpiente crezca. Si la serpiente choca contra su propio cuerpo, el juego termina.

---

## Materiales

* **Arduino Uno**
* **Matriz de LEDs 8x8** con driver MAX7219
* **Joystick analógico** (Módulo KY-023)
* **Cables de conexión** (Jumpers)
* **Protoboard**



---

## Requisitos

* **Arduino IDE**
* Librería **LedControl** instalada.
* Placa Arduino Uno o compatible.

---

## Cómo usar

1.  **Conexión del Hardware:**
    * **Matriz LED (MAX7219):**
        * CLK ➔ Pin **11**
        * DIN ➔ Pin **12**
        * CS ➔ Pin **10**
    * **Joystick:**
        * VRx ➔ Pin analógico **A0**
        * VRy ➔ Pin analógico **A1**
        * SW (Botón) ➔ Pin digital **2**
2.  Carga el código en tu placa Arduino.
3.  **Funcionamiento:**
    * Mueve el Joystick para dar dirección a la serpiente.
    * Cada vez que comas un punto, tu puntaje y tamaño aumentarán.
    * Si atraviesas una pared, aparecerás por el lado opuesto (sistema de bordes infinitos).
    * Si chocas contigo mismo, la pantalla se llenará de luces indicando **Game Over** y el juego se reiniciará.

---

## Explicación Técnica

Este proyecto es un ejemplo complejo de gestión de memoria (arrays) y lógica de colisiones.

### Conceptos clave del código:

* **Gestión de la Cola (`tailX` / `tailY`):**
    Para que la serpiente "crezca", el código utiliza dos arrays que almacenan las posiciones anteriores de la cabeza. En cada movimiento, la posición `0` recibe la ubicación de la cabeza y el resto de los segmentos se desplazan una posición atrás.
    ```cpp
    int tailX[100], tailY[100]; // Permite una serpiente de hasta 100 segmentos
    ```

* **Lógica de Bordes Infinitos:**
    En lugar de perder al tocar la pared, la función `manageSnakeOutOfBounds()` detecta si la coordenada supera el límite (0-7) y la teletransporta al extremo opuesto mediante una validación simple:
    ```cpp
    if (snakeX >= screenWidth) snakeX = 0;
    ```

* **Control de Dirección por Umbrales:**
    Al igual que en proyectos anteriores, el **ADC** convierte el voltaje del joystick en valores de **0 a 1023**. Para evitar movimientos accidentales, el código define "zonas muertas", detectando movimiento solo en los extremos (menor a 100 o mayor a 1000).



* **Renderizado Dinámico (`drawSnake`):**
    En lugar de encender solo un punto, la función recorre toda la matriz en cada frame (cada 300ms) comprobando tres condiciones: ¿Es la cabeza?, ¿Es la comida? o ¿Es parte de la cola? Si no es ninguna, apaga el LED.

---