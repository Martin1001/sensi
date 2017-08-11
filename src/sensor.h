#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <configure.h>

struct sensorData_s {
  uint16_t CO2;
  uint16_t VOC;
  uint16_t LUX;
  sensors_event_t TEMP;
  sensors_event_t HUMID;
  boolean MOTION;
  boolean NOISE;
};

typedef enum { SENSOROK, ERROR_AIRQUALITYSENSOR } errorType;

extern struct sensorData_s sensorData;
extern errorType sensor_setup(void);
extern void aquireData(void);

#endif
