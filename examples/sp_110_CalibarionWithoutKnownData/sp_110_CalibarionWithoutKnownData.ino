/*
 * In this method we will use the two soil one is completely dry and another full wet.
 * (Complete DRY soil means moisture in that should be less than 10% and full wet soil means
 * moisture in that should be more than 90%
 * 
 * This both soil will be reference for the sensor to determines the range of moisture for that perticuler sensor.
 * 
 * This method is only required to choose if you don't know the percetange of the moisture present in the dry/wet soil.
 * If you knows the actual percentage of the dry/wet soil (by measuring from an external device or any other technique) then
 * use another example code (sp_110_CalibarionWithKnownData.ino)
 */


#include "Ensentic_SP110.h"

Ensentic_SP110 sp110;

void setup() {
  int a = 0 ;
  char c = 0;
  Serial.begin(115200);  // start serial for output
  
  while (! sp110.begin()) {
     Serial.println("Sensor not found, check wiring & pullups!");
     delay(500);
  }

  Serial.println("Sending Request to Sensor to start the Calibaration without knowing the actual moisture of the dry and wet soil");

  delay(500);
  
  if(sp110.startCalWithoutData() == 1)
  {
    Serial.println("Sensor is ready to start calibration..! Please put your sensor in DRY soil.");
    Serial.println("Press or Enter Y/N once you have installed sensor properly in DRY Soil");

    while(Serial.available() == 0){}
    c = Serial.read();

    if(c == 'Y')
    {
      Serial.println("Please give me some time to test this dry soil , probabaly around 30 seconds");
      delay(32000);

      if(sp110.calDryPointCovered() == 1)
      {
        Serial.println("Hey there i am done with the DRY soil, Please remove me , clean me carefully and enter in WET soil");
        Serial.println("Press & Enter Y/N once you have installed sensor properly in WET Soil");
        while(Serial.available() == 0){}
        c = Serial.read();
        if(c == 'Y')
        {
          Serial.println("Please give me some time to test this WET soil , probabaly around 30 seconds");
          delay(32000);
          if(sp110.calWetPointCovered() == 1)
          {
            sp110.saveCalibrationWithoutKnownData();
            Serial.println("Greetings,  i am done with the WET soil also, thanks for your time");
            Serial.println("All the settings are saved and i am ready to test any SOIL..!");
          }
          else
          {
            Serial.println("OOps..Something went wrong while testing WET soil");
          }
        }
        else
        {
          Serial.println("Calibration process is terminated now. Bye Bye...");
        }
      }
      else
      {
        Serial.println("OOps..Something went wrong while testing DRY soil");
      }
    }
    else
    {
      Serial.println("Calibration process is terminated now. Bye Bye...");
    }
  }
  else
  {
    Serial.println("Sensor is not ready to start calibration..! Try it another time by checking it's wiring.");
  }
}

void loop() {

  Serial.print("Soil Temp[erature is :-   ");
  float a = sp110.readTemperature();
  Serial.print(a);
  Serial.println(" c");


  Serial.print("Soil Moisure is :- ");
  float b = sp110.readMoisturePercentage();
  Serial.print(b);
  Serial.println(" %");
  
  delay(500);
}


