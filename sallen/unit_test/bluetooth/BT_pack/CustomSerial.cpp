#include "HardwareSerial.h"
#include "CustomSerial.h"
#include "arduino.h"

CustomSerial::CustomSerial(HardwareSerial& serial): HardwareSerial(serial)
{
}
