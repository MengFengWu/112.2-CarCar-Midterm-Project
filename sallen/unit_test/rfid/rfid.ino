#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SPI_PIN 53

MFRC522 *Mfrc;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Serial Start! ");

  SPI.begin();

  Mfrc = new MFRC522(SPI_PIN, RST_PIN);
  Mfrc->PCD_Init();
  Serial.println(("Read UID on a MIFARE PICC: "));
}

void loop() 
{
  if(!Mfrc->PICC_IsNewCardPresent ())
  {
    goto FuncEnd;
  }
  if(!Mfrc-> PICC_ReadCardSerial())
  {
    goto FuncEnd;
  }
  Serial.println ( ("**Card Detected: ") );

  Mfrc->PICC_DumpDetailsToSerial (&(Mfrc->uid));
  Mfrc->PICC_HaltA(); 
  Mfrc->PCD_StopCrypto1(); 
  FuncEnd:;
  
}