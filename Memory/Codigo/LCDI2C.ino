#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);  // prueba tambien 0x27

void setup() {
  lcd.init();          // si no va, prueba lcd.begin(16,2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Prueba LCD");
  lcd.setCursor(0, 1);
  lcd.print("Funciona");
}

void loop() {
}