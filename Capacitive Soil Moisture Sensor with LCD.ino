#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
const int AirValue = 600;   //you need to replace this value with Value_1
const int WaterValue = 350;  //you need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent=0;
void setup() {
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
  lcd.begin(16, 2);
}
void loop() {
soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
Serial.println(soilMoistureValue);
soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
if(soilmoisturepercent > 100)
{
  Serial.println("100 %");
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture");
  lcd.setCursor(0, 1);
  lcd.print("100 %");
  delay(250);
  lcd.clear();
}
else if(soilmoisturepercent <0)
{
  Serial.println("0 %");
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture");
  lcd.setCursor(0, 1);
  lcd.print("0 %");
  delay(250);
  lcd.clear();
}
else if(soilmoisturepercent >0 && soilmoisturepercent < 100)
{
  Serial.print(soilmoisturepercent);
  Serial.println("%");
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture");
  lcd.setCursor(0, 1);
  lcd.print(soilmoisturepercent);
  lcd.print(" %");
  delay(250);
  lcd.clear();
}  
}