#ifndef dual_motor_h
#define dual_motor_h

#include "Arduino.h"
enum myEnum
{
  LEFT,
  RIGHT,
  FORWARD,
  BACKWARD,
};

class dual_motor
{
    public:
        //Constructor: given the pin channel: (left, right)(in1, in2, pwm) + standby, and the tuned front left right max signal 
        dual_motor(uint8_t lin1, uint8_t lin2, uint8_t lpwm, uint8_t rin1, uint8_t rin2, uint8_t rpwm, uint8_t stby, uint8_t lmax = 255, uint8_t rmax = 255);

        void write(int left_power, int right_power) const; //set the relative power of the left and right motor
        void stop() const; 
        void spin(int dir = LEFT, int speed = 255) const; //let the car spin LEFT or RIGHT, and set the relative power of each motor

    private: 
        uint8_t LIn1;
        uint8_t LIn2;
        uint8_t LPWM;
        uint8_t RIn1;
        uint8_t RIn2;
        uint8_t RPWM;
        uint8_t STBY;
        uint8_t LMax;
        uint8_t RMax;
        void setDir(int, int) const;
};

#endif