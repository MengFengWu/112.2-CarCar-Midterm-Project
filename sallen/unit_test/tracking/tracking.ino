#include "IR_sensor.h"
#include "dual_motor.h"

IR_sensor *IR;
dual_motor *Motor;
bool *sensor_read;
double score;
uint32_t time = 5000;

void setup()
{
  Serial.begin(115200);
  Serial.println("Serial Start");
  IR = new IR_sensor(32, 34, 36, 38, 40);
  IR->setWeight(-10.0, -3.0, 0.0, 3.0, 10.0);
  Motor = new dual_motor(6, 5, 12, 3, 2, 11, 13, 250, 220, 20);
  Motor->smooth(0, 0);
}

void loop()
{
  sensor_read = IR->detectRoad();
  if(time >= millis())
  {
    for(int i=0; i<5; i++)
    {
      Serial.print(sensor_read[i]);
    }
    Serial.print(" Score: ");
    score = IR->getScore();
    speedHandle(score);
    Serial.println(score);
  }
  else
    Motor->smooth(0, 0);
}

void speedHandle(double sc)
{
  if(sc < 0)
  {
    Motor->smooth(255.0/(-sc), 255);
  }
  
  if(sc > 0)
  {
    Motor->smooth(255, 255.0/sc);
  }

  if(sc == 0)
  {
    Motor->smooth(255, 255);
  }
}