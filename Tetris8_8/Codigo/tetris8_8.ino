#include <LedControl.h>
#include <LiquidCrystal.h>

// Configuración LCD (pines: RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Configuración matriz LED (DIN, CLK, CS, número de matrices)
LedControl lc = LedControl(12, 11, 10, 1);

// Pines de control
#define VRX A0    // Joystick X
#define VRY A1    // Joystick Y
#define SW 2      // Botón joystick
#define BUZZER 3  // Buzzer

// Variables del juego
byte tablero[8] = {0};  // Tablero 8x8
int piezaX = 3, piezaY = 0;
int rotacion = 0;
unsigned long ultimaCaida = 0;
unsigned long velocidad = 500;
int puntuacion = 0;
int mejorPuntuacion = 0;
bool gameOver = false;

// Definición de piezas (7 piezas, 4 rotaciones cada una)
const byte piezas[7][4][4] = {
  { // Cuadrado (O)
    {B0110, B0110, B0000, B0000},
    {B0110, B0110, B0000, B0000},
    {B0110, B0110, B0000, B0000},
    {B0110, B0110, B0000, B0000}
  },
  { // I
    {B0000, B1111, B0000, B0000},
    {B0010, B0010, B0010, B0010},
    {B0000, B1111, B0000, B0000},
    {B0010, B0010, B0010, B0010}
  },
  { // L
    {B0000, B1110, B0010, B0000},
    {B0100, B0100, B0110, B0000},
    {B1000, B1110, B0000, B0000},
    {B0110, B0100, B0100, B0000}
  },
  { // J
    {B0010, B1110, B0000, B0000},
    {B0110, B0010, B0010, B0000},
    {B0000, B1110, B1000, B0000},
    {B0100, B0100, B0110, B0000}
  },
  { // S
    {B0000, B0110, B1100, B0000},
    {B0100, B0110, B0010, B0000},
    {B0000, B0110, B1100, B0000},
    {B0100, B0110, B0010, B0000}
  },
  { // Z
    {B0000, B1100, B0110, B0000},
    {B0010, B0110, B0100, B0000},
    {B0000, B1100, B0110, B0000},
    {B0010, B0110, B0100, B0000}
  },
  { // T
    {B0000, B1110, B0100, B0000},
    {B0100, B1100, B0100, B0000},
    {B0100, B1110, B0000, B0000},
    {B0100, B0110, B0100, B0000}
  }
};
int piezaActual = 0;

void setup() {
  // Inicializar LCD
  lcd.begin(16, 2);
  lcd.print("Tetris Arduino");
  delay(1000);
  lcd.clear();
  
  // Inicializar matriz LED
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  
  // Configurar pines
  pinMode(SW, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  randomSeed(analogRead(A4)); // Usar A4 para random
  
  nuevaPieza();
  actualizarLCD();
}

void loop() {
  if(!gameOver) {
    leerJoystick();
    actualizarJuego();
    dibujarTablero();
    actualizarLCD();
    delay(100);
  }
}

void actualizarLCD() {
  lcd.setCursor(0, 0);
  lcd.print("Puntos: ");
  lcd.print(puntuacion);
  lcd.print("    ");
  
  lcd.setCursor(0, 1);
  lcd.print("Record: ");
  lcd.print(mejorPuntuacion);
  lcd.print("    ");
}

void nuevaPieza() {
  piezaActual = random(7);
  piezaX = 3;
  piezaY = 0;
  rotacion = 0;
  
  if(colisionEnPosicionInicial()) {
    gameOver = true;
    tone(BUZZER, 200, 1000);
    
    // Actualizar record
    if(puntuacion > mejorPuntuacion) {
      mejorPuntuacion = puntuacion;
    }
    
    // Mostrar Game Over
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER");
    lcd.setCursor(0, 1);
    lcd.print("Puntos: ");
    lcd.print(puntuacion);
    
    delay(2000);
    
    // Reiniciar juego
    for(int i=0; i<8; i++) tablero[i] = 0;
    puntuacion = 0;
    gameOver = false;
    lcd.clear();
  }
}

bool colisionEnPosicionInicial() {
  for(int y=0; y<4; y++) {
    for(int x=0; x<4; x++) {
      if(piezas[piezaActual][rotacion][y] & (1 << (3 - x))) {
        int px = piezaX + x;
        int py = piezaY + y;
        
        if(py >= 0 && bitRead(tablero[py], 7 - px)) return true;
      }
    }
  }
  return false;
}

void leerJoystick() {
  int x = analogRead(VRX);
  int y = analogRead(VRY);
  bool btn = !digitalRead(SW);

  // Movimiento izquierda/derecha
  if(x < 300 && piezaX > 0) {
    piezaX--;
    if(colision()) piezaX++;
    else delay(100);
  }
  if(x > 700 && piezaX < 6) {
    piezaX++;
    if(colision()) piezaX--;
    else delay(100);
  }
  
  // Rotación
  if(btn) {
    int rotacionAnterior = rotacion;
    rotacion = (rotacion + 1) % 4;
    if(colision()) {
      // Ajustar posición si hay colisión
      if(piezaX < 3) piezaX++;
      else if(piezaX > 3) piezaX--;
      if(colision()) rotacion = rotacionAnterior;
    }
    if(rotacion != rotacionAnterior) {
      tone(BUZZER, 800, 50);
      delay(200);
    }
  }
  
  // Caída rápida
  if(y > 700) {
    velocidad = 300;
  } else {
    velocidad = 700;
  }
}

bool colision() {
  for(int y=0; y<4; y++) {
    for(int x=0; x<4; x++) {
      if(piezas[piezaActual][rotacion][y] & (1 << (3 - x))) {
        int px = piezaX + x;
        int py = piezaY + y;
        
        if(px < 0 || px >= 8 || py >= 8) return true;
        if(py >= 0 && bitRead(tablero[py], 7 - px)) return true;
      }
    }
  }
  return false;
}

void actualizarJuego() {
  if(millis() - ultimaCaida > velocidad) {
    piezaY++;
    
    if(colision()) {
      piezaY--;
      fijarPieza();
      eliminarLineas();
      nuevaPieza();
    }
    
    ultimaCaida = millis();
  }
}

void fijarPieza() {
  for(int y=0; y<4; y++) {
    for(int x=0; x<4; x++) {
      if(piezas[piezaActual][rotacion][y] & (1 << (3 - x))) {
        int px = piezaX + x;
        int py = piezaY + y;
        
        if(py >= 0 && py < 8 && px >= 0 && px < 8) {
          tablero[py] |= (1 << (7 - px));
        }
      }
    }
  }
  tone(BUZZER, 400, 100);
}

void eliminarLineas() {
  int lineasCompletas = 0;
  
  for(int y=7; y>=0; y--) {
    if(tablero[y] == B11111111) {
      lineasCompletas++;
      // Desplazar filas
      for(int yy=y; yy>0; yy--) {
        tablero[yy] = tablero[yy-1];
      }
      tablero[0] = 0;
      tone(BUZZER, 1000, 200);
      y++; // Revisar misma fila
    }
  }
  
  // Sistema de puntuación
  switch(lineasCompletas) {
    case 1: puntuacion += 100; break;
    case 2: puntuacion += 300; break;
    case 3: puntuacion += 500; break;
    case 4: puntuacion += 800; break;
  }
}

void dibujarTablero() {
  lc.clearDisplay(0);
  
  // Dibujar tablero
  for(int y=0; y<8; y++) {
    for(int x=0; x<8; x++) {
      lc.setLed(0, y, x, bitRead(tablero[y], 7 - x));
    }
  }
  
  // Dibujar pieza actual
  for(int y=0; y<4; y++) {
    for(int x=0; x<4; x++) {
      if(piezas[piezaActual][rotacion][y] & (1 << (3 - x))) {
        int px = piezaX + x;
        int py = piezaY + y;
        
        if(py >= 0 && py < 8 && px >= 0 && px < 8) {
          lc.setLed(0, py, px, true);
        }
      }
    }
  }
}