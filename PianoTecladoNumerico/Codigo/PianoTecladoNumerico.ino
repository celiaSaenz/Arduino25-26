#include <Keypad.h>

const byte FILAS = 4;
const byte COLUMNAS = 4;

char teclas[FILAS][COLUMNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinesFilas[FILAS] = {9, 8, 7, 6};
byte pinesColumnas[COLUMNAS] = {5, 4, 3, 2};

Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

int buzzer = 10;

// Frecuencias de notas
int DO = 262;
int RE = 294;
int MI = 330;
int FA = 349;
int SOL = 392;
int LA = 440;
int SI = 494;

void setup() {
  pinMode(buzzer, OUTPUT);
}

void loop() {
  char tecla = teclado.getKey();

  if (tecla) {
    switch(tecla) {
      case '1': tone(buzzer, DO); break;
      case '2': tone(buzzer, RE); break;
      case '3': tone(buzzer, MI); break;
      case '4': tone(buzzer, FA); break;
      case '5': tone(buzzer, SOL); break;
      case '6': tone(buzzer, LA); break;
      case '7': tone(buzzer, SI); break;
      default: noTone(buzzer); break;
    }
    delay(300);
    noTone(buzzer);
  }
}