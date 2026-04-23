#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println("Acerca una tarjeta para escribir datos...");
}

void loop() {
  // Espera a que haya una tarjeta nueva
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  Serial.println("Tarjeta detectada");

  byte block = 4; // bloque recomendado para empezar

  // 16 bytes exactos
  byte dataBlock[16] = {
    'H','O','L','A',' ','A','R','D','U','I','N','O',' ',' ',' ',' '
  };

  MFRC522::StatusCode status;

  // Autenticación del bloque
  status = mfrc522.PCD_Authenticate(
    MFRC522::PICC_CMD_MF_AUTH_KEY_A,
    block,
    &key,
    &(mfrc522.uid)
  );

  if (status != MFRC522::STATUS_OK) {
    Serial.print("Error de autenticacion: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // Escritura del bloque
  status = mfrc522.MIFARE_Write(block, dataBlock, 16);

  if (status != MFRC522::STATUS_OK) {
    Serial.print("Error al escribir: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
  } else {
    Serial.println("Datos escritos correctamente en el bloque 4");
  }

  // Finalizar comunicación
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  delay(2000);
}