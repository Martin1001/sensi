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
}

void aquireData(void) {
  messureAirQualityData();
  getData();
}
