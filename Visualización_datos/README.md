# Proyecto: Visualización de datos

Este proyecto introduce la comunicación entre el Arduino y el ordenador.
Mediante un **pulsador** y un **LED**, aprenderemos a enviar información al **Monitor Serie** para visualizar en la pantalla del PC lo que está ocurriendo en el circuito en tiempo real.

---

## Materiales

- Arduino Uno
- 1 LED
- 1 Resistencia de 220Ω (para el LED)
- 1 Pulsador
- 1 Resistencia de 10kΩ (configuración pull-down)
- Cables de conexión
- Protoboard

---

## Requisitos

- Arduino IDE
- Placa Arduino Uno

---

## Cómo usar

1. **Conexión del LED:** Conecta el ánodo al pin **13** y el cátodo a GND (con resistencia).
2. **Conexión del Botón:** Conecta un lado del botón a **5V**. El otro lado conéctalo al pin **2** y, desde ese mismo punto, coloca una resistencia de 10kΩ hacia **GND** (configuración Pull-down).
3. Abre el archivo `.ino` y cárgalo en la placa.
4. Abre el **Monitor Serie** (icono de la lupa en la esquina superior derecha del IDE).
5. Asegúrate de que la velocidad esté en **9600 baudios**.
6. Presiona el botón y observa tanto el LED como los mensajes en la pantalla.

---

## Explicación

### Conceptos clave:
- **`Serial.begin(9600)`**: Inicializa la comunicación de datos a 9600 bits por segundo. Es obligatorio ponerlo en el `setup`.
- **`Serial.println("Texto")`**: Envía un mensaje de texto al ordenador seguido de un salto de línea.
- **Lectura del botón**: Usamos `digitalRead(botonPin)`. Al usar una resistencia *pull-down* externa, el botón leerá `LOW` (0) cuando esté suelto y `HIGH` (1) cuando se presione.
- **Condicional `if/else`**: Si el botón detecta `HIGH`, enciende el LED y manda el mensaje "Boton presionado". Si no, apaga y notifica lo contrario.
