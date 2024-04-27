#include "HardwareSerial.h"
/***************************************************************************/
// File			  [node.h]
// Author		  [Erik Kuo, Joshua Lin]
// Synopsis		[Code for managing car movement when encounter a node]
// Functions  [/* add on your own! */]
// Modify		  [2020/03/027 Erik Kuo]
/***************************************************************************/

#include "dual_motor.h"

/*===========================import variable===========================*/
int extern LeftMotorMax;
int extern RightMotorMax;
double spinSpeed = (LeftMotorMax + RightMotorMax) / 2.0; 
double spinTime(double spinSpeed)
{
    return 100000.0 / spinSpeed;
}
double modi[3] = {1.1, 1.1, 1.44};
void extern tracking(int l2, int l1, int m0, int r1, int r2, dual_motor* Motor);
void extern send_msg(const char& msg);
/*===========================import variable===========================*/

// TODO: add some function to control your car when encounter a node
// here are something you can try: left_turn, right_turn... etc.
int detect()
{
  int count = 0;
  for(int i = 0; i < 5; i++)
  {
    count += digitalRead(32 + 2 * i);
  }
  return count;
}

int detectCenter()
{
  int count = 0;
  for(int i = 0; i < 3; i++)
  {
    count += digitalRead(34 + 2 * i);
  }
  return count;
}

void walk(dual_motor* Motor, int type = 0)
{
  int nowDetect = detect();
  int doubleCheck = 0;
  while(nowDetect <= 2) 
  {
    nowDetect = detect();
    if(nowDetect > 2) break;
    tracking(digitalRead(32), digitalRead(34), digitalRead(36), digitalRead(38), digitalRead(40), Motor);
    Serial.print("line ");
    delay(50);
  }
  //Motor->write(150, 150);
  //delay(100);
}

void forward(dual_motor* Motor)
{
  int nowDetect = detect();
  Motor->write(255, 255);
  delay(100);
  while(nowDetect > 2)
  {
    Motor->write(255, 255);
    nowDetect = detect();
    Serial.print("node ");
    delay(50);
  }
}

void rightSpin(dual_motor* Motor)
{
  Motor->write(255, 60);
  //Motor->write(255, 75);
  delay(modi[0] * spinTime(spinSpeed));
  int nowDetect = detectCenter();
  if(nowDetect == 0)
  {
    //tone(7, 1310, 100);
    Motor->spin(RIGHT, 120);
    while(nowDetect == 0)
    {
      nowDetect = detectCenter();
      delay(10);
      continue;
    }
    Serial.println("right spin leave");
    //tone(7, 16,1000);
  }   
  //noTone(7);
}

void leftSpin(dual_motor* Motor)
{
  Motor->write(75, 255);
  delay(modi[1] * spinTime(spinSpeed));
  int nowDetect = detectCenter();
  if(nowDetect == 0)
  {
    //tone(7, 1310, 100);
    Motor->spin(LEFT, 120);
    while(nowDetect == 0)
    {
      nowDetect = detectCenter();
      delay(10);
      continue;
    }
    Serial.println("left spin leave");
  } 
  //noTone(7);
}

void halfSpin(dual_motor* Motor)
{
  Motor->stop();
  delay(50);
  Motor->spin(RIGHT, 200);
  delay(modi[2] * spinTime(spinSpeed));
  int nowDetect = detectCenter();
  if(nowDetect == 0)
  {
    //tone(7, 1310, 100);
    Motor->spin(RIGHT, 120);
    while(nowDetect == 0)
    {
      nowDetect = detectCenter();
      delay(10);
      continue;
    }
  }  
  //noTone(7);
}

int stop(dual_motor* Motor)
{
  Motor->stop();
}