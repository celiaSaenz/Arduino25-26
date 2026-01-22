# Proyecto: Hola Mundo en LCD 16x2

Este es el proyecto introductorio para el uso de pantallas de cristal líquido (LCD).
Muestra un mensaje de texto estático ("Hola Mundo!") en la primera fila y un contador de segundos dinámico en la segunda fila.

---

## Materiales

- Arduino Uno
- 1 Pantalla LCD 16x2 (Interfaz paralela estándar)
- 1 Potenciómetro de 10kΩ (Imprescindible para ajustar el contraste)
- Cables de conexión
- Protoboard
- (Opcional) Resistencia de 220Ω para la luz de fondo

---

## Requisitos

- Software: Arduino IDE
- Librería: LiquidCrystal.h (Viene instalada por defecto)
- Hardware: Placa Arduino Uno

---

## Esquema de Montaje

Este código utiliza la conexión paralela de 4 bits. Es crucial seguir el orden de los pines exacto declarado en la línea `LiquidCrystal lcd(12, 11, 5, 4, 3, 2);`.



### 1. Conexiones de Control y Datos
| Pin LCD | Función | Conexión Arduino |
|:--------|:--------|:-----------------|
| 4 (RS)  | Registro| Pin Digital 12   |
| 6 (E)   | Enable  | Pin Digital 11   |
| 11 (D4) | Dato 4  | Pin Digital 5    |
| 12 (D5) | Dato 5  | Pin Digital 4    |
| 13 (D6) | Dato 6  | Pin Digital 3    |
| 14 (D7) | Dato 7  | Pin Digital 2    |
| 5 (RW)  | Lectura/Escritura | A GND  |

### 2. Conexiones de Alimentación y Contraste
| Pin LCD | Función | Conexión Protoboard |
|:--------|:--------|:--------------------|
| 1 (VSS) | GND     | Línea Azul (-)      |
| 2 (VDD) | 5V      | Línea Roja (+)      |
| 3 (V0)  | Contraste | **Pata central del Potenciómetro** |
| 15 (A)  | Luz LED+| 5V (Idealmente con resistencia 220Ω) |
| 16 (K)  | Luz LED-| GND                 |

*Nota: Las patas extremas del potenciómetro van a 5V y GND respectivamente.*

---

## Cómo usar

1. Realiza el cableado con el Arduino desconectado.
2. Carga el código en la placa.
3. **AJUSTE DE CONTRASTE:** Si la pantalla se ilumina pero no ves texto, o ves rectángulos blancos sólidos, gira lentamente el potenciómetro hasta que el texto "Hola Mundo!" sea legible.
4. Observa cómo el número en la segunda fila aumenta cada segundo.

---

## Explicación

### Inicialización
- `LiquidCrystal lcd(12, 11, 5, 4, 3, 2);`: Crea el objeto LCD indicando qué pines del Arduino controlan la pantalla (RS, E, D4, D5, D6, D7).
- `lcd.begin(16, 2);`: Configura las dimensiones de la pantalla (16 columnas de ancho, 2 filas de alto).

### Posicionamiento y Escritura
- `lcd.print("Texto");`: Escribe caracteres en la posición actual del cursor.
- `lcd.setCursor(0, 1);`: Mueve el cursor.
  - El primer número (0) es la columna (izquierda).
  - El segundo número (1) es la fila (la de abajo). *Recordar: Fila 0 es la superior, Fila 1 es la inferior.*

### Función de Tiempo
- `millis()`: Devuelve el tiempo en milisegundos desde que el Arduino se encendió.
- `millis()/1000`: Al dividir por 1000, convertimos esos milisegundos en segundos para mostrar un reloj legible.