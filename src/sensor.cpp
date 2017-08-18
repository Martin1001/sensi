#include <Arduino.h>
#include "sensor.h"

// SparkFun Air Quality Sensor (CCS811) Libary
#include "SparkFunCCS811.h"

// Adafruit Temperature & Humidity (SHT31) Library
#include "Adafruit_SHT31.h"

CCS811 airQualitySensor(CCS811_ADDR);
Adafruit_SHT31 sht31 = Adafruit_SHT31();

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
  // CCS811Core::status returnCode = airQualitySensor.begin();
  // if (returnCode != CCS811Core::SENSOR_SUCCESS)
  // {
  //   return ERROR_AIRQUALITYSENSOR;
  // }

  // Temperature & Humidity Sensor (SHT31)
  if (! sht31.begin(SHT31_ADDR)) {
    return ERROR_TEMPERATURSENSOR;
  }

  // Sound Detector ()
  pinMode(NOISEPIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(NOISEPIN), sensor_interupt_handler, RISING);

  // Motion Detector ()
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
}

void getData(void) {
  sensorData.CO2 = airQualitySensor.getCO2();
  sensorData.VOC = airQualitySensor.getTVOC();
  sensorData.TEMP = sht31.readTemperature();
  sensorData.HUMID = sht31.readHumidity();
  sensorData.LUX = getLux();
  sensorData.MOTION = digitalRead(MOTIONPIN);
  sensorData.NOISE = soundcounter;
  soundcounter = 0;
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
