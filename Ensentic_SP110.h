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

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"

#define ENSENTIC_SP110_SENSOR_I2C_ADDRESS               0x38 // read

#define ENSENTIC_SP110_WHO_AM_I_REG_ADDRESS             0x04 // read
#define ENSENTIC_SP110_READ_MOISTURE_REG_ADDRESS        0x01 // read
#define ENSENTIC_SP110_READ_TEMPERATURE_REG_ADDRESS     0x02 // read

#define ENSENTIC_SP110_DATA_READY_REG_ADDRESS           0x05 // read
#define ENSENTIC_SP110_READ_CURRENT_CALIBRATION_SCHEMA  0x06 // read

// Two Point Calibration With Data
#define ENSENTIC_SP110_START_TWO_POINT_CALIBRATION   0x08 // write
#define ENSENTIC_SP110_LOW_POINT_DRY_SOIL_VALUE      0x09 // write
#define ENSENTIC_SP110_HIGH_POINT_WET_SOIL_VALUE     0x10 // write
#define ENSENTIC_SP110_SAVE_CALIBRATION_WITH_DATA    0x11 // write 

#define ENSENTIC_SP110_LOW_POINT_DRY_SOIL_VALUE_TAKE      0x17 // write
#define ENSENTIC_SP110_HIGH_POINT_WET_SOIL_VALUE_TAKE     0x18 // write

// Two Point Calibration without data
#define ENSENTIC_SP110_START_W_TWO_POINT_CALIBRATION   0x12 // write
#define ENSENTIC_SP110_LOW_POINT_W_DRY_SOIL_VALUE      0x13 // write
#define ENSENTIC_SP110_HIGH_POINT_W_WET_SOIL_VALUE     0x14 // write
#define ENSENTIC_SP110_SAVE_CALIBRATION_WITHOUT_DATA   0x15 // write 

#define ENSENTIC_SP110_RESET_TO_FACTORY_DEFAULT      0x16 // write , this will clear all the calibration value and sensor will use the default calibration came from factory

typedef enum
{
  ENSENTIC_SP110_CALIBRATION_NOT_DONE =0,
  ENSENTIC_SP110_CALIBRATION_FACTORY =1,
  ENSENTIC_SP110_CALIBRATION_WITHOUT_KNOWN_DATA =2,
  ENSENTIC_SP110_CALIBRATION_WITH_KNOWN_DATA = 3,
}CALIBRATION_SCHEMA_e;

class Ensentic_SP110 {
 public:
  Ensentic_SP110();
  boolean begin(void);
  float readTemperature();
  float readMoisturePercentage();
  byte startCalWithoutData();
  byte calDryPointCovered();
  byte calWetPointCovered();
  byte saveCalibrationWithoutKnownData();
  byte startCalWithData();
  byte calDryPointCoveredW(int moisture);
  byte calWetPointCoveredW(int moisture);
  byte saveCalibrationWithKnownData();
    
 private:
 void sendDataByte(int regName,int regValue );
  boolean readAddress();
  byte readDataByte(int regName);
  void readTwoDataByte(int regName,byte *data);
};
