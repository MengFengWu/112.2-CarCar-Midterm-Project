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
        char dir = Serial1.read();
        String str = Serial1.readString();
        Serial.println(dir);
        Serial.println(str);

        int tinsec = str.toInt();
        if(0 < tinsec < 30)
        {
            if(dir == 'f')
            {
                Motor->write(200, 200);
            }
            if(dir == 'b')
            {
                Motor->write(-200, -200);
            }
            if(dir == 'r')
            {
                Motor->spin(RIGHT, 100);
            }
            if(dir == 'l')
            {
                Motor->spin(LEFT, 100);
            }
            delay(tinsec);
            Motor->stop();
        }
    }
}