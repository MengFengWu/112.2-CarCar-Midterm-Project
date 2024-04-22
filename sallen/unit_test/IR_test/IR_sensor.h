#ifndef IR_SENSOR_H
#define IR_SENSOR_H
#include "Arduino.h"
class IR_sensor
{
    public:
        IR_sensor(uint8_t llpin, uint8_t lpin, uint8_t midpin, uint8_t rpin, uint8_t rrpin); //Constructor with each sensors pin from left to right
        IR_sensor(uint8_t *pinlist); //Constructor with an array of pin from left to right
        void setWeight(float wll, float wl, float wm, float wr, float wrr); //Set the weight of each sensor from left to right
        void setWeight(float *weight_list); //Set the weight of each sensor from left to right
        const bool* detectRoad(); //Detect the IR sensors and return the the values of each from left to right
        float getScore(); //Detect the IR sensors and compute the score from the weighted value

    private: 
        const uint8_t *PIN;
        int Weight[5];
        bool Read[5];
        void detect();

};


#endif