// Pines de botones
int botones[] = {2, 3, 4, 5, 6, 7};

// Frecuencias de notas (DO RE MI FA SOL LA SI DO)
int notas[] = {262, 294, 330, 349, 392, 440};

int buzzer = 10;
int totalBotones = 6;

void setup() {
  for (int i = 0; i < totalBotones; i++) {
    pinMode(botones[i], INPUT_PULLUP); // Usamos resistencias internas
  }
  pinMode(buzzer, OUTPUT);
}

void loop() {
  for (int i = 0; i < totalBotones; i++) {
    if (digitalRead(botones[i]) == LOW) { // Botón presionado
      tone(buzzer, notas[i]);             // Reproduce la nota
      delay(200);                         // Evita rebotes
    }
  }
  
  noTone(buzzer); // Apaga el buzzer cuando no se presiona nada
}

