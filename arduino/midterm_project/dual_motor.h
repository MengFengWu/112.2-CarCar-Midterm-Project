#ifndef DUAL_MOTOR_H
#define DUAL_MOTOR_H

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
        //signal pins *7 and set default left, right maximum, and the times, delay length(in microseconds) in smooth()
        dual_motor(uint8_t lin1, uint8_t lin2, uint8_t lpwm, uint8_t rin1, uint8_t rin2, uint8_t rpwm, uint8_t stby, uint8_t lmax = 255, uint8_t rmax = 255, int smthdevide = 100, int smthdelay = 10);
        void write(int, int) const; //set the relative power of the left and right motor
        void stop() const;
        void spin(int dir = LEFT, int speed = 255) const;
        void setMax(uint8_t lmax, uint8_t rmax);
        //void smooth(int, int);
        void setSmoothDelay(int microseconds);


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
        int leftspeed;
        int rightspeed;
        //int SMOOTH_DELAY;
        void setDir(int, int) const;
};

#endif