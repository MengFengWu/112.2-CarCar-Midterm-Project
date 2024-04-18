void setup() 
{
  Serial1.begin(9600);
  Serial.begin(115200);
  Serial1.println("BlueTooth Start! ");
  Serial.println("Serial Start! ");
}

void loop() 
{
  if(Serial1.available())
  {
    Serial.println(Serial1.readString());
  }
  if(Serial.available())
  {
    Serial1.println(Serial.readString());
  }

}
