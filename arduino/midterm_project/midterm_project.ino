/***************************************************************************/
// File       [final_project.ino]
// Author     [Erik Kuo]
// Synopsis   [Code for managing main process]
// Functions  [setup, loop, Search_Mode, Hault_Mode, SetState]
// Modify     [2020/03/27 Erik Kuo]
/***************************************************************************/

#define DEBUG  // debug flag

// for RFID
#include "dual_motor.h"
#include "RFID.h"

/*=====Import header files=====*/
#include "bluetooth.h"
#include "node.h"
#include "track.h"
/*=====Import header files=====*/

/*===========================define pin & create module object================================*/
// BlueTooth
// BT connect to Serial1 (Hardware Serial)
// Mega               HC05
// Pin  (Function)    Pin
// 18    TX       ->  RX
// 19    RX       <-  TX
// TB6612, 請按照自己車上的接線寫入腳位(左右不一定要跟註解寫的一樣)
// TODO: 請將腳位寫入下方
#define MotorR_I1 3     // 定義 A1 接腳（右）
#define MotorR_I2 2     // 定義 A2 接腳（右）
#define MotorR_PWMR 11  // 定義 ENA (PWM調速) 接腳
#define MotorL_I3 6     // 定義 B1 接腳（左）
#define MotorL_I4 5     // 定義 B2 接腳（左）
#define MotorL_PWML 12  // 定義 ENB (PWM調速) 接腳
#define Motor_Stby 10
int LeftMotorMax = 200; //
int RightMotorMax = 200;    
dual_motor* Motor;
RFID* Rfid;  // 建立RFID物件

// 循線模組, 請按照自己車上的接線寫入腳位
#define IRpin_LL 32
#define IRpin_L 34
#define IRpin_M 36
#define IRpin_R 38
#define IRpin_RR 40
// RFID, 請按照自己車上的接線寫入腳位
#define RST_PIN 9                 // 讀卡機的重置腳位
#define SS_PIN 53                  // 晶片選擇腳位

#define Buzzer_PIN 7

/*===========================define pin & create module object===========================*/

/*============setup============*/
void setup() {
    // Serial window
    Serial.begin(115200);
    delay(3000);
    // bluetooth initialization
    Serial1.begin(9600);
    // RFID initial
    SPI.begin();
    Rfid = new RFID(SS_PIN, RST_PIN);
    // TB6612 pin
    pinMode(MotorR_I1, OUTPUT);
    pinMode(MotorR_I2, OUTPUT);
    pinMode(MotorL_I3, OUTPUT);
    pinMode(MotorL_I4, OUTPUT);
    pinMode(MotorL_PWML, OUTPUT);
    pinMode(MotorR_PWMR, OUTPUT);
    pinMode(Buzzer_PIN, OUTPUT);
    //TODO: 
    Motor = new dual_motor(MotorL_I3, MotorL_I4, MotorL_PWML, MotorR_I1, MotorR_I2, MotorR_PWMR, Motor_Stby, LeftMotorMax, RightMotorMax);

    // tracking pin
    pinMode(IRpin_LL, INPUT);
    pinMode(IRpin_L, INPUT);
    pinMode(IRpin_M, INPUT);
    pinMode(IRpin_R, INPUT);
    pinMode(IRpin_RR, INPUT);
#ifdef DEBUG
    Serial.println("Start!");
#endif
    /*
    walk(Motor, '1');
    //tone(Buzzer_PIN, 1310, 100);
    rightSpin(Motor);
    walk(Motor, '2');
    //tone(Buzzer_PIN, 655, 100);
    walk(Motor, '3');
    //tone(Buzzer_PIN, 655, 100);
    rightSpin(Motor);
    walk(Motor, '4');
    //tone(Buzzer_PIN, 655, 100);
    Motor->stop();
    */
}
/*============setup============*/

/*===========================initialize variables===========================*/
int l2 = 0, l1 = 0, m0 = 0, r1 = 0, r2 = 0;  // 紅外線模組的讀值(0->white,1->black)                            // set your own value for motor power
int state = 2;     // 0: idle 1: moving 2: reading rfid
String _cmd;  // enum for bluetooth message, reference in bluetooth.h line 2
/*===========================initialize variables===========================*/

/*===========================declare function prototypes===========================*/
void Search();    // search graph
void SetState();  // switch the state
/*===========================declare function prototypes===========================*/

/*===========================define function===========================*/
void loop() {
    if(state == 0) Motor->write(0, 0);
    else if(state == 1) Search();
    else if(state == 2)
    {
        //Serial.println("gimme card");
        Motor->write(0, 0);
        delay(500);
        if(Rfid->detectCard() && Rfid->haveData())
        {
            Serial1.println(Rfid->getUid());
            state = 0;
            //send_msg(RFID->getUID());
        }
    }
    Serial.println(state);
    SetState();
}

void SetState() {
    if(Serial1.available() == 1 && state == 0) state = 1;
}

void Search() {
    // TODO: let your car search graph(maze) according to bluetooth command from computer(python
    // code)
    //Serial.println("asking......");
    _cmd = ask_BT();
    for(int i = 0; i < _cmd.length(); i++)
    switch(_cmd[i])
    {
        case 'f':
            walk(Motor);
            break;
        case 'b':
            halfSpin(Motor);
            walk(Motor);
            break;
        case 'l':
            leftSpin(Motor);
            walk(Motor);
            break;
        case 'r':
            rightSpin(Motor);
            walk(Motor);
            break;
        default:
            Motor->stop();
            break;
    }
    state = 2;
}
/*===========================define function===========================*/
