# Proyecto: Barrera de Garaje Automática

Este proyecto simula un sistema de control de acceso para un garaje o parking.
Utiliza un **sensor de ultrasonidos (HC-SR04)** para detectar la presencia de un vehículo. Cuando el coche se acerca a menos de 15 cm, el sistema activa un **servomotor** que levanta la barrera (simulando la apertura) y la cierra automáticamente cuando el vehículo se aleja.

---

## Materiales

- Arduino Uno
- 1 Sensor de Ultrasonidos (HC-SR04)
- 1 Micro Servomotor (ej. SG90)
- Cables de conexión y Protoboard

---

## Requisitos

- **Software:** Arduino IDE
- **Librería:** `Servo.h` (Incluida por defecto en el IDE)
- **Hardware:** Placa Arduino Uno

---

## Esquema de Montaje

Realiza las conexiones con el Arduino desconectado.

### 1. Sensor Ultrasonidos (HC-SR04)
| Pin Sensor | Conexión Arduino | Función             |
|:-----------|:-----------------|:--------------------|
| VCC        | 5V               | Alimentación        |
| GND        | GND              | Tierra              |
| Trig       | Pin Digital 9    | Emisor de pulso     |
| Echo       | Pin Digital 10   | Receptor de eco     |

### 2. Servomotor
| Cable Servo      | Conexión Arduino | Función             |
|:-----------------|:-----------------|:--------------------|
| Rojo (Centro)    | 5V               | Alimentación        |
| Marrón / Negro   | GND              | Tierra              |
| Naranja / Blanco | Pin Digital 6    | Señal de control    |

---

## Cómo usar

1. **Corrección del Código:** Antes de cargar, asegúrate de declarar los pines de los LEDs al inicio del código si deseas usarlos (ej: `int ledRojo = 4;`). Si no vas a usar LEDs, borra las líneas `pinMode` referentes a ellos en el `setup`.
2. Realiza el montaje del circuito según la tabla.
3. Abre el archivo `.ino` en el Arduino IDE.
4. Carga el código en la placa.
5. Acerca un objeto (tu mano o un coche de juguete) al sensor.
   - **Distancia < 15 cm:** El servo gira a 90° (Barrera abierta).
   - **Distancia > 15 cm:** El servo vuelve a 0° (Barrera cerrada).

---

## Explicación

### Funcionamiento del Sensor HC-SR04
El sensor funciona como un sonar:
1. Envía un pulso de sonido ultrasónico (`digitalWrite(trigPin, HIGH)`).
2. Espera a que el sonido rebote en un objeto y vuelva.
3. Mide el tiempo que ha tardado el viaje (`pulseIn(echoPin, HIGH)`).

### Cálculos Matemáticos
El código convierte el tiempo en distancia con la fórmula:
`distancia = duracion * 0.034 / 2;`
- **0.034:** Es la velocidad del sonido en cm/microsegundo.
- **/ 2:** Dividimos por dos porque el tiempo medido es de ida y vuelta, y solo queremos saber la distancia de ida.

### Lógica de Control
Se utiliza una estructura condicional `if / else`:
- Si la distancia es válida (mayor a 0) y menor a 15 cm, se asume que hay un coche esperando y se ejecuta `puerta.write(90)` para abrir.
- En cualquier otro caso, se ejecuta `puerta.write(0)` para mantener el garaje cerrado.
