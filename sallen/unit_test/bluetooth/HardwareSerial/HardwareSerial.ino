void setup() 
{
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial1.println("BlueTooth Start! ");
  Serial.println("Serial Start! ");
}

void loop() 
{
  if(Serial1.available())
  {
    Serial.println("BT: ");
    Serial.write(Serial1.read());
  }
  if(Serial.available())
  {
    Serial1.write(Serial.read());
  }

}
