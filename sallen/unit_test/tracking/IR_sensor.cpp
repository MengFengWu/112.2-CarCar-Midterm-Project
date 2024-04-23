#include "HardwareSerial.h"
#include "IR_sensor.h"
#include "Arduino.h"

IR_sensor::IR_sensor(uint8_t llpin, uint8_t lpin, uint8_t midpin, uint8_t rpin, uint8_t rrpin): PIN(new uint8_t[5]{llpin, lpin, midpin, rpin, rrpin})
{
    for(int i=0; i<5; i++)
    {
        pinMode(PIN[i], INPUT);
        Weight[i] = 0;
        Read[i] = 0;
    }
}

IR_sensor::IR_sensor(uint8_t *pinlist): PIN(new uint8_t(pinlist))
{
    for(int i=0; i<5; i++)
    {
        pinMode(PIN[i], INPUT);
        Weight[i] = 0;
        Read[i] = 0;
    }
}

void IR_sensor::setWeight(double wll, double wl, double wm, double wr, double wrr)
{
  Weight[0] = wll;
  Weight[1] = wl;
  Weight[2] = wm;
  Weight[3] = wr;
  Weight[4] = wrr;
}

void IR_sensor::setWeight(double *weight_list)
{
  for(int i=0; i<5; i++)
  {
    Weight[i] = weight_list[i];
  }
}

const bool* IR_sensor::detectRoad()
{
  detect();
  return Read;
}

double IR_sensor::getScore()
{
  detect();
  double sum = 0, num = 0;
  for(int i=0; i<5; i++)
  {
    sum += (double)Weight[i]*(double)Read[i];
    num += Read[i];
  }
  /*Serial.print("sum, num: ");
  Serial.print(sum);
  Serial.print(", ");
  Serial.println(num);
  delay(1000);*/

  if(num == 0)
    return 0;
  return sum/num;
}

void IR_sensor::detect()
{
  for(int i=0; i<5; i++)
  {
    Read[i] = digitalRead(PIN[i]);
  }
}