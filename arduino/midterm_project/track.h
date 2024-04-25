/***************************************************************************/
// File			  [track.h]
// Author		  [Erik Kuo]
// Synopsis		[Code used for tracking]
// Functions  [MotorWriting, MotorInverter, tracking]
// Modify		  [2020/03/27 Erik Kuo]
/***************************************************************************/

/*if you have no idea how to start*/
/*check out what you have learned from week 1 & 6*/
/*feel free to add your own function for convenience*/
#include "dual_motor.h"

/*===========================import variable===========================*/

/*===========================import variable===========================*/

#define MotorR_I1 2     // 定義 A1 接腳（右）
#define MotorR_I2 3     // 定義 A2 接腳（右）
#define MotorR_PWMR 11  // 定義 ENA (PWM調速) 接腳
#define MotorL_I3 5     // 定義 B1 接腳（左）
#define MotorL_I4 6     // 定義 B2 接腳（左）
#define MotorL_PWML 12  // 定義 ENB (PWM調速) 接腳

// Write the voltage to motor.
/*
void MotorWriting(double vL, double vR) {
    // TODO: use TB6612 to control motor voltage & direction
    if(vL >= 0)
    {
      digitalWrite(MotorL_I3, LOW);
      digitalWrite(MotorL_I4, HIGH);
      analogWrite(MotorL_PWML, vL);
    }
    if(vL < 0)
    {
      digitalWrite(MotorL_I3, HIGH);
      digitalWrite(MotorL_I4, LOW);
      analogWrite(MotorL_PWML, -vL);
    }
    if(vR >= 0)
    {
      digitalWrite(MotorR_I1, LOW);
      digitalWrite(MotorR_I2, HIGH);
      analogWrite(MotorR_PWMR, vR);
    }
    if(vR < 0)
    {
      digitalWrite(MotorR_I1, HIGH);
      digitalWrite(MotorR_I2, LOW);
      analogWrite(MotorR_PWMR, -vR);
    }
}  // MotorWriting
*/

// Handle negative motor_PWMR value.
void MotorInverter(int motor, bool& dir) {
    // Hint: the value of motor_PWMR must between 0~255, cannot write negative value.
    return;
}  // MotorInverter

// P/PID control Tracking
void tracking(int l2, int l1, int m0, int r1, int r2, dual_motor* Motor) {
    // TODO: find your own parameters!
    double _w0 = 0.0;  //
    double _w1 = 1.5;  //
    double _w2 = 4.0;  //
    double _Kp;  // p term parameter
    double _Kd;  // d term parameter (optional)
    double _Ki;  // i term parameter (optional) (Hint: 不要調太大)
    double error = l2 * _w2 + l1 * _w1 + m0 * _w0 + r1 * (-_w1) + r2 * (-_w2);
    //double vR = vRd;
    //double vL = vLd;  // 馬達左右轉速原始值(從PID control 計算出來)。Between -255 to 255.
    double adj_R = 1, adj_L = 1;  // 馬達轉速修正係數。MotorWriting(_Tp,_Tp)如果歪掉就要用參數修正。

    // TODO: complete your P/PID tracking code
    if(l2 + l1 + m0 + r1 + r2 != 0) error /= l2 + l1 + m0 + r1 + r2;
    if(error < 0)
    {
      adj_R = 1 / ((-1) * error);
    }
    else if(error > 0)
    {
      adj_L = 1 / error;
    }

    // end TODO
    Motor->write(adj_L * 255, adj_R * 255);
}  // tracking
