#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const byte FILAS = 4;
const byte COLUMNAS = 4;

char teclas[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinesFilas[FILAS] = {2, 3, 4, 5};
byte pinesColumnas[COLUMNAS] = {6, 7, 8, 9};

Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

// Cambia 0x27 por 0x3F si tu LCD no muestra nada
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int NUM_CARTAS = 16;
const int NUM_PAREJAS = 8;

// Orden físico de las teclas = posiciones del tablero
const char etiquetas[NUM_CARTAS] = {
  '1', '2', '3', 'A',
  '4', '5', '6', 'B',
  '7', '8', '9', 'C',
  '*', '0', '#', 'D'
};

int tablero[NUM_CARTAS];
bool resueltas[NUM_CARTAS];

int jugadorActual = 1;
int puntosJ1 = 0;
int puntosJ2 = 0;
int parejasEncontradas = 0;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  randomSeed(analogRead(A0));

  pantallaInicio();
  iniciarJuego();
}

void loop() {
  if (parejasEncontradas >= NUM_PAREJAS) {
    mostrarFinal();
    esperarReinicio();
    return;
  }

  jugarTurno();
}

void pantallaInicio() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MEMORY 2 JUG.");
  lcd.setCursor(0, 1);
  lcd.print("Cargando...");
  delay(1500);
}

void iniciarJuego() {
  // Crear parejas: 0,0,1,1,2,2...7,7
  for (int i = 0; i < NUM_PAREJAS; i++) {
    tablero[i * 2] = i;
    tablero[i * 2 + 1] = i;
  }

  // Mezclar tablero
  mezclarTablero();

  // Reset partida
  for (int i = 0; i < NUM_CARTAS; i++) {
    resueltas[i] = false;
  }

  jugadorActual = 1;
  puntosJ1 = 0;
  puntosJ2 = 0;
  parejasEncontradas = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nueva partida");
  lcd.setCursor(0, 1);
  lcd.print("Empieza J1");
  delay(1500);

  // Opcional para depurar
  imprimirTableroPorSerial();
}

void mezclarTablero() {
  for (int i = NUM_CARTAS - 1; i > 0; i--) {
    int j = random(i + 1);

    int temp = tablero[i];
    tablero[i] = tablero[j];
    tablero[j] = temp;
  }
}

void jugarTurno() {
  mostrarCabecera();
  lcd.setCursor(0, 1);
  lcd.print("Elige 1a carta");

  int carta1 = leerCartaValida(-1);

  mostrarUnaCarta(carta1);
  delay(1200);

  mostrarCabecera();
  lcd.setCursor(0, 1);
  lcd.print("Elige 2a carta");

  int carta2 = leerCartaValida(carta1);

  mostrarDosCartas(carta1, carta2);
  delay(1500);

  if (tablero[carta1] == tablero[carta2]) {
    resueltas[carta1] = true;
    resueltas[carta2] = true;
    parejasEncontradas++;

    if (jugadorActual == 1) {
      puntosJ1++;
    } else {
      puntosJ2++;
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pareja! J");
    lcd.print(jugadorActual);
    lcd.print(" suma");
    lcd.setCursor(0, 1);
    lcd.print(etiquetas[carta1]);
    lcd.print("=");
    lcd.print(valorALetra(tablero[carta1]));
    lcd.print(" ");
    lcd.print(etiquetas[carta2]);
    lcd.print("=");
    lcd.print(valorALetra(tablero[carta2]));
    delay(1800);

  } else {
    int siguiente = (jugadorActual == 1) ? 2 : 1;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No coinciden");
    lcd.setCursor(0, 1);
    lcd.print("Turno J");
    lcd.print(siguiente);
    delay(1800);

    jugadorActual = siguiente;
  }
}

int leerCartaValida(int cartaBloqueada) {
  while (true) {
    char tecla = teclado.getKey();

    if (tecla) {
      int indice = teclaAIndice(tecla);

      if (indice == -1) {
        continue;
      }

      if (resueltas[indice]) {
        mostrarMensajeBreve("Ya conseguida", "Elige otra");
        continue;
      }

      if (indice == cartaBloqueada) {
        mostrarMensajeBreve("Carta repetida", "Elige otra");
        continue;
      }

      return indice;
    }
  }
}

int teclaAIndice(char tecla) {
  for (int i = 0; i < NUM_CARTAS; i++) {
    if (etiquetas[i] == tecla) {
      return i;
    }
  }
  return -1;
}

char valorALetra(int valor) {
  return 'A' + valor;   // 0->A, 1->B, ..., 7->H
}

void mostrarCabecera() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("J");
  lcd.print(jugadorActual);
  lcd.print(" P1:");
  lcd.print(puntosJ1);
  lcd.print(" P2:");
  lcd.print(puntosJ2);
}

void mostrarUnaCarta(int carta) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jugador ");
  lcd.print(jugadorActual);
  lcd.setCursor(0, 1);
  lcd.print(etiquetas[carta]);
  lcd.print(" = ");
  lcd.print(valorALetra(tablero[carta]));
}

void mostrarDosCartas(int carta1, int carta2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(etiquetas[carta1]);
  lcd.print("=");
  lcd.print(valorALetra(tablero[carta1]));
  lcd.print(" ");
  lcd.print(etiquetas[carta2]);
  lcd.print("=");
  lcd.print(valorALetra(tablero[carta2]));

  lcd.setCursor(0, 1);
  if (tablero[carta1] == tablero[carta2]) {
    lcd.print("Son pareja");
  } else {
    lcd.print("No son pareja");
  }
}

void mostrarMensajeBreve(const char* linea1, const char* linea2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linea1);
  lcd.setCursor(0, 1);
  lcd.print(linea2);
  delay(1000);
  mostrarCabecera();
}

void mostrarFinal() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fin P1:");
  lcd.print(puntosJ1);
  lcd.print(" P2:");
  lcd.print(puntosJ2);

  lcd.setCursor(0, 1);
  if (puntosJ1 > puntosJ2) {
    lcd.print("Gana Jugador 1");
  } else if (puntosJ2 > puntosJ1) {
    lcd.print("Gana Jugador 2");
  } else {
    lcd.print("Empate");
  }

  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pulsa una tecla");
  lcd.setCursor(0, 1);
  lcd.print("para reiniciar");
}

void esperarReinicio() {
  while (true) {
    char tecla = teclado.getKey();
    if (tecla) {
      iniciarJuego();
      return;
    }
  }
}

void imprimirTableroPorSerial() {
  Serial.println("Tablero mezclado:");
  for (int i = 0; i < NUM_CARTAS; i++) {
    Serial.print(etiquetas[i]);
    Serial.print(":");
    Serial.print(valorALetra(tablero[i]));
    Serial.print("  ");

    if ((i + 1) % 4 == 0) {
      Serial.println();
    }
  }
  Serial.println();
}