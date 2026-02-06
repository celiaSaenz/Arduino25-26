/*************************************************
 * SIMON SAYS - SparkFun Inventor's Kit (Adaptado)
 * Código COMPLETO con comentarios en ESPAÑOL
 *
 * Juego de memoria con LEDs, botones y buzzer
 *************************************************/

/*************************************************
 * Definición de notas musicales (frecuencia en Hz)
 *************************************************/
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

/*************************************************
 * Constantes de control del juego
 *************************************************/
#define CHOICE_OFF      0
#define CHOICE_NONE     0
#define CHOICE_RED      (1 << 0)
#define CHOICE_GREEN    (1 << 1)
#define CHOICE_BLUE     (1 << 2)
#define CHOICE_YELLOW   (1 << 3)

/*************************************************
 * Definición de pines de LEDs
 *************************************************/
#define LED_RED     12
#define LED_YELLOW  10
#define LED_BLUE    8
#define LED_GREEN   6

/*************************************************
 * Definición de pines de botones
 *************************************************/
#define BUTTON_RED     13
#define BUTTON_YELLOW  11
#define BUTTON_BLUE    9
#define BUTTON_GREEN   7

/*************************************************
 * Definición de pines del buzzer
 *************************************************/
#define BUZZER1  5
#define BUZZER2  4

/*************************************************
 * Parámetros del juego
 *************************************************/
#define ROUNDS_TO_WIN      13    // Rondas necesarias para ganar
#define ENTRY_TIME_LIMIT   3000  // Tiempo máximo para pulsar un botón (ms)

#define MODE_MEMORY  0
#define MODE_BATTLE  1
#define MODE_BEEGEES 2

/*************************************************
 * Variables globales del estado del juego
 *************************************************/
byte gameMode = MODE_MEMORY; // Modo de juego actual
byte gameBoard[32];          // Secuencia del juego
byte gameRound = 0;          // Ronda actual

/*************************************************
 * CONFIGURACIÓN INICIAL
 *************************************************/
void setup()
{
  // Configurar botones como entradas con pull-up interno
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);

  // Configurar LEDs como salidas
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  // Configurar buzzer
  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);

  // Selección de modo especial al encender
  if (checkButton() == CHOICE_YELLOW) play_beegees();

  if (checkButton() == CHOICE_GREEN)
  {
    gameMode = MODE_BATTLE;
    setLEDs(CHOICE_GREEN);
    toner(CHOICE_GREEN, 150);
    setLEDs(CHOICE_RED | CHOICE_BLUE | CHOICE_YELLOW);
    while(checkButton() != CHOICE_NONE);
  }

  play_winner(); // Sonido de inicio
}

/*************************************************
 * BUCLE PRINCIPAL
 *************************************************/
void loop()
{
  attractMode(); // Animación de espera

  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW);
  delay(1000);
  setLEDs(CHOICE_OFF);
  delay(250);

  if (gameMode == MODE_MEMORY)
  {
    if (play_memory()) play_winner();
    else play_loser();
  }

  if (gameMode == MODE_BATTLE)
  {
    play_battle();
    play_loser();
  }
}

/*************************************************
 * MODO MEMORIA (SIMON CLÁSICO)
 *************************************************/
boolean play_memory(void)
{
  randomSeed(millis());
  gameRound = 0;

  while (gameRound < ROUNDS_TO_WIN)
  {
    add_to_moves();
    playMoves();

    for (byte currentMove = 0; currentMove < gameRound; currentMove++)
    {
      byte choice = wait_for_button();
      if (choice == 0) return false;
      if (choice != gameBoard[currentMove]) return false;
    }
    delay(1000);
  }
  return true;
}

/*************************************************
 * MODO BATALLA (2 JUGADORES)
 *************************************************/
boolean play_battle(void)
{
  gameRound = 0;
  while (1)
  {
    byte newButton = wait_for_button();
    gameBoard[gameRound++] = newButton;

    for (byte currentMove = 0; currentMove < gameRound; currentMove++)
    {
      byte choice = wait_for_button();
      if (choice == 0) return false;
      if (choice != gameBoard[currentMove]) return false;
    }
    delay(100);
  }
}

/*************************************************
 * Reproduce la secuencia actual de LEDs
 *************************************************/
void playMoves(void)
{
  for (byte i = 0; i < gameRound; i++)
  {
    toner(gameBoard[i], 150);
    delay(150);
  }
}

/*************************************************
 * Añade un nuevo botón aleatorio a la secuencia
 *************************************************/
void add_to_moves(void)
{
  byte r = random(0, 4);
  if (r == 0) r = CHOICE_RED;
  else if (r == 1) r = CHOICE_GREEN;
  else if (r == 2) r = CHOICE_BLUE;
  else r = CHOICE_YELLOW;

  gameBoard[gameRound++] = r;
}

/*************************************************
 * Control de LEDs
 *************************************************/
void setLEDs(byte leds)
{
  digitalWrite(LED_RED,    (leds & CHOICE_RED));
  digitalWrite(LED_GREEN,  (leds & CHOICE_GREEN));
  digitalWrite(LED_BLUE,   (leds & CHOICE_BLUE));
  digitalWrite(LED_YELLOW, (leds & CHOICE_YELLOW));
}

/*************************************************
 * Espera a que el usuario pulse un botón
 *************************************************/
byte wait_for_button(void)
{
  long startTime = millis();
  while ((millis() - startTime) < ENTRY_TIME_LIMIT)
  {
    byte button = checkButton();
    if (button != CHOICE_NONE)
    {
      toner(button, 150);
      while (checkButton() != CHOICE_NONE);
      delay(10);
      return button;
    }
  }
  return CHOICE_NONE;
}

/*************************************************
 * Lee qué botón está pulsado
 *************************************************/
byte checkButton(void)
{
  if (!digitalRead(BUTTON_RED)) return CHOICE_RED;
  if (!digitalRead(BUTTON_GREEN)) return CHOICE_GREEN;
  if (!digitalRead(BUTTON_BLUE)) return CHOICE_BLUE;
  if (!digitalRead(BUTTON_YELLOW)) return CHOICE_YELLOW;
  return CHOICE_NONE;
}

/*************************************************
 * Enciende LED y genera tono
 *************************************************/
void toner(byte which, int duration)
{
  setLEDs(which);
  switch(which)
  {
    case CHOICE_RED:    buzz_sound(duration, 1136); break;
    case CHOICE_GREEN:  buzz_sound(duration, 568);  break;
    case CHOICE_BLUE:   buzz_sound(duration, 851);  break;
    case CHOICE_YELLOW: buzz_sound(duration, 638);  break;
  }
  setLEDs(CHOICE_OFF);
}

/*************************************************
 * Genera sonido en el buzzer
 *************************************************/
void buzz_sound(int ms, int delay_us)
{
  long total = ms * 1000L;
  while (total > delay_us * 2)
  {
    total -= delay_us * 2;
    digitalWrite(BUZZER1, LOW);
    digitalWrite(BUZZER2, HIGH);
    delayMicroseconds(delay_us);
    digitalWrite(BUZZER1, HIGH);
    digitalWrite(BUZZER2, LOW);
    delayMicroseconds(delay_us);
  }
}

/*************************************************
 * Sonido y luces de victoria
 *************************************************/
void play_winner(void)
{
  for (byte i = 0; i < 4; i++)
  {
    setLEDs(CHOICE_GREEN | CHOICE_BLUE);
    winner_sound();
    setLEDs(CHOICE_RED | CHOICE_YELLOW);
    winner_sound();
  }
}

void winner_sound(void)
{
  for (byte x = 250; x > 70; x--)
    for (byte y = 0; y < 3; y++)
    {
      digitalWrite(BUZZER2, HIGH);
      digitalWrite(BUZZER1, LOW);
      delayMicroseconds(x);
      digitalWrite(BUZZER2, LOW);
      digitalWrite(BUZZER1, HIGH);
      delayMicroseconds(x);
    }
}

/*************************************************
 * Sonido y luces de derrota
 *************************************************/
void play_loser(void)
{
  for (byte i = 0; i < 4; i++)
  {
    setLEDs(CHOICE_RED | CHOICE_GREEN);
    buzz_sound(255, 1500);
    setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
    buzz_sound(255, 1500);
  }
}

/*************************************************
 * Animación mientras espera al jugador
 *************************************************/
void attractMode(void)
{
  while (1)
  {
    setLEDs(CHOICE_RED); delay(100); if (checkButton()) return;
    setLEDs(CHOICE_BLUE); delay(100); if (checkButton()) return;
    setLEDs(CHOICE_GREEN); delay(100); if (checkButton()) return;
    setLEDs(CHOICE_YELLOW); delay(100); if (checkButton()) return;
  }
}

/*************************************************
 * MODO BEE GEES (HUEVO DE PASCUA)
 *************************************************/
int melody[] = {
  NOTE_G4, NOTE_A4, 0, NOTE_C5, 0, 0, NOTE_G4, 0,
  0, 0, NOTE_E4, 0, NOTE_D4, NOTE_E4, NOTE_G4, 0,
  NOTE_D4, NOTE_E4, 0, NOTE_G4, 0, 0,
  NOTE_D4, 0, NOTE_E4, 0, NOTE_G4, 0, NOTE_A4, 0, NOTE_C5, 0
};

int noteDuration = 115;
int LEDnumber = 0;

void play_beegees()
{
  setLEDs(CHOICE_YELLOW);
  toner(CHOICE_YELLOW, 150);
  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE);
  while(checkButton() != CHOICE_NONE);
  setLEDs(CHOICE_NONE);
  delay(1000);
  digitalWrite(BUZZER1, LOW);

  while(checkButton() == CHOICE_NONE)
  {
    for (int i = 0; i < 32; i++)
    {
      changeLED();
      tone(BUZZER2, melody[i], noteDuration);
      delay(noteDuration * 1.3);
      noTone(BUZZER2);
    }
  }
}

void changeLED(void)
{
  setLEDs(1 << LEDnumber);
  LEDnumber = (LEDnumber + 1) % 4;
}
