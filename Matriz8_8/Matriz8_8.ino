#include "LedControl.h"

/*
 Creamos un objeto LedControl.
 Conexiones usadas:
 Pin 12 -> DIN
 Pin 11 -> CLK
 Pin 10 -> CS/LOAD

 Solo usamos una matriz MAX72XX.
*/
LedControl lc=LedControl(12,11,10,1);

/* Tiempo de espera entre animaciones */
unsigned long delaytime=100;

void setup() {

  /*
   El MAX72XX inicia en modo ahorro de energía,
   así que debemos activarlo.
  */
  lc.shutdown(0,false);

  /* Ajustar brillo (0 a 15) */
  lc.setIntensity(0,8);

  /* Limpiar la pantalla */
  lc.clearDisplay(0);
}

/*
 Esta función muestra las letras
 de la palabra "Arduino" una por una.
*/
void writeArduinoOnMatrix() {

  /* Datos binarios de cada letra */
  byte a[5]={B01111110,B10001000,B10001000,B10001000,B01111110};
  byte r[5]={B00111110,B00010000,B00100000,B00100000,B00010000};
  byte d[5]={B00011100,B00100010,B00100010,B00010010,B11111110};
  byte u[5]={B00111100,B00000010,B00000010,B00000100,B00111110};
  byte i[5]={B00000000,B00100010,B10111110,B00000010,B00000000};
  byte n[5]={B00111110,B00010000,B00100000,B00100000,B00011110};
  byte o[5]={B00011100,B00100010,B00100010,B00100010,B00011100};

  /* Mostrar letra A */
  lc.setRow(0,0,a[0]);
  lc.setRow(0,1,a[1]);
  lc.setRow(0,2,a[2]);
  lc.setRow(0,3,a[3]);
  lc.setRow(0,4,a[4]);
  delay(delaytime);

  /* Mostrar letra R */
  lc.setRow(0,0,r[0]);
  lc.setRow(0,1,r[1]);
  lc.setRow(0,2,r[2]);
  lc.setRow(0,3,r[3]);
  lc.setRow(0,4,r[4]);
  delay(delaytime);

  /* Mostrar letra D */
  lc.setRow(0,0,d[0]);
  lc.setRow(0,1,d[1]);
  lc.setRow(0,2,d[2]);
  lc.setRow(0,3,d[3]);
  lc.setRow(0,4,d[4]);
  delay(delaytime);

  /* Mostrar letra U */
  lc.setRow(0,0,u[0]);
  lc.setRow(0,1,u[1]);
  lc.setRow(0,2,u[2]);
  lc.setRow(0,3,u[3]);
  lc.setRow(0,4,u[4]);
  delay(delaytime);

  /* Mostrar letra I */
  lc.setRow(0,0,i[0]);
  lc.setRow(0,1,i[1]);
  lc.setRow(0,2,i[2]);
  lc.setRow(0,3,i[3]);
  lc.setRow(0,4,i[4]);
  delay(delaytime);

  /* Mostrar letra N */
  lc.setRow(0,0,n[0]);
  lc.setRow(0,1,n[1]);
  lc.setRow(0,2,n[2]);
  lc.setRow(0,3,n[3]);
  lc.setRow(0,4,n[4]);
  delay(delaytime);

  /* Mostrar letra O */
  lc.setRow(0,0,o[0]);
  lc.setRow(0,1,o[1]);
  lc.setRow(0,2,o[2]);
  lc.setRow(0,3,o[3]);
  lc.setRow(0,4,o[4]);
  delay(delaytime);

  /* Apagar la matriz */
  lc.setRow(0,0,0);
  lc.setRow(0,1,0);
  lc.setRow(0,2,0);
  lc.setRow(0,3,0);
  lc.setRow(0,4,0);

  delay(delaytime);
}

/*
 Esta función enciende LEDs por filas.
 Cada fila parpadea según su número.
*/
void rows() {

  for(int row=0; row<8; row++) {

    delay(delaytime);

    lc.setRow(0,row,B10100000);

    delay(delaytime);

    lc.setRow(0,row,(byte)0);

    for(int i=0; i<row; i++) {

      delay(delaytime);

      lc.setRow(0,row,B10100000);

      delay(delaytime);

      lc.setRow(0,row,(byte)0);
    }
  }
}

/*
 Esta función enciende LEDs por columnas.
 Cada columna parpadea según su número.
*/
void columns() {

  for(int col=0; col<8; col++) {

    delay(delaytime);

    lc.setColumn(0,col,B10100000);

    delay(delaytime);

    lc.setColumn(0,col,(byte)0);

    for(int i=0; i<col; i++) {

      delay(delaytime);

      lc.setColumn(0,col,B10100000);

      delay(delaytime);

      lc.setColumn(0,col,(byte)0);
    }
  }
}

/*
 Esta función enciende cada LED
 uno por uno en toda la matriz.
*/
void single() {

  for(int row=0; row<8; row++) {

    for(int col=0; col<8; col++) {

      delay(delaytime);


      
      lc.setLed(0,row,col,true);

      delay(delaytime);

      for(int i=0; i<col; i++) {

        lc.setLed(0,row,col,false);

        delay(delaytime);

        lc.setLed(0,row,col,true);

        delay(delaytime);
      }
    }
  }
}

/* Bucle principal */
void loop() {

  writeArduinoOnMatrix();

  rows();

  columns();

  single();
}