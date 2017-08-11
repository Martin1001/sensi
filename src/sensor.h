#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

#define CCS811_ADDR 0x5B //Default I2C Address
//#define CCS811_ADDR 0x5A //Alternate I2C Address

struct sensorData_s {
  uint16_t CO2;
  uint16_t VOC;
  uint16_t LUX;
};

typedef enum { SENSOROK, ERROR_AIRQUALITYSENSOR } errorType;

extern struct sensorData_s sensorData;
extern errorType sensor_setup(void);
extern void messureAirQualityData(void);
extern void getData(void);
extern void aquireData(void);
extern uint16_t getLux(void);

#endif
