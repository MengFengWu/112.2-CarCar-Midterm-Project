#include "dual_motor.h"
#include "Arduino.h"


dual_motor::dual_motor(uint8_t lin1, uint8_t lin2, uint8_t lpwm, uint8_t rin1, uint8_t rin2, uint8_t rpwm, uint8_t stby, uint8_t lmax, uint8_t rmax, int smthdevide, int smthdelay): LIn1(lin1), LIn2(lin2), LPWM(lpwm), RIn1(rin1), RIn2(rin2), RPWM(rpwm), STBY(stby), LMax(lmax), RMax(rmax), SMOOTH_DELAY(smthdelay)
{
  pinMode(LIn1, OUTPUT);
  pinMode(LIn2, OUTPUT);
  pinMode(RIn1, OUTPUT);
  pinMode(RIn2, OUTPUT);
  pinMode(STBY, OUTPUT);

  analogWrite(LPWM, 0);
  analogWrite(RPWM, 0);
  leftspeed = 0;
  rightspeed = 0;

  setDir(LEFT, FORWARD);
  setDir(RIGHT, FORWARD);
  
  digitalWrite(STBY, 1);
}

void dual_motor::write(int lspeed, int rspeed) const
{
  if(lspeed == 0 && rspeed == 0)
  {
    stop();
  }

  if(lspeed >= 0)
  {
    setDir(LEFT, FORWARD);
    analogWrite(LPWM, lspeed*(double)LMax/255.0);
  }
  else
  {
    setDir(LEFT, BACKWARD);
    analogWrite(LPWM, -lspeed*(double)LMax/255.0);
  }
  
  if(rspeed >= 0)
  {
    setDir(RIGHT, FORWARD);
    analogWrite(RPWM, rspeed*(double)RMax/255.0);
  }
  else
  {
    setDir(RIGHT, BACKWARD);
    analogWrite(RPWM, -rspeed*(double)RMax/255.0);
  }
}

void dual_motor::stop() const
{
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
  setDir(LEFT, FORWARD);
  setDir(RIGHT, FORWARD);
}

void dual_motor::spin(int side, int speed) const
{
  if(side == RIGHT)
  {
    setDir(LEFT, FORWARD);
    setDir(RIGHT, BACKWARD);
  }
  if(side == LEFT)
  {
    setDir(LEFT, BACKWARD);
    setDir(RIGHT, FORWARD);
  }

  analogWrite(LPWM, speed*LMax/255.0);
  analogWrite(RPWM, speed*RMax/255.0);
}

void dual_motor::setMax(uint8_t lmax, uint8_t rmax)
{
  LMax = lmax;
  RMax = rmax;
}

void dual_motor::smooth(int left, int right)
{
  double left_delta = (left - leftspeed)/smthdevide;
  double right_delta = (right - rightspeed)/smthdevide;
  for(; abs(leftspeed-left) > 2 && abs(rightspeed-right) > 2; leftspeed+=left_delta, rightspeed+=right_delta)
  {
    write(leftspeed, rightspeed);
    delayMicroseconds(smthdelay);
  }
}

void dual_motor::setSmoothDelay(int microseconds)
{
  SMOOTH_DELAY = microseconds;
}

void dual_motor::setDir(int side, int dir) const
{
  if(side == LEFT)
  {
    if(dir == FORWARD)
    {
      digitalWrite(LIn1, HIGH);
      digitalWrite(LIn2, LOW);
    }
    if(dir == BACKWARD)
    {
      digitalWrite(LIn1, LOW);
      digitalWrite(LIn2, HIGH);
    }
  }
  if(side == RIGHT)
  {
    if(dir == FORWARD)
    {
      digitalWrite(RIn1, HIGH);
      digitalWrite(RIn2, LOW);
    }
    if(dir == BACKWARD)
    {
      digitalWrite(RIn1, LOW);
      digitalWrite(RIn2, HIGH);
    }
  }
}