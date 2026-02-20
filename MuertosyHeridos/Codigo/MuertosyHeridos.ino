#include <Keypad.h>

/* =======================
   CONFIGURACIÓN DEL JUEGO
   ======================= */
#define NUM_DIGITS 4          // Cambia a 3 si quieres (y ajusta LEDs si te apetece)
#define MAX_TRIES 12
#define ALLOW_REPEATS false   // típico: sin repetición
#define ALLOW_LEADING_ZERO false

/* =======================
   TECLADO 4x4
   ======================= */
const byte ROWS = 4;
const byte COLS = 4;

// Layout típico de 4x4:
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};   // R1..R4 -> D2..D5
byte colPins[COLS] = {5, 4, 3, 2};   // C1..C4 -> D6..D9

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

/* =======================
   LEDs
   ======================= */
const byte muertosLED[4] = {13, 12, 11, 10}; // hasta 4
const byte heridosLED[4] = {A3, A2, A1, A0}; // hasta 4

/* =======================
   ESTADO
   ======================= */
char secret[NUM_DIGITS + 1];
char guess[NUM_DIGITS + 1];
byte guessLen = 0;
int tries = 0;
bool gameOver = false;

/* =======================
   UTILIDADES
   ======================= */
void clearLeds() {
  for (int i = 0; i < 4; i++) {
    pinMode(muertosLED[i], OUTPUT);
    pinMode(heridosLED[i], OUTPUT);
    digitalWrite(muertosLED[i], LOW);
    digitalWrite(heridosLED[i], LOW);
  }
}

void showCounts(byte muertos, byte heridos) {
  clearLeds();
  for (byte i = 0; i < muertos && i < 4; i++) digitalWrite(muertosLED[i], HIGH);
  for (byte i = 0; i < heridos && i < 4; i++) digitalWrite(heridosLED[i], HIGH);
}

bool containsChar(const char *arr, byte n, char c) {
  for (byte i = 0; i < n; i++) if (arr[i] == c) return true;
  return false;
}

void generateSecret() {
  // Semilla “suficiente” para Arduino (ruido analógico)
  randomSeed(analogRead(A5) + micros());

  for (byte i = 0; i < NUM_DIGITS; i++) secret[i] = '\0';

  for (byte i = 0; i < NUM_DIGITS; i++) {
    while (true) {
      char d = char('0' + random(0, 10));

      if (!ALLOW_LEADING_ZERO && i == 0 && d == '0') continue;

      if (!ALLOW_REPEATS) {
        if (containsChar(secret, i, d)) continue;
      }
      secret[i] = d;
      break;
    }
  }
  secret[NUM_DIGITS] = '\0';
}

bool guessIsValid() {
  if (guessLen != NUM_DIGITS) return false;

  if (!ALLOW_REPEATS) {
    for (byte i = 0; i < NUM_DIGITS; i++) {
      for (byte j = i + 1; j < NUM_DIGITS; j++) {
        if (guess[i] == guess[j]) return false;
      }
    }
  }
  if (!ALLOW_LEADING_ZERO && guess[0] == '0') return false;

  return true;
}

void scoreGuess(const char *g, const char *s, byte &muertos, byte &heridos) {
  muertos = 0;
  heridos = 0;

  // Muertos: misma cifra, misma posición
  for (byte i = 0; i < NUM_DIGITS; i++) {
    if (g[i] == s[i]) muertos++;
  }

  // Heridos: cifra existe pero en otra posición (sin contar muertos)
  for (byte i = 0; i < NUM_DIGITS; i++) {
    if (g[i] == s[i]) continue; // ya contado como muerto
    for (byte j = 0; j < NUM_DIGITS; j++) {
      if (i == j) continue;
      if (g[i] == s[j] && g[j] != s[j]) { // evita “dobles conteos” simples en modo sin repetición
        heridos++;
        break;
      }
    }
  }
}

void resetGuess() {
  guessLen = 0;
  for (byte i = 0; i < NUM_DIGITS; i++) guess[i] = '\0';
  guess[NUM_DIGITS] = '\0';
}

void newGame() {
  tries = 0;
  gameOver = false;
  resetGuess();
  clearLeds();
  generateSecret();

  Serial.println();
  Serial.println("=== MUERTOS Y HERIDOS ===");
  Serial.print("Numero de cifras: "); Serial.println(NUM_DIGITS);
  Serial.println("Escribe digitos. '*' borra. '#' envia intento.");
  Serial.print("Intentos maximos: "); Serial.println(MAX_TRIES);
  Serial.println("-------------------------");
  // Serial.print("[DEBUG] Secreto: "); Serial.println(secret); // descomenta si quieres hacer pruebas
}

void winAnimation() {
  for (int k = 0; k < 6; k++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(muertosLED[i], (k % 2) ? HIGH : LOW);
      digitalWrite(heridosLED[i], (k % 2) ? LOW : HIGH);
    }
    delay(150);
  }
  clearLeds();
}

/* =======================
   SETUP / LOOP
   ======================= */
void setup() {
  Serial.begin(9600);
  clearLeds();
  newGame();
}

void loop() {
  char key = keypad.getKey();
  if (!key) return;

  if (gameOver) {
    // Tras terminar, pulsa 'D' para nueva partida (o '#')
    if (key == 'D' || key == '#') newGame();
    return;
  }

  if (key >= '0' && key <= '9') {
    if (guessLen < NUM_DIGITS) {
      guess[guessLen++] = key;
      guess[guessLen] = '\0';

      Serial.print("Entrada: ");
      Serial.println(guess);
    } else {
      Serial.println("Ya tienes todas las cifras. Pulsa '#' para enviar o '*' para borrar.");
    }
    return;
  }

  if (key == '*') {
    resetGuess();
    clearLeds();
    Serial.println("Borrado.");
    return;
  }

  if (key == '#') {
    if (!guessIsValid()) {
      Serial.println("Intento invalido (longitud / repetidos / cero inicial).");
      return;
    }

    tries++;
    byte muertos, heridos;
    scoreGuess(guess, secret, muertos, heridos);

    Serial.print("Intento "); Serial.print(tries); Serial.print(": ");
    Serial.print(guess);
    Serial.print(" -> Muertos="); Serial.print(muertos);
    Serial.print(" | Heridos="); Serial.println(heridos);

    showCounts(muertos, heridos);

    if (muertos == NUM_DIGITS) {
      Serial.println("✅ GANASTE. Pulsa 'D' o '#' para nueva partida.");
      winAnimation();
      gameOver = true;
      return;
    }

    if (tries >= MAX_TRIES) {
      Serial.print("❌ Fin. El numero era: ");
      Serial.println(secret);
      Serial.println("Pulsa 'D' o '#' para nueva partida.");
      gameOver = true;
      return;
    }

    // Siguiente intento
    resetGuess();
    return;
  }

  // Teclas A/B/C/D no se usan excepto D tras gameOver
}