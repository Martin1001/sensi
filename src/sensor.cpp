#include <Arduino.h>
#include "sensor.h"

// CO2 Sensor Libary
#include "SparkFunCCS811.h"

// DHT Sensor
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

CCS811 airQualitySensor(CCS811_ADDR);
DHT_Unified dht(DHTPIN, DHTTYPE);

struct sensorData_s sensorData;

// Interne Funktionen
extern uint16_t getLux(void);
extern void triggerMessurement(void);
extern void getData(void);

// Setup
errorType sensor_setup(void) {
  // Air Quality Sensor
  CCS811Core::status returnCode = airQualitySensor.begin();
  if (returnCode != CCS811Core::SENSOR_SUCCESS)
  {
    return ERROR_AIRQUALITYSENSOR;
  }

  // DHT Sensor
  dht.begin();

  pinMode(NOISEPIN, INPUT);
  pinMode(MOTIONPIN, INPUT);
  
  return SENSOROK;
}

void aquireData(void) {
  triggerMessurement();
  getData();
}

void triggerMessurement(void) {
  //Check to see if data is ready with .dataAvailable()
  if (airQualitySensor.dataAvailable()) {
    airQualitySensor.readAlgorithmResults();
  }

  //Trigger DHT
  dht.temperature().getEvent(&sensorData.TEMP);
  dht.humidity().getEvent(&sensorData.HUMID);
}

void getData(void) {
  sensorData.CO2 = airQualitySensor.getCO2();
  sensorData.VOC = airQualitySensor.getTVOC();
  sensorData.LUX = getLux();
  // DHT nicht notwendig, wird vom Trigger gesetzt
  sensorData.MOTION = digitalRead(MOTIONPIN);
  sensorData.NOISE = digitalRead(NOISEPIN);
}

uint16_t getLux(void) {
  uint64_t val = 0;

  for (uint8_t i = 0; i < LUXAVERAGE ; i++) {
      val += analogRead(LUXPIN);
  }

  return floor(val / LUXAVERAGE);
}
