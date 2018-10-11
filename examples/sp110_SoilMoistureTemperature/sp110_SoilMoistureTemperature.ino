#include "Ensentic_SP110.h"

Ensentic_SP110 sp110;

void setup() {

  Serial.begin(115200);  // start serial for output
  
  while (! sp110.begin()) {
     Serial.println("Sensor not found, check wiring & pullups!");
     delay(500);
  }
}

void loop() {

  Serial.print("Temperature is :- ");
  float a = sp110.readTemperature();
  Serial.print(a);
  Serial.println(" c");


  Serial.print("Moisure is :- ");
  float b = sp110.readMoisturePercentage();
  Serial.print(b);
  Serial.println(" %");
  
  delay(500);
}



