#include <LiquidCrystal.h>
#include <DHT.h>

// --- Configuración de Hardware ---

// 1. Configuración de la Pantalla LCD (Modo 4 bits)
// Pines: RS, EN, D4, D5, D6, D7
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// 2. Sensor DHT11
#define DHTPIN 8      
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

// 3. Actuadores
const int ledAlarma = 9;  // Movido al pin 9
const int buzzer = 10;    // Movido al pin 10

// Umbral de temperatura
const int umbralTemp = 28;

void setup() {
  pinMode(ledAlarma, OUTPUT);
  pinMode(buzzer, OUTPUT);

  dht.begin();
  
  // Iniciar LCD (16 columnas, 2 filas)
  lcd.begin(16, 2);
  
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    lcd.setCursor(0,0);
    lcd.print("Error Sensor");
    return;
  }

  // --- Mostrar en LCD ---
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");

  lcd.setCursor(0,1);
  lcd.print("Hum:  ");
  lcd.print(h);
  lcd.print(" %");

  // --- Alarma ---
  if (t >= umbralTemp) {
    digitalWrite(ledAlarma, HIGH);
    tone(buzzer, 1000);
  } else {
    digitalWrite(ledAlarma, LOW);
    noTone(buzzer);
  }

  delay(2000);
}
