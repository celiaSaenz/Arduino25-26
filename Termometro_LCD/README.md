# Proyecto: Termómetro Digital con Alarma (LCD Estándar)

Este proyecto convierte tu Arduino en una estación de monitoreo ambiental.
Utiliza un sensor **DHT11** para leer temperatura y humedad, mostrando los valores en una **pantalla LCD 16x2** convencional. Además, incluye un sistema de seguridad que activa una alarma visual (LED) y sonora (Buzzer) si la temperatura supera un límite seguro (28°C).

---

## Materiales

- Arduino Uno
- 1 Sensor de temperatura y humedad DHT11
- 1 Pantalla LCD 16x2 (versión estándar de 16 pines)
- **1 Potenciómetro de 10kΩ** (Imprescindible para el contraste)
- 1 Buzzer (Activo o Pasivo)
- 1 LED Rojo
- 1 Resistencia de 220Ω (para el LED)
- Cables de conexión y Protoboard

---

## Requisitos

- **Software:** Arduino IDE
- **Librerías necesarias:**
  1. `DHT sensor library` (Instalar desde el Gestor de Librerías).
  2. `LiquidCrystal` (Viene preinstalada en Arduino IDE).
- **Hardware:** Placa Arduino Uno.

---

## Esquema de Montaje

Este proyecto requiere atención al cableado debido a la pantalla LCD. Sigue esta tabla conexión a conexión.

### 1. Conexiones Principales

| Componente | Pin/Pata | Conectar a... | Nota |
|:--- |:--- |:--- |:--- |
| **Potenciómetro** | Extremo Izq. | 5V | |
| | Extremo Der. | GND | |
| | **Centro** | **Pin 3 (V0)** de la LCD | **Controla el contraste** |
| **Sensor DHT11** | VCC (+) | 5V | |
| | GND (-) | GND | |
| | DATA (S) | Pin Digital **8** | |
| **LED Rojo** | Ánodo (+) | Pin Digital **9** | |
| | Cátodo (-) | GND | Usar resistencia 220Ω |
| **Buzzer** | Positivo (+) | Pin Digital **10** | |
| | Negativo (-) | GND | |

### 2. Conexión Pantalla LCD (Pines 1 al 16)

| Pin LCD | Nombre | Conexión Arduino / Protoboard |
|:--- |:--- |:--- |
| 1 | VSS | GND |
| 2 | VDD | 5V |
| 3 | V0 | **Pata Central del Potenciómetro** |
| 4 | RS | Pin Digital **12** |
| 5 | RW | GND |
| 6 | E | Pin Digital **11** |
| 7-10 | - | No conectar (Vacíos) |
| 11 | D4 | Pin Digital **5** |
| 12 | D5 | Pin Digital **4** |
| 13 | D6 | Pin Digital **3** |
| 14 | D7 | Pin Digital **2** |
| 15 | A (+) | 5V (Opcional: Resistencia 220Ω) |
| 16 | K (-) | GND |

---

## Cómo usar

1. **Instalar Librería:** Abre Arduino IDE, ve a *Programa > Incluir Librería > Administrar Bibliotecas*, busca **"DHT sensor library"** e instálala.
2. Realiza el montaje siguiendo estrictamente la tabla de arriba.
3. Abre el archivo `.ino` y cárgalo en la placa.
4. **Paso Crítico:** Si la pantalla se enciende pero no ves texto (o ves rectángulos blancos), **gira la perilla del potenciómetro** suavemente hasta que las letras aparezcan nítidas.
5. Prueba la alarma calentando el sensor con el aliento hasta superar los 28°C.

---

## Explicación

### Pantalla LCD (Modo 4 bits)
La pantalla se conecta en modo paralelo utilizando 6 pines de control del Arduino.
- `LiquidCrystal lcd(12, 11, 5, 4, 3, 2);`: Esta línea configura la librería para saber qué pines físicos del Arduino están conectados a los pines RS, E, D4, D5, D6 y D7 de la pantalla.

### Sensor y Actuadores
- El sensor DHT11 envía datos digitales por el pin 8.
- El código evalúa la temperatura en cada ciclo del `loop()`.
- **Condicional de Alarma:**
  ```cpp
  if (t >= umbralTemp) { ... }
