/***************************************************************************/
// File			  [node.h]
// Author		  [Erik Kuo, Joshua Lin]
// Synopsis		[Code for managing car movement when encounter a node]
// Functions  [/* add on your own! */]
// Modify		  [2020/03/027 Erik Kuo]
/***************************************************************************/

/*===========================import variable===========================*/
int extern vLd;
int extern vRd;
void extern MotorWriting(double vL, double vR);
void extern tracking(int l2, int l1, int m0, int r1, int r2);
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

void walk()
{
  int nowDetect = detect();
  while(nowDetect <= 2) 
  {
    tracking(digitalRead(32), digitalRead(34), digitalRead(36), digitalRead(38), digitalRead(40));
    nowDetect = detect();
  }
  while(nowDetect > 2)
  {
    tracking(digitalRead(32), digitalRead(34), digitalRead(36), digitalRead(38), digitalRead(40));
    nowDetect = detect();
  }
}

void rightSpin()
{
  MotorWriting(vLd, -vRd);
  delay(14000/40); 
  MotorWriting(0, 0);
  delay(200);
}

void leftSpin()
{
  MotorWriting(-vLd, vRd);
  delay(14000/40); 
  MotorWriting(0, 0);
  delay(200);
}

void halfSpin()
{
  MotorWriting(vLd, -vRd);
  delay(14000/20); 
  MotorWriting(0, 0);
  delay(200);
}

int stop()
{
  MotorWriting(0, 0);
}