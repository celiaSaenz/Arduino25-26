# Proyecto: Juego “Muertos y Heridos” (Picas y Fijas) con Teclado de Membrana + LEDs

Este proyecto implementa el clásico juego de deducción lógica **Muertos y Heridos** (también llamado **Picas y Fijas / Punto y Fama / 4digits**) usando un **teclado de membrana** para introducir el número y **LEDs** para mostrar el resultado de cada intento.

El Arduino genera un número secreto de **3 o 4 cifras** (configurable). En cada intento, el jugador escribe un número y el sistema responde con:

- **💀 Muertos:** cifra correcta y en la **posición correcta**
- **🩹 Heridos:** cifra correcta pero en **posición incorrecta**

El historial y el detalle de cada intento se muestran por el **Monitor Serie**.

---

## Materiales

- Arduino Uno o Nano
- 1× Teclado de membrana **4x4** (8 pines) *(se puede adaptar a 4x3)*
- 8× LEDs
  - 4× LEDs para **Muertos** (recomendado: rojos)
  - 4× LEDs para **Heridos** (recomendado: verdes/amarillos)
- 8× Resistencias de **220Ω** (o 330Ω)
- Protoboard
- Cables Dupont

---

## Requisitos

- Arduino IDE
- Librería **Keypad**

### Instalar librería Keypad
1. Arduino IDE → **Herramientas → Administrar bibliotecas…**
2. Buscar **Keypad**
3. Instalarla

---

## Montaje

### 1) Conexión del teclado 4x4
Conecta filas y columnas del teclado a pines digitales:

- **Filas (R1–R4)** → D2, D3, D4, D5  
- **Columnas (C1–C4)** → D6, D7, D8, D9

> Si tu teclado no viene marcado como R/C, normalmente los 8 pines están en orden; si al jugar las teclas no coinciden, hay que invertir/ajustar el mapa.

### 2) Conexión de LEDs
Cada LED:
- **Pin Arduino → resistencia 220Ω → ánodo (pata larga)**
- **cátodo (pata corta) → GND**

#### LEDs de Muertos (hasta 4)
- M1 → D10
- M2 → D11
- M3 → D12
- M4 → D13

#### LEDs de Heridos (hasta 4)
- H1 → A0
- H2 → A1
- H3 → A2
- H4 → A3

---

## Cómo jugar

1. Sube el programa al Arduino.
2. Abre el **Monitor Serie** a **9600 baudios**.
3. Introduce tu intento con el teclado:
   - **0–9**: escribir dígitos
   - `*`: borrar intento actual
   - `#`: enviar intento
4. Observa el resultado:
   - LEDs **rojos** encendidos → número de **muertos**
   - LEDs **verdes/amarillos** encendidos → número de **heridos**
5. Ganas cuando todos los dígitos son **muertos**.

---

## Explicación del código (sin mostrar el código)

### 1) Configuración del juego (constantes)
El programa empieza con constantes que permiten cambiar la dificultad sin tocar la lógica:
- **`NUM_DIGITS`**: número de cifras del secreto (3 o 4).
- **`MAX_TRIES`**: máximo de intentos permitidos.
- **`ALLOW_REPEATS`**: si se permiten dígitos repetidos (normalmente no).
- **`ALLOW_LEADING_ZERO`**: si se permite que el número empiece por 0.

Esto hace el proyecto “parametrizable”.

---

### 2) Lectura del teclado (librería Keypad)
Se define una **matriz** con el mapa de teclas (1–9, 0, `*`, `#`, etc.) y se indican los pines de filas/columnas.

En cada iteración del `loop()` se llama a una lectura tipo:
- “si hay tecla pulsada → procesa esa tecla”

El control se basa en 3 tipos de entrada:
- **dígitos**: se van acumulando para formar el intento
- `*`: borra el intento actual
- `#`: valida y evalúa el intento

---

### 3) Almacenamiento del secreto y del intento
Se guardan dos “cadenas” (arrays de `char`):
- **`secret[]`**: el número oculto
- **`guess[]`**: lo que va escribiendo el jugador

Además se usa un contador:
- **`guessLen`**: cuántas cifras llevas escritas

Esto permite construir el número “tecla a tecla”.

---

### 4) Generación del número secreto (aleatorio)
El secreto se genera al iniciar partida:
- Se usa `randomSeed()` con ruido (por ejemplo lectura analógica) para que no sea siempre igual.
- Se van eligiendo dígitos aleatorios y se van metiendo en `secret[]`.
- Si **no se permiten repetidos**, se comprueba que un dígito no se haya usado antes.

Así garantizas un secreto válido según la configuración.

---

### 5) Validación del intento antes de evaluarlo
Cuando el jugador pulsa `#`, el programa verifica:
- que el intento tiene **exactamente** `NUM_DIGITS` cifras
- que no hay **repetidos** (si está desactivado)
- que no empieza por **0** (si está desactivado)

Si falla, se rechaza el intento y se pide otro.

---

### 6) Cálculo de “Muertos”
Se recorren las posiciones del intento y el secreto:
- si `guess[i] == secret[i]` → suma 1 muerto

Esto cuenta únicamente las cifras correctas **y bien colocadas**.

---

### 7) Cálculo de “Heridos”
Para heridos se busca:
- cifras que están en el secreto pero **en otra posición**
- sin contar las que ya son muertos

En modo “sin repetidos”, el cálculo es más simple porque cada dígito puede contarse como herido una sola vez.

---

### 8) Mostrar resultado con LEDs (arrays + bucles)
Los LEDs se controlan con **dos arrays**:
- `muertosLED[]`
- `heridosLED[]`

Primero se apagan todos.
Luego se encienden tantos como indique el resultado:
- por ejemplo, 2 muertos → enciende los dos primeros LEDs rojos
- 1 herido → enciende el primer LED verde

Esto practica muy bien el uso de:
- **arrays**
- bucles `for`
- control de pines de salida

---

### 9) Control de intentos y fin de partida
Tras cada intento:
- se incrementa `tries`
- si muertos == `NUM_DIGITS` → **ganaste**
- si `tries` >= `MAX_TRIES` → **perdiste** y se muestra el secreto por serie

Se usa una variable tipo:
- **`gameOver`** para bloquear entradas normales hasta reiniciar.

---

## Ideas de ampliación (opcional)

- Añadir un **buzzer** (pitidos: uno por muerto, otro por herido)
- Añadir una **pantalla** (LCD o 7 segmentos) y jugar sin PC
- Modo difícil: permitir repetidos o usar 5 cifras
- Guardar récord de intentos (mejor marca)

---