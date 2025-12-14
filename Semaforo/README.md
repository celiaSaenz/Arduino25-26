# Proyecto: Creación de Semáforo Simple

Este ejercicio simula el funcionamiento básico de un semáforo utilizando tres LEDs (Rojo, Amarillo y Verde).
El objetivo es reforzar el uso de **arreglos (arrays)** para gestionar múltiples pines y controlar tiempos de encendido y apagado.

---

## Materiales

- Arduino Uno
- 1 LED Rojo, 1 LED Amarillo, 1 LED Verde
- 3 Resistencias de 220Ω
- Cables de conexión
- Protoboard

---

## Requisitos

- Arduino IDE
- Placa Arduino Uno

---

## Cómo usar

1. Conecta los LEDs a los siguientes pines (ánodo al pin, cátodo a GND con resistencia):
   - **Rojo:** Pin 3
   - **Amarillo:** Pin 4
   - **Verde:** Pin 5
2. Carga el código en tu Arduino Uno.
3. Observa la secuencia de luces.

---

## Explicación

- **Arreglos (`int leds[] = {3, 4, 5}`):** Permite agrupar los pines de los LEDs.
    - `leds[0]` corresponde al Rojo (Pin 3).
    - `leds[1]` corresponde al Amarillo (Pin 4).
    - `leds[2]` corresponde al Verde (Pin 5).
- **`setup()` optimizado:** Usamos un bucle `for` para configurar los 3 pines como salida en pocas líneas de código.
- **Secuencia:** El programa enciende el Rojo, espera `tiempo1`, luego pasa al Verde por `tiempo1` y finalmente al Amarillo por `tiempo2`, repitiendo el ciclo indefinidamente.
