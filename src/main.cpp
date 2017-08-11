#include <Arduino.h>
#include "Sensor.h"

void setup()
{
  Serial.begin(115200);
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
  Serial.println();
  Serial.println(sensorData.TEMP.temperature);
  Serial.println(sensorData.HUMID.relative_humidity);
  Serial.println();
  Serial.println(sensorData.NOISE);
  Serial.println();
  Serial.println(sensorData.MOTION);

  delay(1000);
}
