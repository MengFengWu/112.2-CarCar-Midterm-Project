#include "arduino.h"
#include "HardwareSerial.h"

class CustomSerial: public HardwareSerial
{
  public: 
    CustomSerial(HardwareSerial &serail);
}; 