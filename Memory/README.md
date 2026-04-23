# Proyecto: Juego de Memoria (Memory) para 2 Jugadores

Este proyecto recrea el clásico juego de encontrar parejas de cartas utilizando un **teclado matricial 4x4** como tablero físico y una **pantalla LCD 16x2** con interfaz I2C para mostrar el progreso, los puntos y el estado de la partida. Está diseñado para que dos jugadores compitan por ver quién tiene mejor memoria.

---

## Materiales

* **Arduino Uno**
* **Teclado Matricial 4x4** (Keypad)
* **Pantalla LCD 16x2** con módulo **I2C**
* **Cables de conexión** (Jumpers)
* **Protoboard**

---

## Requisitos

* **Arduino IDE** instalado.
* Librería **Keypad** (disponible en el Gestor de Librerías).
* Librería **LiquidCrystal_I2C** (disponible en el Gestor de Librerías).

---

## Cómo usar

1.  **Conexión del Teclado (Pines digitales):**
    * Filas ➔ Pines **2, 3, 4, 5**
    * Columnas ➔ Pines **6, 7, 8, 9**
2.  **Conexión de la Pantalla LCD (I2C):**
    * SDA ➔ Pin **A4** (en Arduino Uno)
    * SCL ➔ Pin **A5** (en Arduino Uno)
    * VCC ➔ 5V
    * GND ➔ GND
3.  Carga el código en tu placa Arduino.
4.  **Dinámica del juego:**
    * El LCD indicará de quién es el turno (Jugador 1 o Jugador 2).
    * Cada tecla del teclado (**1** al **D**) representa una posición en el tablero.
    * Pulsa una tecla para revelar la primera carta (se mostrará una letra de la A a la H).
    * Pulsa una segunda tecla para intentar encontrar su pareja.
    * Si coinciden, sumas un punto. Si fallas, el turno pasa al siguiente jugador.
    * Al encontrar las 8 parejas, la pantalla anunciará al ganador.

---

## Explicación

El sistema gestiona un tablero virtual de 16 posiciones que se mezcla aleatoriamente en cada inicio de partida.

### Conceptos clave del código:

* **Mapeo del Teclado Matricial:**
  Se utiliza la librería `Keypad` para leer una matriz de 16 botones usando solo 8 pines. El código traduce caracteres como '1', 'A' o '*' en índices numéricos del 0 al 15 para acceder al array del tablero.

* **Mezcla Aleatoria (Random Seed):**
  Para que las cartas no estén siempre en el mismo sitio, se usa `randomSeed(analogRead(A0))`. Esto toma el ruido eléctrico de un pin vacío para generar una semilla verdaderamente aleatoria al iniciar.

* **Comunicación I2C:**
  Al usar un adaptador I2C para el LCD, ahorramos muchos pines que de otro modo serían necesarios para los datos de la pantalla, permitiendo que el teclado y la pantalla coexistan sin conflictos de pines.

* **Lógica de Validación:**
  El programa incluye funciones como `leerCartaValida()` que comprueban si una carta ya fue resuelta o si el jugador está intentando pulsar la misma tecla dos veces, lanzando avisos en pantalla para guiar a los usuarios.

---