#include "dual_motor.h"

dual_motor *motor;

int left = 0, right = 0, time = 0;
uint32_t last = millis();
char cmd;

void setup() {
  motor = new dual_motor(6, 5, 12, 3, 2, 11, 13, 250, 220, 100);
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.println("Serial Start");

}

void loop() {
  if(Serial.available())
  {
    Serial.println("read");
    Serial.readStringUntil('-');
    cmd = Serial.read();
    switch (cmd) 
    {
      case 'l': 
        left = Serial.parseInt();
        Serial.print("Set left: ");
        Serial.println(left);
        break; 
      case 'r': 
        right = Serial.parseInt();
        Serial.print("Set right: ");
        Serial.println(right);
        break;
      case 't':
        time = Serial.parseInt();
        Serial.print("Set time: ");
        Serial.println(time);
        break;
      default:
        Serial.print("Error command: " + cmd);
        Serial.readStringUntil('-');
        break;
    }
  }

  if(millis()-last < time)
  {
    motor->smooth(left, right);
    delay(time);
    motor->stop();
    time = 0;
  }
  last = millis();
}
