#include <Arduino.h>
#include "sensor.h"
#include "led.h"

void setup()
{
  Serial.begin(115200);
  Serial.println();

  if (sensor_setup() != SENSOROK) {
    Serial.println("Error in Sensor Setup");
  } else {
    Serial.println("200");
  }

  led_setup();
}

void loop()
{
  aquireData();
  Serial.print("CO2: ");
  Serial.print(sensorData.CO2);
  Serial.print(" ppm | TVOC: ");
  Serial.print(sensorData.VOC);
  Serial.print(" ppm | LUX: ");
  Serial.print(sensorData.LUX);
  Serial.print(" | Temperature: ");
  Serial.print(sensorData.TEMP.temperature);
  Serial.print(" ° C | Humidity: ");
  Serial.print(sensorData.HUMID.relative_humidity);
  Serial.print(" % | ");
  Serial.print(sensorData.NOISE);
  Serial.print(" | Motion: ");
  Serial.print(sensorData.MOTION);
  Serial.println("");
  delay(1000);
}
