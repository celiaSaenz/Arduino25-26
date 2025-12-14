# Proyecto: Secuencia de LED RGB

Este proyecto controla un **LED RGB** (Rojo, Verde, Azul) para mostrar una secuencia de colores primarios.
El objetivo es aprender a manejar componentes que integran múltiples actuadores en uno solo y cómo optimizar el código utilizando **funciones personalizadas** para evitar repetir instrucciones.

---

## Materiales

- Arduino Uno
- 1 LED RGB (Cátodo Común)
- 3 Resistencias de 220Ω (una para cada canal de color)
- Cables de conexión
- Protoboard

---

## Requisitos

- Arduino IDE o Arduino Cloud Web Editor
- Placa Arduino Uno

---

## Cómo usar

1. **Identifica las patas del LED RGB:**
   - La pata más larga es el **Cátodo (-) o GND**.
   - Las otras tres corresponden a los colores **Rojo (R)**, **Verde (G)** y **Azul (B)**.
2. **Conexión:**
   - Conecta la pata larga (Cátodo) a **GND**.
   - Conecta la pata del **Rojo** al pin **9** (con resistencia).
   - Conecta la pata del **Verde** al pin **10** (con resistencia).
   - Conecta la pata del **Azul** al pin **11** (con resistencia).
3. Abre el archivo `.ino` en el Arduino IDE.
4. Selecciona la placa **Arduino Uno** y el puerto correcto.
5. Haz clic en **Cargar**.
6. Observa cómo el LED cambia de color cíclicamente cada medio segundo.

---

## Explicación

Un LED RGB contiene en su interior tres LEDs pequeños (uno rojo, uno verde y uno azul). Al encenderlos de forma individual o combinada, podemos generar distintos colores.

### Conceptos clave del código:

- **Constantes de pines:**
  `const int ledRojo = 9;`
  Se usan constantes para definir los pines. Esto hace que el código sea más fácil de leer y modificar si cambias las conexiones.

- **Función personalizada `encenderColor()`:**
  En lugar de escribir tres veces `digitalWrite` cada vez que queremos cambiar el color, creamos una función auxiliar:
  ```cpp
  void encenderColor(int r, int g, int b) {
    digitalWrite(ledRojo, r);
    digitalWrite(ledVerde, g);
    digitalWrite(ledAzul, b);
  }
