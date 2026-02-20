# Proyecto: Contador con Display de 7 Segmentos y 74HC595

Este proyecto utiliza un **Registro de Desplazamiento 74HC595** para controlar un display de 7 segmentos. El objetivo principal es aprender a ahorrar pines del Arduino (usando solo 3 pines para controlar 8 salidas) y entender cómo enviar datos de forma serial a paralela.

---

## Materiales

- Arduino Uno
- Registro de desplazamiento **74HC595**
- Display de 7 segmentos (Cátodo Común)
- 7 Resistencias de 220Ω (una para cada segmento)
- Cables de conexión
- Protoboard



---

## Requisitos

- Arduino IDE
- Placa Arduino Uno o compatible
- Esquema de pines del display de 7 segmentos

---

## Cómo usar

1. **Conexión del 74HC595:**
   - **Pin 2 (DS):** Conecta al pin **2** de Arduino (Data).
   - **Pin 3 (ST_CP):** Conecta al pin **3** de Arduino (Latch).
   - **Pin 4 (SH_CP):** Conecta al pin **4** de Arduino (Clock).
   - Conecta las salidas **Q0-Q6** a los segmentos **a-g** del display (usa resistencias).
2. Abre el archivo `.ino` en el Arduino IDE.
3. Haz clic en **Cargar**.
4. El display comenzará una cuenta regresiva del **9 al 0** cada segundo.
5. Al finalizar la cuenta, el sistema espera 4 segundos y reinicia el ciclo.

---

## Explicación

Controlar un display directamente consume muchos pines del Arduino. Al usar el **74HC595**, "empaquetamos" los datos y los enviamos uno tras otro por un solo cable de datos.

### Conceptos clave del código:

- **Patrones Binarios (`byte`):**
  Se define un array llamado `seven_seg_digits` donde cada número está representado por un byte (8 bits). Cada bit indica si un segmento específico (a, b, c, d, e, f, g) debe encenderse (1) o apagarse (0).

  B11111100 // Representa el número 0 encendiendo casi todos los segmentos

- **Función `shiftOut()`:** Es la herramienta clave de Arduino para este proyecto. Permite enviar un byte completo (8 bits) de forma serial a través de un solo pin. La función se encarga de "trocear" el dato y enviarlo **bit a bit** al registro de desplazamiento. El parámetro `LSBFIRST` (*Least Significant Bit First*) indica que el envío comienza por el bit de menor valor.



- **Manejo del `latchPin` (Pin de cerrojo):** Funciona como un interruptor de seguridad para la visualización. Mientras transmitimos los datos, el pin se mantiene en `LOW`. Solo cuando el `latchPin` sube a `HIGH`, el chip **74HC595** actualiza todas sus salidas de forma simultánea. Esto es fundamental para que el ojo humano no vea el "desfile" de bits, evitando parpadeos extraños en el display durante la carga de datos.

---
