# Proyecto: Termómetro con Alarma (LCD Estándar)

Este proyecto monitoriza la temperatura ambiental usando un sensor **DHT11** y muestra los datos en una **pantalla LCD 16x2 convencional** (conexión paralela).
Incluye un sistema de seguridad que activa una alarma visual y sonora si la temperatura excede el límite seguro.

---

## Materiales

- Arduino Uno
- 1 Sensor DHT11
- 1 Pantalla LCD 16x2 (16 pines)
- **1 Potenciómetro de 10kΩ** (Imprescindible para el contraste de la pantalla)
- 1 Buzzer
- 1 LED Rojo
- 1 Resistencia de 220Ω (para el LED)
- Muchos cables de conexión
- Protoboard

---

## Requisitos

- **Software:** Arduino IDE
- **Librerías:** 1. `DHT sensor library` (Instalar desde gestor)
  2. `LiquidCrystal` (Viene incluida en Arduino)
- **Hardware:** Placa Arduino Uno

---

## Esquema de Montaje

El montaje de la pantalla requiere atención. Sigue la tabla pin a pin.

### 1. Conexión de la Pantalla LCD (16 Pines)
La pantalla tiene los pines numerados del 1 al 16 (de izquierda a derecha).


| Pin LCD | Nombre | Conexión | Función |
|---|---|---|---|
| 1 | VSS | **GND** Arduino | Tierra |
| 2 | VDD | **5V** Arduino | Alimentación |
| 3 | V0 | **Pata central del Potenciómetro** | Contraste (ver nota abajo) |
| 4 | RS | Pin Digital **12** | Selección de registro |
| 5 | RW | **GND** Arduino | Escritura (siempre a tierra) |
| 6 | E | Pin Digital **11** | Enable (Habilitar) |
| 11 | D4 | Pin Digital **5** | Datos |
| 12 | D5 | Pin Digital **4** | Datos |
| 13 | D6 | Pin Digital **3** | Datos |
| 14 | D7 | Pin Digital **2** | Datos |
| 15 | A (LED+) | **5V** (con resistencia 220Ω opc) | Luz de fondo |
| 16 | K (LED-) | **GND** | Luz de fondo |

**Nota sobre el Potenciómetro:**
Conecta una pata extrema del potenciómetro a 5V, la otra extrema a GND, y la **central al Pin 3 (V0)** de la LCD. Gíralo hasta ver los caracteres nítidos.

### 2. Resto de componentes
Debido a que la pantalla ocupa los pines 2 al 5, movemos el resto:
- **Sensor DHT11 (Datos):** Al Pin Digital **8**.
- **LED Rojo:** Al Pin Digital **9**.
- **Buzzer:** Al Pin Digital **10**.

---

## Cómo usar

1. Realiza el cableado con paciencia. Un solo cable mal puesto en la pantalla hará que no muestre nada.
2. Carga el código `.ino` en tu Arduino.
3. **Ajuste inicial:** Si la pantalla se enciende pero no ves texto (o ves cuadros blancos), **gira el potenciómetro** lentamente hasta que aparezcan las letras.
4. Verifica que la temperatura se actualiza cada 2 segundos.

---

## Explicación

### Conexión Paralela (4 bits)
A diferencia de las pantallas I2C modernas, esta pantalla se conecta "a la antigua", usando 6 pines digitales del Arduino para enviar la información.
- `LiquidCrystal lcd(12, 11, 5, 4, 3, 2);`: Le indicamos al Arduino qué pines físicos están conectados a los pines de control y datos de la pantalla.

### Gestión de Pines
Al usar una pantalla paralela, consumimos casi todos los pines digitales básicos (del 2 al 5 y 11-12). Por eso es crucial planificar bien dónde conectamos los sensores extra (en este caso, movidos al 8, 9 y 10) para evitar conflictos de señal.
