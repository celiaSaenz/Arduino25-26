//Canal YouTube -> RobotUNO
//Proyecto 1
#include "IRremote.h"
#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5
#define LED5 6
#define LED6 7
#define LED7 8
#define LED8 9
#define LED9 10
#define LED10 12

int receiver = 11;
IRrecv irrecv(receiver);
decode_results results;

void translateIR(){
  switch(results.value){    
  case 0xFFA25D: Serial.println("POWER");
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  digitalWrite(LED8, LOW);
  digitalWrite(LED9, LOW);
  digitalWrite(LED10, LOW);
  break;  
  
  case 0xFFC23D: Serial.println("FAST FORWARD");
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
  digitalWrite(LED6, HIGH);
  digitalWrite(LED7, HIGH);
  digitalWrite(LED8, HIGH);
  digitalWrite(LED9, HIGH);
  digitalWrite(LED10, HIGH);
  break;  
  
  case 0xFF6897: Serial.println("0");
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);
  break;  
  
  case 0xFF30CF: Serial.println("1");
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, HIGH);
  break;  
  
  case 0xFF18E7: Serial.println("2");
  pinMode(LED3, OUTPUT);
  digitalWrite(LED3, HIGH);
  break;  
  
  case 0xFF7A85: Serial.println("3");
  pinMode(LED4, OUTPUT);
  digitalWrite(LED4, HIGH);
  break;  
  
  case 0xFF10EF: Serial.println("4");
  pinMode(LED5, OUTPUT);
  digitalWrite(LED5, HIGH);
  break;  
  
  case 0xFF38C7: Serial.println("5");
  pinMode(LED6, OUTPUT);
  digitalWrite(LED6, HIGH);
  break; 
   
  case 0xFF5AA5: Serial.println("6");
  pinMode(LED7, OUTPUT);
  digitalWrite(LED7, HIGH);
  break;  
  
  case 0xFF42BD: Serial.println("7");
  pinMode(LED8, OUTPUT);
  digitalWrite(LED8, HIGH);
  break;  
  
  case 0xFF4AB5: Serial.println("8");
  pinMode(LED9, OUTPUT);
  digitalWrite(LED9, HIGH);
  break;  
  
  case 0xFF52AD: Serial.println("9");
  pinMode(LED10, OUTPUT);
  digitalWrite(LED10, HIGH);
  break;  
  
  case 0xFFFFFFFF: Serial.println("ERROR");break; 
  
  default: 
    Serial.println("Otro botón");
  }
  delay(500);
}


void setup() {
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn();
}


void loop(){
  if (irrecv.decode(&results)) 
  {
    translateIR(); 
    irrecv.resume();
  }  
}