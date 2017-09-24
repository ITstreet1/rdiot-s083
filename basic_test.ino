/* ML8511 UV Sensor (GYML8511) [S083] : http://rdiot.tistory.com/72 [RDIoT Demo] */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Hardware pin definitions
int UVOUT = A0; //Output from the sensor
int REF_3V3 = A1; //3.3V power on the Arduino board

LiquidCrystal_I2C lcd(0x27,20,4);  // LCD2004

void setup()
{
  lcd.init();  // initialize the lcd 
  lcd.backlight();
  lcd.print("start LCD2004");
  
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);

  delay(1000);

  lcd.clear();
}

void loop()
{
  lcd.setCursor(0,0);
  lcd.print("S083:GYML8511 UV");

 int uvLevel = averageAnalogRead(UVOUT);
 int refLevel = averageAnalogRead(REF_3V3);
 //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
 float outputVoltage = 3.3 / refLevel * uvLevel;  
 float uvIntensity = mapfloat(outputVoltage, 0.99, 2.9, 0.0, 15.0);


 lcd.setCursor(0,1);
 lcd.print("uvLevel=" + (String)uvLevel + " ");

 lcd.setCursor(0,2);
 lcd.print("voltage=" + (String)outputVoltage + " ");

 lcd.setCursor(0,3);
 lcd.print("uv=" + (String)uvIntensity + "(mW/cm^2)");
  
 delay(100);

}
//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
  return(runningValue);  
}
//The Arduino Map function but for floats
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
