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
        dual_motor(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t lmax = 255, uint8_t rmax = 255);
        void write(int, int) const; //set the relative power of the lef and right motor
        void stop() const;
        void spin(int dir = LEFT, int speed = 255) const;

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