# Proyecto: Termómetro Digital con Alarma

Este proyecto combina monitoreo ambiental y sistemas de alerta. Utiliza un sensor **DHT11** para leer temperatura y humedad, mostrando los valores en una pantalla **LCD 16x2**.
Además, integra lógica de control: si la temperatura supera un límite preestablecido, se activa una alarma visual (LED) y sonora (Buzzer).

---

## Materiales

- Arduino Uno
- 1 Sensor de temperatura y humedad DHT11
- 1 Pantalla LCD 16x2 con adaptador I2C
- 1 Buzzer pasivo o activo
- 1 LED Rojo
- 1 Resistencia de 220Ω (para el LED)
- Cables de conexión (Macho-Hembra y Macho-Macho)
- Protoboard

---

## Requisitos

- **Software:** Arduino IDE
- **Librerías necesarias:**
  1. `DHT sensor library` (por Adafruit)
  2. `LiquidCrystal I2C`
- **Hardware:** Placa Arduino Uno

---

## Esquema de Montaje

### 1. Pantalla LCD (I2C)
La pantalla usa el protocolo I2C, que solo requiere dos pines de datos.
- **GND** → GND Arduino
- **VCC** → 5V Arduino
- **SDA** → Pin **A4** (en Arduino Uno)
- **SCL** → Pin **A5** (en Arduino Uno)

### 2. Sensor DHT11
- **Pin 1 (-)** → GND
- **Pin 2 (+)** → 5V
- **Pin 3 (Out/S)** → Pin Digital **2**

### 3. Alarma
- **LED Rojo:** Ánodo al Pin **8**, Cátodo a GND (con resistencia).
- **Buzzer:** Positivo al Pin **9**, Negativo a GND.

---

## Cómo usar

1. **Instalar Librerías:** En el Arduino IDE, ve a *Programa > Incluir Librería > Administrar Bibliotecas*. Busca e instala "DHT sensor library" y "LiquidCrystal I2C".
2. Realiza el montaje del circuito siguiendo el esquema.
3. Abre el archivo `.ino`.
4. Carga el código en tu placa.
5. Verás la temperatura y humedad en la pantalla.
6. **Prueba la alarma:** Acerca una fuente de calor suave (o tu aliento) al sensor. Cuando pase de **28°C**, el LED se encenderá y el buzzer sonará.

---

## Explicación

### Protocolo I2C
Para la pantalla LCD usamos un módulo I2C. Esto nos permite controlar la pantalla usando solo los pines analógicos **A4 (SDA)** y **A5 (SCL)**, en lugar de conectar los 16 pines de la pantalla uno por uno.
- `LiquidCrystal_I2C lcd(0x27, 16, 2);`: Crea el objeto pantalla en la dirección 0x27 con tamaño 16x2.

### Sensor DHT11
Es un sensor digital que mide temperatura y humedad.
- `dht.readTemperature()`: Devuelve el valor en grados Celsius.
- `isnan(t)`: Es una función de seguridad. Verifica si el sensor devolvió "Not a Number" (error de lectura) para evitar mostrar datos falsos.

### Lógica de Control
El `loop()` revisa constantemente la temperatura. Usamos un condicional `if`:
- Si `temperatura >= 28`: Activamos `digitalWrite(led, HIGH)` y `tone(buzzer)`.
- Si no: Apagamos todo.
