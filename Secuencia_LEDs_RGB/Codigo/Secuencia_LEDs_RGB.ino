// --- SECCIÓN 1: Definición de Constantes ---
// Definimos los números de pines donde conectamos cada pata del LED RGB.
// Usamos 'const' porque estos números no cambiarán durante la ejecución.
const int ledRojo = 11;   // Pin digital 9 para el color Rojo (R)
const int ledVerde = 10; // Pin digital 10 para el color Verde (G)
const int ledAzul = 9;  // Pin digital 11 para el color Azul (B)

// --- SECCIÓN 2: Configuración Inicial (Setup) ---
// Esta parte se ejecuta una sola vez al encender el Arduino.
void setup() {
  // Configuramos los pines como SALIDA (OUTPUT) para poder enviar voltaje al LED.
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);
}

// --- SECCIÓN 3: Bucle Principal (Loop) ---
// Esta parte se repite infinitamente.
void loop() {
  // 1. Encender ROJO
  // Llamamos a nuestra función 'encenderColor'.
  // HIGH en el primero (Rojo) y LOW en los otros dos apaga Verde y Azul.
  encenderColor(HIGH, LOW, LOW); 
  delay(500); // Mantiene el color durante 500 milisegundos (0.5 segundos)

  // 2. Encender VERDE
  // Enviamos LOW al Rojo, HIGH al Verde, y LOW al Azul.
  encenderColor(LOW, HIGH, LOW); 
  delay(500); // Espera 0.5 segundos

  // 3. Encender AZUL
  // Enviamos LOW al Rojo y Verde, y HIGH al Azul.
  encenderColor(LOW, LOW, HIGH); 
  delay(500); // Espera 0.5 segundos
}

// --- SECCIÓN 4: Función Personalizada ---
// Esta función nos ayuda a escribir menos código en el loop.
// Recibe 3 parámetros (r, g, b) que pueden ser HIGH (encendido) o LOW (apagado).
void encenderColor(int r, int g, int b) {
  digitalWrite(ledRojo, r);  // Aplica el estado recibido 'r' al pin del Rojo
  digitalWrite(ledVerde, g); // Aplica el estado recibido 'g' al pin del Verde
  digitalWrite(ledAzul, b);  // Aplica el estado recibido 'b' al pin del Azul
}