#include "NewPing.h"
#define PIN_TRIG 12   // Pin del Arduino conectado al pin Trigger del sensor de ultrasonidos
#define PIN_ECHO 8   // Pin del Arduino conectado al pin Echo del sensor de ultrasonidos
#define MAX_DISTANCIA 100  // Distancia máxima a detectar en cm.
NewPing sonar(PIN_TRIG, PIN_ECHO, MAX_DISTANCIA);
// MOTOR 1
int IN1 = 2;
int IN2 = 7;
int ENA = 6;
// MOTOR 2
int IN3 = 4;
int IN4 = 3;
int ENB = 5;
long randomNumber;
const int PinLedRojo = 11;
const int PinLedVerde = 10;
const int PinLedAzul = 9;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(PinLedVerde, OUTPUT);
  pinMode(PinLedRojo, OUTPUT);
  pinMode(PinLedAzul, OUTPUT);
  randomSeed(analogRead(A0));  
}

void loop() {
  delay(1000);
  int tiempo = sonar.ping_median();
  int distancia = tiempo / US_ROUNDTRIP_CM;
  // Imprimir el tiempo medido en la consola
  Serial.print("Tiempo: ");
  Serial.print(tiempo);
  Serial.println(" microsegundos");
  // Imprimir la distancia medida en la consola
  Serial.print("Distancia: ");
  // US_ROUNDTRIP_CM constante para determinar la distancia. Convertir el tiempo en distancia (0 = indica fuera de rango)
  Serial.print(distancia);
  Serial.println(" cm");
  /*  */
  if (distancia > 0){  // hay espacio
    if(distancia < 30){
      //parar();
      if(distancia > 20){
        rojo();
        retrocede();
        delay(200);
        parada(100);
      }else{
        randomNumber = random(1,3);
        Serial.print("El numero aleatorio es = ");
        Serial.println(randomNumber);
        if (randomNumber == 1){
          azul();
          izquierda();
          delay(400);
          parada(500);
        }else{
          azul();
          derecha();
          delay(400);
          parada(500);
        }
      }
    }else{
      verde();
      avanza();
      //delay(200);
      //parada(500);
    }
  }else{
    verde();
    avanza();
  }
}
void parada(uint16_t tiempo) {
  parar();  // Para los motores
  delay(tiempo);        // Espera el tiempo que se le indique.
}

void avanza(){
 // MOTOR 1 
  analogWrite (ENA, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // MOTOR 2
  analogWrite(ENB, 150);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void retrocede(){
 // MOTOR 1 
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // MOTOR 2
  digitalWrite(ENB, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void derecha(){
 // MOTOR 1 
  analogWrite (ENA, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // MOTOR 2
  analogWrite (ENB, 150);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void izquierda(){
 // MOTOR 1 
  analogWrite (ENA, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // MOTOR 2
  analogWrite (ENB, 150);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void parar(){
 // MOTOR 1 
  digitalWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  // MOTOR 2
  digitalWrite(ENB, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void verde(){
  Serial.println("¡Verde!");
  digitalWrite(PinLedRojo, LOW);
  digitalWrite(PinLedVerde, HIGH);
  digitalWrite(PinLedAzul, LOW);
}
void rojo(){
  Serial.println("¡Rojo!");
  digitalWrite(PinLedRojo, HIGH);
  digitalWrite(PinLedVerde, LOW);
  digitalWrite(PinLedAzul, LOW);
}
void azul(){
  Serial.println("¡Azul!");
  digitalWrite(PinLedRojo, LOW);
  digitalWrite(PinLedVerde, LOW);
  digitalWrite(PinLedAzul, HIGH);
}