#include <SoftwareSerial.h>


SoftwareSerial BT(18, 19);

void setup() 
{
  BT.begin(9600);
  Serial.begin(9600);
  BT.println("BlueTooth Start! ");
  Serial.println("Serial Start! ");
}

void loop() 
{
  if(BT.available())
  {
    Serial.write(BT.read());
  }
  if(Serial.available())
  {
    BT.write(Serial.read());
  }

}
