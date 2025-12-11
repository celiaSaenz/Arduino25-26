void setup() { //comienza la configuracion
  pinMode(13, OUTPUT); //configura el pin 13 como de salida
} //termina la configuracion

void loop() { //comienza el bucle principal del programa
  digitalWrite(13, HIGH); //envia 5V al pin (salida) 13
  delay (500); //espera 500 ms pin 13 con 5V
  digitalWrite(13, LOW); //envia 0V al pin (salida) 13
  delay (100); //espera 100 ms pin 13 con 0V
}
