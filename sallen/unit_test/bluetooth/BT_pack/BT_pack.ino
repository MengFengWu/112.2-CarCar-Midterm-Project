#include "CustomSerial.h"

CustomSerial *BT_serial;

void setup() {
  BT_serial = new CustomSerial(Serial);
  BT_serial->begin(115200);
  BT_serial->print("1"); 
  BT_serial->print("2"); 
  BT_serial->print("3"); 
  BT_serial->print("4"); 
  //Serial.begin(115200);
  //Serial.println("Serial Start");
}

void loop() {
}
