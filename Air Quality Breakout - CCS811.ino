/*Mandatory wiring:
 *    Common for 3.3V and 5V Arduino boards:
 *        sensor I2C SDA  <------> Arduino I2C SDA
 *        sensor I2C SCL  <------> Arduino I2C SCL
 *        sensor GND      <------> Arduino GND
 *        sensor PAD6     <------> Arduino D5 or Arduino GND [connecting to GND the CCS811 sensor will be always ON]
 *    For Arduino 3.3V compatible:
 *        sensor Vin      <------> Arduino 3.3V
 *    For Arduino 5V compatible:
 *        sensor Vin      <------> Arduino 5V
  SPECIAL note for some ARDUINO boards:
 *        SDA (Serial Data)   ->  A4 on Uno/Pro-Mini, 20 on Mega2560/Due, 2 Leonardo/Pro-Micro
 *        SCK (Serial Clock)  ->  A5 on Uno/Pro-Mini, 21 on Mega2560/Due, 3 Leonardo/Pro-Micro
 * 
 */

#define SERIAL_SPEED  19200

#include <sSense-CCS811.h>

CCS811 ssenseCCS811;


void setup()
{
  DebugPort.begin(SERIAL_SPEED);
  delay(5000);
  DebugPort.println("s-Sense CCS811 I2C sensor.");
  if(!ssenseCCS811.begin(uint8_t(I2C_CCS811_ADDRESS), uint8_t(CCS811_WAKE_PIN), driveMode_1sec))
    DebugPort.println("Initialization failed.");
}

void loop()
{ 
  ssenseCCS811.setEnvironmentalData((float)(21.102), (float)(57.73));  // replace with temperature and humidity values from HDC2010 sensor
  /*if (ssenseCCS811.dataAvailable()){
  {
    ssenseCCS811.readAlgorithmResults(); //Calling this function updates the global tVOC and CO2 variables

    .....DebugPort.print("CO2[");
    DebugPort.print(ssenseCCS811.getCO2());
    DebugPort.print("] tVOC[");
    DebugPort.print(ssenseCCS811.gettVOC());
    DebugPort.print("] millis[");
    DebugPort.print(millis());
    DebugPort.print("]");
    DebugPort.println();
  }
  */
  if (ssenseCCS811.checkDataAndUpdate())
  {
    DebugPort.print("CO2[");
    DebugPort.print(ssenseCCS811.getCO2());
    DebugPort.print("] tVOC[");
    DebugPort.print(ssenseCCS811.gettVOC());
    DebugPort.print("] millis[");
    DebugPort.print(millis());
    DebugPort.print("]");
    DebugPort.println();
  }
  else if (ssenseCCS811.checkForError())
  {
    ssenseCCS811.printError();
  }

  delay(2000);
}