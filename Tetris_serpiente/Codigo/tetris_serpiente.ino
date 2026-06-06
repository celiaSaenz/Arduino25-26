#include <LedControl.h>
#include <LiquidCrystal.h>

// ===================== PINES =====================
// Matriz LED MAX7219: DIN, CLK, CS
const byte PIN_MATRIX_DIN = 12;
const byte PIN_MATRIX_CLK = 11;
const byte PIN_MATRIX_CS  = 10;

// LCD 16x2 en modo paralelo: RS, EN, D4, D5, D6, D7
// IMPORTANTE: en tu Tetris original el LCD usaba 10, 11 y 12,
// que chocan con la matriz LED. Por eso aqui lo cambio a 4-9.
const byte PIN_LCD_RS = 4;
const byte PIN_LCD_EN = 5;
const byte PIN_LCD_D4 = 6;
const byte PIN_LCD_D5 = 7;
const byte PIN_LCD_D6 = 8;
const byte PIN_LCD_D7 = 9;

// Joystick
const byte PIN_JOY_X  = A0;
const byte PIN_JOY_Y  = A1;
const byte PIN_JOY_SW = 2;

// Buzzer
const byte PIN_BUZZER = 3;

// Botones para elegir juego
// Conectar cada boton entre el pin y GND. No hace falta resistencia externa.
const byte BTN_TETRIS     = A2;
const byte BTN_SERPIENTE  = A3;

LedControl lc = LedControl(PIN_MATRIX_DIN, PIN_MATRIX_CLK, PIN_MATRIX_CS, 1);
LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

// Prototipos de funciones
bool botonPulsado(byte pin);
void setPixel(int x, int y, bool encendido);
void mostrarMenu();
void leerBotonesDeJuego();
void iniciarTetris();
void loopTetris();
void tetrisActualizarLCD();
void tetrisNuevaPieza();
bool tetrisColisionEnPosicionInicial();
void tetrisLeerJoystick();
bool tetrisColision();
void tetrisActualizarJuego();
void tetrisFijarPieza();
void tetrisEliminarLineas();
void tetrisDibujarTablero();
void iniciarSerpiente();
void loopSerpiente();
void serpienteStartGame();
void serpienteLeerJoystick();
void serpienteCambiarDireccion();
void serpienteFueraDePantalla();
void serpienteComprobarChoqueConCola();
void serpienteComerComida();
void serpienteActualizarCola();
void serpienteNuevaComida();
void serpienteDibujar();
void serpienteMostrarGameOver();

// ===================== CONTROL GENERAL =====================
enum JuegoActual {
  MENU,
  JUEGO_TETRIS,
  JUEGO_SERPIENTE
};

JuegoActual juegoActual = MENU;
unsigned long ultimoCambioJuego = 0;

bool botonPulsado(byte pin) {
  return digitalRead(pin) == LOW;   // INPUT_PULLUP: pulsado = LOW
}

void setPixel(int x, int y, bool encendido) {
  if (x >= 0 && x < 8 && y >= 0 && y < 8) {
    lc.setLed(0, y, x, encendido);
  }
}

void mostrarMenu() {
  lc.clearDisplay(0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("A2: Tetris");
  lcd.setCursor(0, 1);
  lcd.print("A3: Serpiente");
}

void leerBotonesDeJuego() {
  if (millis() - ultimoCambioJuego < 250) return; // antirrebote simple

  if (botonPulsado(BTN_TETRIS) && juegoActual != JUEGO_TETRIS) {
    iniciarTetris();
    ultimoCambioJuego = millis();
  } else if (botonPulsado(BTN_SERPIENTE) && juegoActual != JUEGO_SERPIENTE) {
    iniciarSerpiente();
    ultimoCambioJuego = millis();
  }
}

void setup() {
  lcd.begin(16, 2);

  lc.shutdown(0, false);
  lc.setIntensity(0, 5);
  lc.clearDisplay(0);

  pinMode(PIN_JOY_SW, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(BTN_TETRIS, INPUT_PULLUP);
  pinMode(BTN_SERPIENTE, INPUT_PULLUP);

  randomSeed(analogRead(A5));
  mostrarMenu();
}

void loop() {
  leerBotonesDeJuego();

  if (juegoActual == MENU) {
    // Esperando a que se pulse A2 o A3.
    delay(50);
  } else if (juegoActual == JUEGO_TETRIS) {
    loopTetris();
  } else if (juegoActual == JUEGO_SERPIENTE) {
    loopSerpiente();
  }
}

// ============================================================
// ========================= TETRIS ============================
// ============================================================

byte tetrisTablero[8] = {0};
int tetrisPiezaX = 3;
int tetrisPiezaY = 0;
int tetrisRotacion = 0;
unsigned long tetrisUltimaCaida = 0;
unsigned long tetrisVelocidad = 500;
int tetrisPuntuacion = 0;
int tetrisMejorPuntuacion = 0;
bool tetrisGameOver = false;
int tetrisPiezaActual = 0;

const byte tetrisPiezas[7][4][4] = {
  { // O
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

void iniciarTetris() {
  juegoActual = JUEGO_TETRIS;
  lc.setIntensity(0, 5);

  for (int i = 0; i < 8; i++) tetrisTablero[i] = 0;
  tetrisPiezaX = 3;
  tetrisPiezaY = 0;
  tetrisRotacion = 0;
  tetrisUltimaCaida = millis();
  tetrisVelocidad = 500;
  tetrisPuntuacion = 0;
  tetrisGameOver = false;

  lc.clearDisplay(0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tetris");
  delay(500);

  tetrisNuevaPieza();
  tetrisActualizarLCD();
}

void loopTetris() {
  if (!tetrisGameOver) {
    tetrisLeerJoystick();
    tetrisActualizarJuego();
    tetrisDibujarTablero();
    tetrisActualizarLCD();
    delay(100);
  }
}

void tetrisActualizarLCD() {
  lcd.setCursor(0, 0);
  lcd.print("Puntos: ");
  lcd.print(tetrisPuntuacion);
  lcd.print("    ");

  lcd.setCursor(0, 1);
  lcd.print("Record: ");
  lcd.print(tetrisMejorPuntuacion);
  lcd.print("    ");
}

void tetrisNuevaPieza() {
  tetrisPiezaActual = random(7);
  tetrisPiezaX = 3;
  tetrisPiezaY = 0;
  tetrisRotacion = 0;

  if (tetrisColisionEnPosicionInicial()) {
    tetrisGameOver = true;
    tone(PIN_BUZZER, 200, 1000);

    if (tetrisPuntuacion > tetrisMejorPuntuacion) {
      tetrisMejorPuntuacion = tetrisPuntuacion;
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER");
    lcd.setCursor(0, 1);
    lcd.print("Puntos: ");
    lcd.print(tetrisPuntuacion);
    delay(2000);

    iniciarTetris();
  }
}

bool tetrisColisionEnPosicionInicial() {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (tetrisPiezas[tetrisPiezaActual][tetrisRotacion][y] & (1 << (3 - x))) {
        int px = tetrisPiezaX + x;
        int py = tetrisPiezaY + y;
        if (py >= 0 && py < 8 && px >= 0 && px < 8 && bitRead(tetrisTablero[py], 7 - px)) return true;
      }
    }
  }
  return false;
}

void tetrisLeerJoystick() {
  int x = analogRead(PIN_JOY_X);
  int y = analogRead(PIN_JOY_Y);
  bool btn = !digitalRead(PIN_JOY_SW);

  if (x < 300) {
    tetrisPiezaX--;
    if (tetrisColision()) tetrisPiezaX++;
    else delay(100);
  }

  if (x > 700) {
    tetrisPiezaX++;
    if (tetrisColision()) tetrisPiezaX--;
    else delay(100);
  }

  if (btn) {
    int rotacionAnterior = tetrisRotacion;
    tetrisRotacion = (tetrisRotacion + 1) % 4;

    if (tetrisColision()) {
      if (tetrisPiezaX < 3) tetrisPiezaX++;
      else if (tetrisPiezaX > 3) tetrisPiezaX--;
      if (tetrisColision()) tetrisRotacion = rotacionAnterior;
    }

    if (tetrisRotacion != rotacionAnterior) {
      tone(PIN_BUZZER, 800, 50);
      delay(200);
    }
  }

  if (y > 700) tetrisVelocidad = 300;
  else tetrisVelocidad = 700;
}

bool tetrisColision() {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (tetrisPiezas[tetrisPiezaActual][tetrisRotacion][y] & (1 << (3 - x))) {
        int px = tetrisPiezaX + x;
        int py = tetrisPiezaY + y;

        if (px < 0 || px >= 8 || py >= 8) return true;
        if (py >= 0 && bitRead(tetrisTablero[py], 7 - px)) return true;
      }
    }
  }
  return false;
}

void tetrisActualizarJuego() {
  if (millis() - tetrisUltimaCaida > tetrisVelocidad) {
    tetrisPiezaY++;

    if (tetrisColision()) {
      tetrisPiezaY--;
      tetrisFijarPieza();
      tetrisEliminarLineas();
      tetrisNuevaPieza();
    }

    tetrisUltimaCaida = millis();
  }
}

void tetrisFijarPieza() {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (tetrisPiezas[tetrisPiezaActual][tetrisRotacion][y] & (1 << (3 - x))) {
        int px = tetrisPiezaX + x;
        int py = tetrisPiezaY + y;

        if (py >= 0 && py < 8 && px >= 0 && px < 8) {
          tetrisTablero[py] |= (1 << (7 - px));
        }
      }
    }
  }
  tone(PIN_BUZZER, 400, 100);
}

void tetrisEliminarLineas() {
  int lineasCompletas = 0;

  for (int y = 7; y >= 0; y--) {
    if (tetrisTablero[y] == B11111111) {
      lineasCompletas++;
      for (int yy = y; yy > 0; yy--) {
        tetrisTablero[yy] = tetrisTablero[yy - 1];
      }
      tetrisTablero[0] = 0;
      tone(PIN_BUZZER, 1000, 200);
      y++;
    }
  }

  switch (lineasCompletas) {
    case 1: tetrisPuntuacion += 100; break;
    case 2: tetrisPuntuacion += 300; break;
    case 3: tetrisPuntuacion += 500; break;
    case 4: tetrisPuntuacion += 800; break;
  }
}

void tetrisDibujarTablero() {
  lc.clearDisplay(0);

  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      setPixel(x, y, bitRead(tetrisTablero[y], 7 - x));
    }
  }

  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (tetrisPiezas[tetrisPiezaActual][tetrisRotacion][y] & (1 << (3 - x))) {
        int px = tetrisPiezaX + x;
        int py = tetrisPiezaY + y;
        setPixel(px, py, true);
      }
    }
  }
}

// ============================================================
// ======================= SERPIENTE ===========================
// ============================================================

const int serpienteAncho = 8;
const int serpienteAlto = 8;
int serpienteX = 4;
int serpienteY = 4;
int comidaX = 0;
int comidaY = 0;
int serpienteScore = 0;
int serpienteSize = 1;
char serpienteDireccion = ' ';
int colaX[100];
int colaY[100];
bool serpienteGameOver = false;

void iniciarSerpiente() {
  juegoActual = JUEGO_SERPIENTE;
  lc.setIntensity(0, 1);
  lc.clearDisplay(0);

  serpienteX = 4;
  serpienteY = 4;
  serpienteScore = 0;
  serpienteSize = 1;
  serpienteDireccion = ' ';
  serpienteGameOver = false;

  for (int i = 0; i < 100; i++) {
    colaX[i] = 0;
    colaY[i] = 0;
  }

  serpienteNuevaComida();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Serpiente");
  lcd.setCursor(0, 1);
  lcd.print("Score: 0");
  delay(500);
}

void loopSerpiente() {
  if (serpienteGameOver) {
    serpienteMostrarGameOver();
  } else {
    serpienteStartGame();
  }
}

void serpienteStartGame() {
  serpienteLeerJoystick();
  serpienteCambiarDireccion();
  serpienteFueraDePantalla();
  serpienteComprobarChoqueConCola();
  serpienteComerComida();
  serpienteActualizarCola();
  serpienteDibujar();

  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(serpienteScore);
  lcd.print("    ");

  delay(300);
}

void serpienteLeerJoystick() {
  int x = analogRead(PIN_JOY_X);
  int y = analogRead(PIN_JOY_Y);

  if (x > 1000 && serpienteDireccion != 'd') {
    serpienteDireccion = 'u';
  } else if (x < 100 && serpienteDireccion != 'u') {
    serpienteDireccion = 'd';
  } else if (y > 1000 && serpienteDireccion != 'r') {
    serpienteDireccion = 'l';
  } else if (y < 100 && serpienteDireccion != 'l') {
    serpienteDireccion = 'r';
  }
}

void serpienteCambiarDireccion() {
  switch (serpienteDireccion) {
    case 'l': serpienteX--; break;
    case 'r': serpienteX++; break;
    case 'u': serpienteY--; break;
    case 'd': serpienteY++; break;
  }
}

void serpienteFueraDePantalla() {
  if (serpienteX >= serpienteAncho) serpienteX = 0;
  else if (serpienteX < 0) serpienteX = serpienteAncho - 1;

  if (serpienteY >= serpienteAlto) serpienteY = 0;
  else if (serpienteY < 0) serpienteY = serpienteAlto - 1;
}

void serpienteComprobarChoqueConCola() {
  for (int i = 1; i < serpienteSize; i++) {
    if (colaX[i] == serpienteX && colaY[i] == serpienteY) {
      serpienteGameOver = true;
    }
  }
}

void serpienteComerComida() {
  if (serpienteX == comidaX && serpienteY == comidaY) {
    serpienteScore++;
    serpienteSize++;
    if (serpienteSize > 99) serpienteSize = 99;
    tone(PIN_BUZZER, 900, 80);
    serpienteNuevaComida();
  }
}

void serpienteActualizarCola() {
  int previousX = colaX[0];
  int previousY = colaY[0];
  int prevX, prevY;

  colaX[0] = serpienteX;
  colaY[0] = serpienteY;

  for (int i = 1; i < serpienteSize; i++) {
    prevX = colaX[i];
    prevY = colaY[i];
    colaX[i] = previousX;
    colaY[i] = previousY;
    previousX = prevX;
    previousY = prevY;
  }
}

void serpienteNuevaComida() {
  bool posicionValida = false;

  while (!posicionValida) {
    comidaX = random(serpienteAncho);
    comidaY = random(serpienteAlto);
    posicionValida = true;

    if (comidaX == serpienteX && comidaY == serpienteY) {
      posicionValida = false;
    }

    for (int i = 0; i < serpienteSize; i++) {
      if (colaX[i] == comidaX && colaY[i] == comidaY) {
        posicionValida = false;
      }
    }
  }
}

void serpienteDibujar() {
  lc.clearDisplay(0);
  setPixel(comidaX, comidaY, true);
  setPixel(serpienteX, serpienteY, true);

  for (int k = 0; k < serpienteSize; k++) {
    setPixel(colaX[k], colaY[k], true);
  }
}

void serpienteMostrarGameOver() {
  tone(PIN_BUZZER, 200, 500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GAME OVER");
  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(serpienteScore);

  for (int i = 0; i < serpienteAlto; i++) {
    for (int j = 0; j < serpienteAncho; j++) {
      setPixel(j, i, true);
      delay(30);
    }
  }

  delay(1000);
  iniciarSerpiente();
}
