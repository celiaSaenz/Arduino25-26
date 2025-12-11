# Proyecto: Secuencia de LEDs

Este proyecto enciende y apaga cuatro LEDs conectados a los pines 5, 6, 7 y 8 de manera secuencial.  
Es ideal para aprender **control de múltiples salidas digitales** y uso de **variables para tiempos**.

---

## Materiales

- Arduino Uno
- 4 LEDs
- 4 resistencias de 220Ω 
- Cables de conexión
- Protoboard 

---

## Requisitos

- Arduino IDE o Arduino Cloud Web Editor
- Placa Arduino Uno

---

## Cómo usar

1. Conecta cuatro LEDs a los pines 5, 6, 7 y 8 (ánodo al pin, cátodo a GND con resistencia).  
2. Abre el archivo `.ino` en Arduino IDE o Web Editor.  
3. Selecciona la placa **Arduino Uno** y el puerto correcto.  
4. Haz clic en **Cargar**.  
5. Observa cómo los LEDs se encienden y apagan secuencialmente según el tiempo programado.

## Explicación

### Ejemplo 1:
- `pinMode(pin, OUTPUT)` configura cada pin como salida.  
- `digitalWrite(pin, HIGH)` enciende el LED en el pin correspondiente.  
- `digitalWrite(pin, LOW)` apaga el LED.  
- `delay(tiempo)` pausa el programa la cantidad de milisegundos indicada por la variable `tiempo`.

### Ejemplo 2:
- `int tiempo = 200;` define el tiempo de encendido y apagado de cada LED en milisegundos.
- `for (n=5; n<9; n++) { pinMode(n, OUTPUT); }` en el `setup()` configura los pines 5, 6, 7 y 8 como salidas digitales.
- La función `secuencia()` recorre los LEDs usando un bucle `for`, encendiéndolos (`digitalWrite(n, HIGH)`) y apagándolos (`digitalWrite(n, LOW)`) de manera secuencial, con una pausa de `delay(tiempo)` entre cada acción.
- `loop()` llama continuamente a la función `secuencia()`, haciendo que los LEDs se enciendan y apaguen en secuencia de forma repetida.

### Ejemplo 3:
- `int leds[] = {5,6,7,8};` declara un arreglo que contiene los pines a los que están conectados los LEDs.  
- `int tiempo = 200;` define el tiempo de encendido y apagado de cada LED en milisegundos.  
- En `setup()`, el bucle `for (n=0; n<4; n++) { pinMode(leds[n], OUTPUT); }` configura cada pin del arreglo como salida digital.  
- La función `secuencia()` recorre el arreglo de LEDs usando un bucle `for`, encendiendo (`digitalWrite(leds[n], HIGH)`) y apagando (`digitalWrite(leds[n], LOW)`) cada LED de manera secuencial, con una pausa de `delay(tiempo)` entre cada acción.  
- `loop()` llama continuamente a la función `secuencia()`, haciendo que los LEDs se enciendan y apaguen en secuencia de forma repetida.
