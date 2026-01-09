#include <Servo.h>

Servo puerta;

// Pines
const int trigPin = 9;
const int echoPin = 10;

long duracion;
int distancia;

void setup() {
  puerta.attach(6);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  puerta.write(0); // Puerta cerrada
}

void loop() {
  // Enviar pulso ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leer eco
  duracion = pulseIn(echoPin, HIGH);
  distancia = duracion * 0.034 / 2;

  if (distancia > 0 && distancia < 15) {
    // Coche detectado
    puerta.write(90); // Abrir puerta
  } else {
    // Garaje libre
    puerta.write(0); // Cerrar puerta
  }

  delay(500);
}
