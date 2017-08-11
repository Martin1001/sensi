#include <Arduino.h>
#include "Sensor.h"

void setup()
{
  Serial.begin(9600);
  Serial.println();

  if (sensor_setup() != SENSOROK) {
    Serial.println("Error in Sensor Setup");
  } else {
    Serial.println("200");
  }
}

void loop()
{
  aquireData();
  Serial.print(sensorData.CO2);
  Serial.print("  |  ");
  Serial.print(sensorData.VOC);
  Serial.println();
  Serial.println(sensorData.LUX);

  delay(1000);
}
