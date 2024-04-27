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
#include "node_new.h"
#include "track.h"
#include "buzzer.h"
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
//int LeftMotorMax = 122; //
//int RightMotorMax = 122;    
int LeftMotorMax = 250;
int RightMotorMax = 220;  
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
    Serial1.setTimeout(10);
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
}
/*============setup============*/

/*===========================initialize variables===========================*/
int l2 = 0, l1 = 0, m0 = 0, r1 = 0, r2 = 0;  // 紅外線模組的讀值(0->white,1->black)                            // set your own value for motor power
int state = 1, last_state = 1;     // 0: idle 1: moving 2: reading rfid
String _cmd;  // enum for bluetooth message, reference in bluetooth.h line 2
/*===========================initialize variables===========================*/

/*===========================declare function prototypes===========================*/
void Search();    // search graph
void SetState();  // switch the state
int NowTime = millis();
/*===========================declare function prototypes===========================*/

/*===========================define function===========================*/
void loop() {
    btDoRoutine();
    if(state == 0) Motor->write(0, 0);
    else if(state == 1) Search();
    else if(state == 2)
    {
        //Serial.println("gimme card");
        Motor->write(-35, -35);
        NowTime = millis();
        while(!Rfid->detectCard())
        {
            if(millis() - NowTime >= 2000) 
            {
              noTone(7);
              break;
            }
            else {
              tone(7, 32);
            }
        }
        Serial1.println(Rfid->getUid());
        Serial1.print("Uid: ")
        Serial.println(Rfid->getUid());
        Motor->stop();
        state = 0;
        //send_msg(RFID->getUID());
    }
    if(last_state != state)
    {
        Serial.print("State change to: ");
        Serial.println(state);
        last_state = state;
    }
    SetState();
}

void test_loop()
{
    walk(Motor);
    rightSpin(Motor);
    walk(Motor);
    halfSpin(Motor);
    walk(Motor);
    forward(Motor);
    walk(Motor);
    halfSpin(Motor);
    walk(Motor);
    leftSpin(Motor);
    walk(Motor);
    halfSpin(Motor);
    walk(Motor);
    forward(Motor);
    walk(Motor);
    halfSpin(Motor);
}

void SetState() {
    if(cmdAvailable() && state == 0) state = 1;
}

void Search() {
    // TODO: let your car search graph(maze) according to bluetooth command from computer(python
    // code)
    //Serial.println("asking......");
    _cmd = ask_BT();
    if(_cmd.length() == 0)
        return ;
    Serial.print("Search by command: ");
    Serial.println(_cmd);
    for(int i=0; i < _cmd.length(); i++)
    {
        switch(_cmd[i])
        {
            case 'f':
                Serial.print("f ");
                Serial.println(millis());
                forward(Motor);
                break;
            case 'b':
                Serial.print("b ");
                Serial.println(millis());
                halfSpin(Motor);
                break;
            case 'l':
                Serial.print("l ");
                Serial.println(millis());
                leftSpin(Motor);
                break;
            case 'r':
                Serial.print("r ");
                Serial.println(millis());
                rightSpin(Motor);
                break;

            case 'g':
                //music!
                playMusic();
                break;
            default:
                Motor->stop();
                break;
        }
        walk(Motor);
    }
    Motor->stop();
    state = 2;
}

/*===========================define function===========================*/
