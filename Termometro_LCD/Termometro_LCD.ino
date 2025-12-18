#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// --- Configuración de Hardware ---
// Sensor DHT11
#define DHTPIN 2     // Pin digital donde conectamos el sensor
#define DHTTYPE DHT11   // Definimos el tipo de sensor
DHT dht(DHTPIN, DHTTYPE);

// Pantalla LCD I2C (Dirección usualmente 0x27 o 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);  

// Actuadores
const int ledAlarma = 8;
const int buzzer = 9;

// Umbral de temperatura para la alarma
const int umbralTemp = 28; // Si pasa de 28°C, suena la alarma

void setup() {
  // Iniciar componentes
  pinMode(ledAlarma, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  // Iniciar sensor
  dht.begin();
  
  // Iniciar LCD
  lcd.init();
  lcd.backlight(); // Encender luz de fondo
  
  // Mensaje de bienvenida
  lcd.setCursor(0,0);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Leer temperatura y humedad
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Comprobar si la lectura falló
  if (isnan(h) || isnan(t)) {
    lcd.setCursor(0,0);
    lcd.print("Error Sensor");
    return;
  }

  // --- Mostrar en LCD ---
  // Fila 0: Temperatura
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");

  // Fila 1: Humedad
  lcd.setCursor(0,1);
  lcd.print("Hum:  ");
  lcd.print(h);
  lcd.print(" %");

  // --- Lógica de Alarma ---
  if (t >= umbralTemp) {
    digitalWrite(ledAlarma, HIGH);
    tone(buzzer, 1000); // Sonido agudo
  } else {
    digitalWrite(ledAlarma, LOW);
    noTone(buzzer);
  }

  delay(2000); // Actualizar cada 2 segundos
}
