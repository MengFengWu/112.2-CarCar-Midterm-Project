#include "IR_sensor.h"

IR_sensor *IR;
bool *sensor_read;

void setup()
{
  Serial.begin(115200);
  Serial.println("Serial Start");
  IR = new IR_sensor(32, 34, 36, 38, 40);
  IR->setWeight(-2.0, -1.5, 0, 1.5, 2.0);
}

void loop()
{
  sensor_read = IR->detectRoad();
  Serial.print("[");
  for(int i=0; i<5; i++)
  {
    Serial.print(sensor_read[i]);
    Serial.print("; ");
  }
  Serial.print("], Score: ");
  Serial.println(IR->getScore());
  delay(1000);
}