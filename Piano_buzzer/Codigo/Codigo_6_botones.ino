// Pines de botones
int botones[] = {2, 3, 4, 5, 6, 7};

// Frecuencias de notas (DO, RE, MI, FA, SOL)
int notas[] = {262, 294, 330, 349, 392, 440};

int buzzer = 10;
int totalBotones = 6;

void setup() {
  for (int i = 0; i < totalBotones; i++) {
    pinMode(botones[i], INPUT_PULLUP); // Botones conectan a GND
  }
  pinMode(buzzer, OUTPUT);
}

void loop() {
  bool algunBotonPresionado = false; // Bandera para saber si tocamos algo

  for (int i = 0; i < totalBotones; i++) {
    if (digitalRead(botones[i]) == LOW) { // Si se presiona
      tone(buzzer, notas[i]);             // Suena la nota
      algunBotonPresionado = true;        // Marcamos que estamos tocando
    }
  }

  // Si NINGÚN botón se presionó en este ciclo, apagamos el sonido.
  // Esto permite mantener la nota sonando si dejas el dedo puesto.
  if (algunBotonPresionado == false) {
    noTone(buzzer);
  }
  
  // Quitamos el delay para que la respuesta sea instantánea
}
