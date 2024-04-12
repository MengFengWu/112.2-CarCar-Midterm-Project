int PWMA = 11, PWMB = 12;
int AIN1 = 2, AIN2 = 3, BIN1 = 5, BIN2 = 6;
//int STBY = 5;


void setup() {
  Serial.begin(115200);
  Serial.println("Serial Start!");
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  //pinMode(STBY, OUTPUT);

  //digitalWrite(STBY, HIGH);

  analogWrite(PWMA, 250);
  analogWrite(PWMB, 250);

  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  
  delay(1000);

  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}



void loop() 
{
  Serial.println(millis());

}
