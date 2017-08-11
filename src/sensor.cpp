#include <Arduino.h>
#include "Sensor.h"
#include "SparkFunCCS811.h"

CCS811 airQualitySensor(CCS811_ADDR);

struct sensorData_s sensorData;

errorType sensor_setup(void) {
  // Air Quality Sensor
  CCS811Core::status returnCode = airQualitySensor.begin();
  if (returnCode != CCS811Core::SENSOR_SUCCESS)
  {
    return ERROR_AIRQUALITYSENSOR;
  }
  //pinMode(A8, ANALOG);
  return SENSOROK;
}

void messureAirQualityData(void) {
  //Check to see if data is ready with .dataAvailable()
  if (airQualitySensor.dataAvailable()) {
    airQualitySensor.readAlgorithmResults();
  }
}

void getData(void) {
  sensorData.CO2 = airQualitySensor.getCO2();
  sensorData.VOC = airQualitySensor.getTVOC();
  sensorData.LUX = getLux();
}

void aquireData(void) {
  messureAirQualityData();
  getData();
}

uint16_t getLux(void) {
  uint64_t val = 0;

  for (uint8_t i = 0; i < 100 ; i++) {
      val += analogRead(A8);
  }

  return floor(val / 100);

}
