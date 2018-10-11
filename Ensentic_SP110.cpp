/*************************************************** 
  This is a library for the SP110 Soil Moisutre and Temperature Sensor
  Designed specifically to work with the SP110 sensor from Ensentic
  
  These displays use I2C to communicate, 2 pins are required to  
  interface
  
  Ensentic invests time and resources providing this open source code, 
  please support Ensentic and open-source hardware by purchasing 
  products from Ensentic.com!

  
  Written by Bhautik Ramoliya for Ensentic Sensors.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

 #include "Ensentic_SP110.h"

 #if defined(__AVR__)
  #include <util/delay.h>
#endif

Ensentic_SP110::Ensentic_SP110() {
}

boolean Ensentic_SP110::begin(void) {
  Wire.begin();
  
   // try to read data, as a test
  return readAddress();
}

void Ensentic_SP110::sendDataByte(int regName,int regValue )
{
  Wire.beginTransmission(ENSENTIC_SP110_SENSOR_I2C_ADDRESS); // transmit to device #8
  Wire.write((byte)regName);              // sends one byte
  Wire.write((byte)regValue); 
  Wire.endTransmission();    // stop transmitting
}



byte Ensentic_SP110::readDataByte(int regName)
{
  Wire.beginTransmission(ENSENTIC_SP110_SENSOR_I2C_ADDRESS); // select device with "beginTransmission()"
  Wire.write(regName); // select starting register with "write()"
  Wire.endTransmission(); // end write operation, as we just wanted to select the starting register
  Wire.requestFrom(ENSENTIC_SP110_SENSOR_I2C_ADDRESS, 1); // select number of bytes to get from the device (1 bytes in this case)
  return Wire.read();
}

void Ensentic_SP110::readTwoDataByte(int regName,byte *data)
{
  Wire.beginTransmission(ENSENTIC_SP110_SENSOR_I2C_ADDRESS); // select device with "beginTransmission()"
  Wire.write(regName); // select starting register with "write()"
  Wire.endTransmission(); // end write operation, as we just wanted to select the starting register
  Wire.requestFrom(ENSENTIC_SP110_SENSOR_I2C_ADDRESS, 2); // select number of bytes to get from the device (2 bytes in this case)
  data[0] =  Wire.read();
  data[1] = Wire.read();
}

boolean Ensentic_SP110::readAddress(void) {

  int a = readDataByte(ENSENTIC_SP110_WHO_AM_I_REG_ADDRESS);
  if(a == ENSENTIC_SP110_SENSOR_I2C_ADDRESS)
  {
    delay(1500); // necessary wait to take sensor correct data for first time
    return true;
  }
  else
  {
    return false;
  }
}

float Ensentic_SP110::readTemperature(void) {

   byte soilTemp[2];
   float temp = 0;
   
  readTwoDataByte(ENSENTIC_SP110_READ_TEMPERATURE_REG_ADDRESS,soilTemp);

  temp = (((soilTemp[0]*100 + soilTemp[1]))/100.00);
  
  return temp;
}


float Ensentic_SP110::readMoisturePercentage(void) {

   byte moistureByte[2];
   float moisture = 0;
   
  readTwoDataByte(ENSENTIC_SP110_READ_MOISTURE_REG_ADDRESS,moistureByte);


  moisture = (((moistureByte[0]*100 + moistureByte[1]))/100.00);
  
  return moisture;
}

byte Ensentic_SP110::startCalWithoutData(void){
  byte readByte;

  return readDataByte(ENSENTIC_SP110_START_W_TWO_POINT_CALIBRATION);
}

byte Ensentic_SP110::calDryPointCovered(void){
  byte readByte;

  return readDataByte(ENSENTIC_SP110_LOW_POINT_W_DRY_SOIL_VALUE);
}
byte Ensentic_SP110::calWetPointCovered(void){
  byte readByte;

  return readDataByte(ENSENTIC_SP110_HIGH_POINT_W_WET_SOIL_VALUE);
}
byte Ensentic_SP110::saveCalibrationWithoutKnownData(void){
  byte readByte;

  return readDataByte(ENSENTIC_SP110_SAVE_CALIBRATION_WITHOUT_DATA);
}

byte Ensentic_SP110::startCalWithData(void){
  byte readByte;

  return readDataByte(ENSENTIC_SP110_START_TWO_POINT_CALIBRATION);
}

byte Ensentic_SP110::calDryPointCoveredW(int moisture){
  byte readByte;

  sendDataByte(ENSENTIC_SP110_LOW_POINT_DRY_SOIL_VALUE_TAKE,moisture);
  return readDataByte(ENSENTIC_SP110_LOW_POINT_DRY_SOIL_VALUE);
}

byte Ensentic_SP110::calWetPointCoveredW(int moisture){
  byte readByte;
  sendDataByte(ENSENTIC_SP110_HIGH_POINT_WET_SOIL_VALUE_TAKE,moisture);
  return readDataByte(ENSENTIC_SP110_HIGH_POINT_WET_SOIL_VALUE);
}

byte Ensentic_SP110::saveCalibrationWithKnownData(void){
  byte readByte;

  return readDataByte(ENSENTIC_SP110_SAVE_CALIBRATION_WITH_DATA);
}
