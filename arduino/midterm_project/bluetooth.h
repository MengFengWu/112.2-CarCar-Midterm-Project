#include "HardwareSerial.h"
/***************************************************************************/
// File			  [bluetooth.h]
// Author		  [Erik Kuo]
// Synopsis		[Code for bluetooth communication]
// Functions  [ask_BT, send_msg, send_byte]
// Modify		  [2020/03/27 Erik Kuo]
/***************************************************************************/

/*if you have no idea how to start*/
/*check out what you have learned from week 2*/

bool invalidCom(char c)
{
  if(c == 'f' || c == 'b' || c == 'l' || c == 'r' || c == 'g') 
    return false;
  
  return true;
}

enum BT_CMD {
    NOTHING,
    // TODO: add your own command type here
    ADVANCE,
    U_TURN,
    TURN_RIGHT,
    TURN_LEFT,
    HALT
};

String cmds = "";

void btDoRoutine()
{
  if(Serial1.available())
  {
    String get = Serial1.readString();
    Serial.print("BT receive: ");
    Serial.println(get);
    for(int i=0; i<get.length(); i++)
    {
      if(!invalidCom(get[i]))
      {
        cmds += get[i];
      }
    }
  }
}

String ask_BT() {
    //BT_CMD message = NOTHING;
    String ret = cmds;
    cmds = "";
    return ret;
    String cmd;
    //Serial.print("asking...");
// TODO:
// 1. get cmd from Serial1(bluetooth serial)
// 2. link bluetooth message to your own command type
      /*
#ifdef DEBUG
        Serial.print("cmd : ");
        Serial.println(cmd);
#endif
*/
}  // ask_BT

bool cmdAvailable()
{
    return cmds.length()>0;
}

// send msg back through Serial1(bluetooth serial)
// can use send_byte alternatively to send msg back
// (but need to convert to byte type)
void send_msg(const char& msg) {
    // TODO:
    Serial1.println(msg);
}  // send_msg

// send UID back through Serial1(bluetooth serial)
void send_byte(byte* id, byte& idSize) {
    for (byte i = 0; i < idSize; i++) {  // Send UID consequently.
        Serial1.write(id[i]);
    }
#ifdef DEBUG
    Serial.print("Sent id: ");
    for (byte i = 0; i < idSize; i++) {  // Show UID consequently.
        Serial.print(id[i], HEX);
    }
    Serial.println();
#endif
}  // send_byte
