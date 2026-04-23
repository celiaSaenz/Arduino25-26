# Proyecto: Mini Piano con Teclado Matricial 4x4

Este proyecto utiliza un **teclado matricial 4x4** para detectar pulsaciones y reproducir notas musicales en un **buzzer**, convirtiéndolo en un **mini piano funcional**. Es un excelente ejercicio para aprender cómo leer múltiples entradas, generar sonido con Arduino y mapear teclas a frecuencias musicales.

---

## Materiales

* Arduino Uno (o compatible)
* Teclado matricial 4x4
* Buzzer pasivo (recomendado)
* Cables de conexión
* Protoboard

---

## Requisitos

* Arduino IDE
* Librería **Keypad** (instalada en el IDE)
* Placa Arduino Uno

---

## Cómo usar

1. **Conexión del teclado 4x4:**
   - Filas → pines 9, 8, 7, 6  
   - Columnas → pines 5, 4, 3, 2  

2. **Conexión del buzzer:**
   - Positivo → pin 10  
   - Negativo → GND  

3. Carga el código en el Arduino.

4. Pulsa cualquier tecla:
   - Cada tecla reproduce una nota musical  
