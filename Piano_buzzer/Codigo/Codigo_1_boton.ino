int boton = 2;    // Pin donde conectamos el botón
int buzzer = 10;  // Pin donde conectamos el buzzer

void setup() {
  pinMode(boton, INPUT_PULLUP); 
  pinMode(buzzer, OUTPUT); // Configura el buzzer como salida
}

void loop() {
  int estadoBoton = digitalRead(boton); // Lee el estado del botón

  if (estadoBoton == LOW) { 
    tone(buzzer, 440); // Emite una nota de 440Hz (Nota La)
  } else {
    noTone(buzzer);    // Detiene el sonido
  }
}