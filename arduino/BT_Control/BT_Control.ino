#include "dual_motor.h"

dual_motor* Motor;

void setup()
{
    Motor = new dual_motor(6, 5, 12, 3, 2, 11, 13);
    
    Serial1.begin(9600);
    Serial.begin(115200);
    Serial1.println("BlueTooth Start! ");
    Serial.println("Serial Start! ");
}

void loop()
{
    if(Serial1.available())
    {
        String str = Serial1.readString();
        int tinsec = str.toInt();
        if(0 < tinsec < 30)
        {
          Serial.print("run: ");
          Serial.println(tinsec);
          Motor->write(150, 150);
          delay(tinsec *1000);
          Motor->stop();
        }
    }
}