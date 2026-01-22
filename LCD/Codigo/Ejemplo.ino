// Incluyendo el codigo de la libreria
#include <LiquidCrystal.h> 
// Initializando la libreria con los numeros de los pines
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Configurando el numero de filas y columnas:
  lcd.begin(16, 2);
  // Imprimiendo el mensaje en la pantalla.
  lcd.print("Hola Mundo!");
}

void loop() {
  // Poniendo el cursor en la columna 0, linea 1
  // (Nota: linea1 es la segunda fila, desde el inicio contado desde 0):
  lcd.setCursor(0, 1);
  // Imprimiendo el numero de mili segundos desde el ultimo reinicio:
  lcd.print(millis()/1000);
}