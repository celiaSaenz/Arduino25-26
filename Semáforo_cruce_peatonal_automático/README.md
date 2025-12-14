# Proyecto: Semáforo con Cruce Peatonal Automático

Este sistema integra un semáforo para vehículos y otro para peatones.
Funciona de manera automática mediante tiempos preprogramados, alternando el derecho de paso entre los coches y las personas.

---

## Materiales

- Arduino Uno
- **Semáforo Autos:** LEDs Rojo, Amarillo, Verde.
- **Semáforo Peatones:** LEDs Rojo, Verde.
- 5 Resistencias de 220Ω
- Cables y Protoboard

---

## Requisitos

- Arduino IDE
- Placa Arduino Uno

---

## Cómo usar

1. **Conexiones Autos:** Rojo (Pin 3), Amarillo (Pin 4), Verde (Pin 5).
2. **Conexiones Peatones:** Rojo (Pin 6), Verde (Pin 7).
3. Carga el código.
4. Observa cómo los peatones solo tienen luz verde cuando los autos están totalmente detenidos (Luz roja).

---

## Explicación

El ciclo se divide en 3 estados claros:
1. **Autos avanzan:** Luz verde de autos ENCENDIDA, luz roja de peatones ENCENDIDA. (Es seguro para autos, peligroso para peatones).
2. **Precaución:** Luz amarilla de autos ENCENDIDA. Peatones siguen en rojo.
3. **Peatones cruzan:** Luz roja de autos ENCENDIDA. Luz verde de peatones ENCENDIDA.

Se utilizan variables `const int` para definir los pines y los tiempos, lo que hace el código más legible y fácil de modificar si se quiere cambiar la duración del semáforo.
