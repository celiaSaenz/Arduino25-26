int tiempo=200;
int n;

void setup() { //comienza la configuracion
  for (n=5;n<9;n++) {
    pinMode (n, OUTPUT);
  }
}
void secuencia() {
  for (n=5;n<9;n++) {
    digitalWrite (n, HIGH);
    delay (tiempo);
    digitalWrite (n, LOW);
    delay (tiempo);
  }
}

void loop() {
  secuencia();
}
