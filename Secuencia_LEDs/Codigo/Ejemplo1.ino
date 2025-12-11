int tiempo=200; //declara una variable como entero y de valor 200

void setup() { //comienza la configuracion
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
}

void loop() { //comienza el bucle principal del programa
  digitalWrite(5,HIGH);
  delay(tiempo);
  digitalWrite(5,LOW);
  delay(tiempo);
  digitalWrite(6,HIGH);
  delay(tiempo);
  digitalWrite(6,LOW);
  delay(tiempo);
  digitalWrite(7,HIGH);
  delay(tiempo);
  digitalWrite(7,LOW);
  delay(tiempo);
  digitalWrite(8,HIGH);
  delay(tiempo);
  digitalWrite(8,LOW);
  delay(tiempo);
}
