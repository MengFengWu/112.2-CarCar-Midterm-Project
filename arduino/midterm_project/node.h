/***************************************************************************/
// File			  [node.h]
// Author		  [Erik Kuo, Joshua Lin]
// Synopsis		[Code for managing car movement when encounter a node]
// Functions  [/* add on your own! */]
// Modify		  [2020/03/027 Erik Kuo]
/***************************************************************************/

#include "dual_motor.h"

/*===========================import variable===========================*/
int spinSpeed = 50;
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

void walk(dual_motor* Motor, char Text = 'D')
{
  int nowDetect = detect();
  while(nowDetect <= 2) 
  {
    tracking(digitalRead(32), digitalRead(34), digitalRead(36), digitalRead(38), digitalRead(40), Motor);
    nowDetect = detect();
    //Serial.print("line ");
  }
  //Serial.println();
  while(nowDetect > 2)
  {
    tracking(digitalRead(32), digitalRead(34), digitalRead(36), digitalRead(38), digitalRead(40), Motor);
    nowDetect = detect();
    //Serial.print("node ");
  }
  //Serial.println();
}

void rightSpin(dual_motor* Motor)
{
  Motor->stop();
  delay(50);
  Motor->spin(RIGHT, 255);
  delay(14000/spinSpeed); 
  Motor->stop();
  delay(200);
}

void leftSpin(dual_motor* Motor)
{
  Motor->stop();
  delay(50);
  Motor->spin(LEFT, 255);
  delay(14000/spinSpeed); 
  Motor->stop();
  delay(200);
}

void halfSpin(dual_motor* Motor)
{
  Motor->stop();
  delay(50);
  Motor->spin(RIGHT, 255);
  delay(14000/(spinSpeed/2)); 
  Motor->stop();
  delay(200);
}

int stop(dual_motor* Motor)
{
  Motor->stop();
}