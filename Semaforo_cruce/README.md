# Proyecto: Cruce de Semáforos

Este proyecto aumenta la complejidad simulando un **cruce vial** con dos semáforos sincronizados.
El objetivo es aprender a coordinar múltiples salidas para que los estados de un semáforo correspondan lógicamente con los del otro (ej. si uno está en Verde, el otro debe estar en Rojo).

---

## Materiales

- Arduino Uno
- 2 LEDs Rojos, 2 LEDs Amarillos, 2 LEDs Verdes
- 6 Resistencias de 220Ω
- Cables de conexión
- Protoboard

---

## Requisitos

- Arduino IDE
- Placa Arduino Uno

---

## Cómo usar

1. **Semáforo 1:** Rojo (Pin 3), Amarillo (Pin 4), Verde (Pin 5).
2. **Semáforo 2:** Rojo (Pin 6), Amarillo (Pin 7), Verde (Pin 8).
3. Conecta todos los cátodos a GND con sus resistencias.
4. Carga el código en la placa.
5. Verifica que cuando un semáforo permite el paso (verde), el otro lo prohíbe (rojo).

---

## Explicación

El código gestiona una máquina de estados secuencial dentro del `loop()`:

1. **Fase 1:** Semáforo 1 en **Rojo** y Semáforo 2 en **Verde** (Paso para la vía 2). Dura 3 segundos.
2. **Fase 2:** Semáforo 2 cambia a **Amarillo** (precaución), mientras el 1 sigue en Rojo. Dura 0.5 segundos.
3. **Fase 3:** Semáforo 1 cambia a **Verde** y Semáforo 2 se pone en **Rojo** (Paso para la vía 1). Dura 3 segundos.
4. **Fase 4:** Semáforo 1 pasa a **Amarillo**, el 2 se mantiene en Rojo. Dura 0.5 segundos.

Esta lógica garantiza que nunca haya dos luces verdes encendidas al mismo tiempo, evitando "accidentes".


## Conexiones (idénticas al proyecto):
Semáforo 1:
1. Pin 3 → Resistencia → LED rojo → GND
2. Pin 4 → Resistencia → LED amarillo → GND
3. Pin 5 → Resistencia → LED verde → GND

Semáforo 2:
1. Pin 6 → Resistencia → LED rojo → GND
2. Pin 7 → Resistencia → LED amarillo → GND
3. Pin 8 → Resistencia → LED verde → GND
