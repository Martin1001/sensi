#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

#include <configure.h>

struct sensorData_s {
  uint16_t CO2;
  uint16_t VOC;
  float TEMP;
  float HUMID;
  uint16_t LUX;
  boolean MOTION;
  uint16_t NOISE;
};

typedef enum { SENSOROK, ERROR_AIRQUALITYSENSOR, ERROR_TEMPERATURSENSOR } errorType;

extern struct sensorData_s sensorData;
extern errorType sensor_setup(void);
extern void aquireData(void);

#endif
