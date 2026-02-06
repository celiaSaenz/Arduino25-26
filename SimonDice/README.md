# Proyecto: Simon Says (Simón Dice)

Este proyecto recrea el clásico juego de memoria electrónica **Simon Says**. El Arduino genera una secuencia aleatoria de luces y sonidos que el jugador debe repetir correctamente. A medida que avanzas, la secuencia se vuelve más larga y desafiante.

---

## Materiales

* **Arduino Uno** (o compatible)
* **4 LEDs** (Rojo, Amarillo, Azul, Verde)
* **4 Pulsadores** (Buttons)
* **4 Resistencias de 220Ω** (para proteger los LEDs)
* **1 Buzzer** (o transductor piezoeléctrico)
* Cables de conexión y Protoboard

---

## Requisitos

* **Arduino IDE** instalado.
* Conexión mediante cable USB a la placa.
* No requiere librerías externas (las frecuencias de las notas están definidas en el código).

---

## Cómo usar

1.  **Conexión de Hardware:**
    * **LEDs:** Conecta los ánodos a los pines digitales **12 (Rojo)**, **10 (Amarillo)**, **8 (Azul)** y **6 (Verde)**.
    * **Botones:** Conéctalos a los pines **13, 11, 9 y 7**. Nota: Van directos a GND ya que el código activa las resistencias `PULLUP` internas.
    * **Buzzer:** Conecta sus terminales a los pines **5** y **4**.
2.  Carga el código `.ino` en tu Arduino.
3.  **Inicio:** Al encenderse, verás una animación de luces. Pulsa cualquier botón para empezar la primera ronda.
4.  **Dinámica:** Observa la secuencia, escúchala y repítela.