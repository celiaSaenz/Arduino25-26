// Proyecto: Creación de Semáforo Simple

// Arreglo de LEDs: 0 = Rojo, 1 = Amarillo, 2 = Verde
int leds[] = {3, 4, 5};

// Tiempos en milisegundos
int tiempo1 = 3000; // 3 segundos
int tiempo2 = 1000; // 1 segundo

void setup() {
  // Configurar los pines de los LEDs como salidas
  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // Encender LED Rojo
  digitalWrite(leds[0], HIGH);
  delay(tiempo1);
  digitalWrite(leds[0], LOW);

  // Encender LED Verde
  digitalWrite(leds[2], HIGH);
  delay(tiempo1);
  digitalWrite(leds[2], LOW);

  // Encender LED Amarillo
  digitalWrite(leds[1], HIGH);
  delay(tiempo2);
  digitalWrite(leds[1], LOW);
}
