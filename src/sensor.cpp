#include <Arduino.h>
#include "sensor.h"

// Air Quality Sensor (CCS811) Libary
#include "SparkFunCCS811.h"

// DHT Sensor Library
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

CCS811 airQualitySensor(CCS811_ADDR);
DHT_Unified dht(DHTPIN, DHTTYPE);

struct sensorData_s sensorData;
volatile uint16_t soundcounter = 0;

// Internal Function
extern uint16_t getLux(void);
extern void triggerMessurement(void);
extern void getData(void);
extern void sensor_interupt_handler(void);

// Sensor Setup
errorType sensor_setup(void) {
  // Air Quality Sensor (CCS811)
  CCS811Core::status returnCode = airQualitySensor.begin();
  if (returnCode != CCS811Core::SENSOR_SUCCESS)
  {
    return ERROR_AIRQUALITYSENSOR;
  }

  // DHT Sensor
  dht.begin();

  pinMode(NOISEPIN, INPUT);
  pinMode(MOTIONPIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(NOISEPIN), sensor_interupt_handler, RISING);

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
  sensorData.MOTION = digitalRead(MOTIONPIN);
  sensorData.NOISE = soundcounter;
  soundcounter = 0;

  // not necessary for DHT, is set via trigger
}

uint16_t getLux(void) {
  uint64_t val = 0;

  for (uint8_t i = 0; i < LUXAVERAGE ; i++) {
      val += analogRead(LUXPIN);
  }

  return floor(val / LUXAVERAGE);
}

void sensor_interupt_handler(void) {
  soundcounter++;
}
