int motorPin = 9;

void setup() {
  pinMode(motorPin, OUTPUT);
}

void loop() {
  analogWrite(motorPin, 200);
  delay(3000);

  analogWrite(motorPin, 0);
  delay(2000);
}