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

void IR_sensor::setWeight(float wll, float wl, float wm, float wr, float wrr)
{
  Weight[0] = wll;
  Weight[1] = wl;
  Weight[2] = wm;
  Weight[3] = wr;
  Weight[4] = wrr;
}

void IR_sensor::setWeight(float *weight_list)
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

float IR_sensor::getScore()
{
  detect();
  float sum = 0;
  for(int i=0; i<5; i++)
  {
    sum += Weight[i]*Read[i];
  }
  return sum;
}

void IR_sensor::detect()
{
  for(int i=0; i<5; i++)
  {
    Read[i] = digitalRead(PIN[i]);
  }
}