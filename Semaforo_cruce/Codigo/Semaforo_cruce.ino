// Cruce de Semáforos - Arduino Uno

// Semáforo 1
const int rojo1 = 3;
const int amarillo1 = 4;
const int verde1 = 5;

// Semáforo 2
const int rojo2 = 6;
const int amarillo2 = 7;
const int verde2 = 8;

void setup() {
  // Configurar todos los pines como salida
  pinMode(rojo1, OUTPUT);
  pinMode(amarillo1, OUTPUT);
  pinMode(verde1, OUTPUT);

  pinMode(rojo2, OUTPUT);
  pinMode(amarillo2, OUTPUT);
  pinMode(verde2, OUTPUT);
}

void loop() {
  // FASE 1: Semáforo 1 Rojo, Semáforo 2 Verde
  digitalWrite(rojo1, HIGH);
  digitalWrite(amarillo1, LOW);
  digitalWrite(verde1, LOW);

  digitalWrite(rojo2, LOW);
  digitalWrite(amarillo2, LOW);
  digitalWrite(verde2, HIGH);

  delay(3000);

  // FASE 2: Semáforo 2 Amarillo
  digitalWrite(verde2, LOW);
  digitalWrite(amarillo2, HIGH);

  delay(500);

  // FASE 3: Semáforo 1 Verde, Semáforo 2 Rojo
  digitalWrite(rojo1, LOW);
  digitalWrite(verde1, HIGH);

  digitalWrite(amarillo2, LOW);
  digitalWrite(rojo2, HIGH);

  delay(3000);

  // FASE 4: Semáforo 1 Amarillo
  digitalWrite(verde1, LOW);
  digitalWrite(amarillo1, HIGH);

  delay(500);

  // Apagar amarillo 1 antes de reiniciar el ciclo
  digitalWrite(amarillo1, LOW);
}
