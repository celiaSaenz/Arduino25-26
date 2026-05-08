# Proyecto: Control de Matriz de 10 LEDs por Infrarrojos

Este proyecto permite controlar un conjunto de **10 LEDs** de forma individual o grupal utilizando un **mando a distancia IR**. Es ideal para entender cómo mapear señales inalámbricas para activar múltiples salidas digitales y crear paneles de control remotos.

---

## Materiales

* **Arduino Uno**
* **10 LEDs** (pueden ser de diferentes colores)
* **10 Resistencias de 220Ω**
* **Módulo Receptor IR** (ej. VS1838B)
* **Control Remoto Infrarrojo**
* **Cables de conexión** y Protoboard

---

## Requisitos

* **Arduino IDE**
* Librería **IRremote** instalada.
* Placa Arduino Uno.

---

## Cómo usar

1.  **Conexión de los LEDs:**
    * Conecta los ánodos de los 10 LEDs a los pines digitales: **2, 3, 4, 5, 6, 7, 8, 9, 10 y 12**.
    * Usa una resistencia para cada LED conectada a Tierra (GND).
2.  **Conexión del Receptor IR:**
    * **Signal** ➔ Pin **11**
    * **VCC** ➔ 5V
    * **GND** ➔ GND
3.  Carga el código en tu Arduino.
4.  **Funcionamiento del Mando:**
    * **Botones 0 al 9:** Encienden el LED correspondiente uno por uno.
    * **Botón FAST FORWARD:** Enciende **todos** los LEDs al mismo tiempo.
    * **Botón POWER:** Apaga **todos** los LEDs por completo.
5.  Abre el **Monitor Serie** para ver qué botón estás pulsando en tiempo real.

---

## Explicación

El código funciona como un conmutador remoto que asigna una acción específica a cada código hexadecimal recibido.

### Conceptos clave del código:

* **Decodificación de Señales IR:**
    Cada vez que pulsas un botón, el receptor capta una ráfaga de luz y la convierte en un número único. Por ejemplo, el código `0xFFA25D` es interpretado por el programa como el botón "POWER".

* **Control Individual (Modo Selección):**
    A diferencia de otros proyectos donde los pines se configuran todos al inicio, aquí el código usa `pinMode(LEDx, OUTPUT)` dentro del `switch` para activar el pin solo cuando se presiona el número correspondiente.

* **Apagado y Encendido Maestro:**
    * El caso `0xFFA25D` (POWER) ejecuta una lista de instrucciones `digitalWrite(pin, LOW)` para todos los pines, limpiando el tablero.
    * El caso `0xFFC23D` (FAST FORWARD) hace lo contrario, poniendo todos los pines en `HIGH` para un encendido total.

* **Gestión de Repetición:**
    Si el receptor recibe el código `0xFFFFFFFF`, significa que el botón se ha dejado pulsado. El código lo identifica como "ERROR" o repetición para evitar comportamientos erráticos.

---