# Proyecto: Barrera de Garaje Automática con Semáforo

Este proyecto mejora la versión anterior añadiendo indicadores visuales.
Simula una barrera de parking que se abre automáticamente al detectar un vehículo mediante un sensor de ultrasonidos. Además, incluye un sistema de semáforo (LEDs Rojo y Verde) para indicar el estado de la puerta o la ocupación del espacio.

---

## Materiales

- Arduino Uno
- 1 Sensor de Ultrasonidos (HC-SR04)
- 1 Micro Servomotor (ej. SG90)
- 1 LED Rojo
- 1 LED Verde
- 2 Resistencias de 220 Ohmios (para los LEDs)
- Cables de conexión y Protoboard

---

## Requisitos

- Software: Arduino IDE
- Librería: Servo.h (Incluida por defecto en el IDE)
- Hardware: Placa Arduino Uno

---

## Esquema de Montaje



Realiza las conexiones con el Arduino desconectado. Presta atención a los pines de los LEDs:

1. SENSOR ULTRASONIDOS (HC-SR04)
   - VCC  -> 5V Arduino
   - GND  -> GND Arduino
   - Trig -> Pin Digital 9
   - Echo -> Pin Digital 10

2. SERVOMOTOR
   - Rojo (VCC)    -> 5V Arduino
   - Marrón (GND)  -> GND Arduino
   - Naranja (Señal)-> Pin Digital 6

3. INDICADORES LED
   - LED Rojo (Ánodo/Pata larga)  -> Pin Digital 11
   - LED Verde (Ánodo/Pata larga) -> Pin Digital 12
   - Cátodos (Patas cortas)       -> A GND (usando resistencias de 220 Ohms)

---

## Cómo usar

1. Monta el circuito siguiendo la tabla de conexiones.
2. Abre el Arduino IDE y carga el código proporcionado.
3. Observa el estado inicial:
   - Si no hay nada cerca, la barrera está bajada (0 grados) y el LED VERDE está encendido (indicando "Libre" o "Esperando").
4. Acerca un objeto a menos de 15 cm del sensor:
   - La barrera se levanta (90 grados).
   - El LED VERDE se apaga.
   - El LED ROJO se enciende (indicando "Ocupado" o "Acción en curso").

---

## Explicación

### Lógica de Control
El código funciona mediante una condición principal (IF / ELSE) que controla tres componentes simultáneamente:

1. MEDICIÓN: El sensor HC-SR04 mide la distancia constantemente.
   
2. ESTADO DE REPOSO (Distancia > 15 cm):
   - El servo se mantiene en 0 grados (Cerrado).
   - Se activa el LED Verde (HIGH).
   - Se apaga el LED Rojo (LOW).

3. ESTADO ACTIVO (Distancia < 15 cm):
   - El servo gira a 90 grados (Abierto).
   - Se activa el LED Rojo (HIGH).
   - Se apaga el LED Verde (LOW).

### Detalles Técnicos
- 'pulseIn(echoPin, HIGH)': Mide la duración del rebote del sonido.
- 'distancia = duracion * 0.034 / 2': Convierte tiempo en distancia física.
- 'delay(500)': Hace que el sistema verifique la distancia cada medio segundo, evitando que el servo vibre o se mueva erráticamente.
