# Proyecto: Display 7 Segmentos controlado por Control Remoto IR

Este proyecto utiliza un **receptor infrarrojo (IR)** para recibir comandos de un mando a distancia y mostrar el número correspondiente en un **display de 7 segmentos**. Es un excelente ejercicio para entender la decodificación de señales inalámbricas y el control de salidas digitales mediante lógica de selección (`switch-case`).

---

## Materiales

* **Arduino Uno**
* **Módulo Receptor IR** (ej. VS1838B)
* **Control Remoto Infrarrojo**
* **Display de 7 segmentos** (Cátodo Común)
* **7 Resistencias de 220Ω**
* **Cables de conexión**
* **Protoboard**



---

## Requisitos

* **Arduino IDE**
* Librería **IRremote** (debe estar instalada en el IDE).
* Placa Arduino Uno.

---

## Cómo usar

1.  **Conexión del Receptor IR:**
    * **VCC** ➔ 5V
    * **GND** ➔ GND
    * **Signal** ➔ Pin **11**
2.  **Conexión del Display de 7 Segmentos:**
    * Conecta los segmentos **a, b, c, d, e, f, g** a los pines digitales **2, 3, 4, 5, 6, 7, 8** respectivamente (usando resistencias).
3.  Carga el código en tu Arduino.
4.  Abre el **Monitor Serie** (9600 baudios) para verificar los códigos recibidos.
5.  Apunta con el mando al receptor y presiona los números del 0 al 9; el display se actualizará instantáneamente.

---

## Explicación Técnica

El proyecto funciona como un sistema de traducción: convierte señales invisibles de luz infrarroja en dígitos legibles.

### Conceptos clave del código:

* **Librería IRremote:**
    Esta librería permite al Arduino "escuchar" la señal modulada del mando. El receptor convierte la ráfaga de luz IR en un **código hexadecimal** único (ej. `0xFF6897`).



* **Decodificación con `switch-case`:**
    La función `translateIR()` actúa como un diccionario. Compara el código recibido (`results.value`) con una lista de códigos conocidos. Si coinciden, ejecuta las instrucciones para encender los segmentos específicos de ese número.

* **Control de Segmentos:**
    Cada número en el display es una combinación de 7 LEDs independientes. Por ejemplo, para mostrar el número **1**, el código pone en `HIGH` solo los pines **b** y **c**, manteniendo los demás en `LOW`:
    ```cpp
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    ```

* **Prevención de Errores:**
    El código incluye un caso para `0xFFFFFFFF`, que es el código que envían muchos mandos cuando se mantiene pulsado un botón (repetición), evitando que el programa se confunda.

---