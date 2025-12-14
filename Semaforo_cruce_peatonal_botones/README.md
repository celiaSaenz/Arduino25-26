# Proyecto: Semáforo Peatonal con Botón

Este es un semáforo inteligente. Por defecto, prioriza el tráfico de vehículos (siempre en verde), pero incluye un **botón de solicitud** para los peatones. Cuando se presiona, el sistema inicia una secuencia segura para detener los autos y permitir el cruce.

---

## Materiales

- Arduino Uno
- 5 LEDs (Rojo, Amarillo, Verde para autos; Rojo, Verde para peatones).
- 1 Pulsador
- Resistencias y cables.

---

## Requisitos

- Arduino IDE
- Placa Arduino Uno

---

## Cómo usar

1. **Conexiones LEDs:** Iguales al ejercicio anterior (Autos: 3,4,5 / Peatones: 6,7).
2. **Conexión Botón:** Conecta un pulsador entre el pin **2** y **GND**. No hace falta resistencia externa.
3. Carga el código.
4. Verás que los autos siempre tienen verde.
5. **Presiona el botón:** El sistema esperará, cambiará el semáforo de autos a rojo y te dará luz verde peatonal.

---

## Explicación

### Lógica Interactiva
- **`INPUT_PULLUP`**: El botón usa la resistencia interna del Arduino. Se activa con `LOW` (al conectarse a GND).
- **Control de flujo**: El `loop()` verifica constantemente si el botón ha sido presionado.
    - Si **NO** se presiona: Ejecuta `secuenciaAutos()` (Autos fluyen, pero en este código realiza ciclos de demostración).
    - Si **SÍ** se presiona: Activa la variable `botonPresionado` y llama a la función `cambiarSemaforoPeatonal()`.

### Funciones
- **`cambiarSemaforoPeatonal()`**: Esta función contiene la lógica específica para:
    1. Detener autos (Verde -> Amarillo -> Rojo).
    2. Dar paso a peatones (Rojo peatón apagado -> Verde peatón encendido).
    3. Esperar tiempo de cruce.
    4. Restaurar el tráfico (Parpadeo peatonal/Rojo peatón -> Verde autos).
