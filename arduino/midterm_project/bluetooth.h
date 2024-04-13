/***************************************************************************/
// File			  [bluetooth.h]
// Author		  [Erik Kuo]
// Synopsis		[Code for bluetooth communication]
// Functions  [ask_BT, send_msg, send_byte]
// Modify		  [2020/03/27 Erik Kuo]
/***************************************************************************/

/*if you have no idea how to start*/
/*check out what you have learned from week 2*/

enum BT_CMD {
    NOTHING,
    // TODO: add your own command type here
    ADVANCE,
    U_TURN,
    TURN_RIGHT,
    TURN_LEFT,
    HALT
};

BT_CMD ask_BT() {
    BT_CMD message = NOTHING;
    char cmd;
    //Serial.print("asking...");
    if (Serial1.available()) {
// TODO:
// 1. get cmd from Serial1(bluetooth serial)
// 2. link bluetooth message to your own command type
      cmd = Serial1.read();
      switch(cmd)
      {
        case 'f':
            message = ADVANCE;
            break;
        case 'b':
            message = U_TURN;
            break;
        case 'r':
            message = TURN_RIGHT;
            break;
        case 'l':
            message = TURN_LEFT;
            break;
        default:
            message = NOTHING;
            break;
      }
//#ifdef DEBUG
        Serial.print("cmd : ");
        Serial.println(cmd);
//#endif
    }
    return message;
}  // ask_BT

// send msg back through Serial1(bluetooth serial)
// can use send_byte alternatively to send msg back
// (but need to convert to byte type)
void send_msg(const char& msg) {
    // TODO:
    Serial1.write(msg);
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
