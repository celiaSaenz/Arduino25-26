# Proyecto: Piano con buzzer

Este proyecto convierte tu Arduino en un instrumento musical utilizando un **buzzer piezoeléctrico** y pulsadores.
Incluye dos vertientes: una básica para entender el control de sonido con un botón y otra avanzada que simula un piano de 6 notas. Es ideal para aprender sobre la generación de frecuencias con `tone()`, el uso de **arreglos (arrays)** y la gestión de múltiples entradas.

---

## Materiales

- Arduino Uno
- 1 Buzzer pasivo (Piezoeléctrico)
- 1 a 6 Pulsadores (Push buttons)
- Cables de conexión
- Protoboard
- Resistencia 220 

---

## Requisitos

- Arduino IDE o Arduino Cloud Web Editor
- Placa Arduino Uno

---

## Cómo usar

1. **Montaje del Buzzer:** Conecta el positivo del buzzer al pin **10** y el negativo a **GND**.
2. **Montaje de Botones:**
   - **Para 1 botón:** Conecta un pulsador entre el pin **2** y **GND**.
   - **Para 6 botones:** Conecta 6 pulsadores a los pines **2, 3, 4, 5, 6 y 7**. El otro extremo de todos los botones va a **GND**.
3. Abre el archivo `.ino` correspondiente (`Codigo_1_boton` o `Codigo_6_botones`) en el Arduino IDE.
4. Selecciona la placa **Arduino Uno** y el puerto correcto.
5. Haz clic en **Cargar**.
6. Presiona los botones para reproducir las notas musicales.

---

## Explicación

### General:
- `tone(pin, frecuencia)`: Genera una onda cuadrada en el pin especificado con la frecuencia en Hertz indicada (sonido).
- `noTone(pin)`: Detiene la generación de sonido en el pin.
- `INPUT_PULLUP`: Se usa en la configuración de los botones para activar las resistencias internas del Arduino. Esto significa que el botón leerá `HIGH` cuando está suelto y `LOW` cuando se presiona (lógica inversa).

### Ejemplo 1 (Codigo_1_boton):
- Se configura un solo botón en el pin 2.
- El `loop()` verifica constantemente el estado con `digitalRead()`.
- Si el botón se presiona (`LOW`), se emite una nota fija de **440Hz** (La).
- Si se suelta, se llama a `noTone()` para silenciar el buzzer.

### Ejemplo 2 (Codigo_6_botones):
- `int botones[] = {2, 3, 4, 5, 6, 7};`: Define un arreglo con los pines de entrada.
- `int notas[] = {262, 294, 330, ...};`: Define un arreglo paralelo con las frecuencias de las notas (Do, Re, Mi, Fa, Sol, La).
- En el `setup()`, un bucle `for` configura automáticamente todos los pines del arreglo como `INPUT_PULLUP`.
- En el `loop()`, otro bucle `for` recorre los 6 botones muy rápidamente:
  - Si detecta que el botón en la posición `i` está presionado, ejecuta `tone(buzzer, notas[i])`, reproduciendo la frecuencia correspondiente a ese botón.
  - Incluye un pequeño `delay(200)` para evitar rebotes mecánicos y separar las notas.
