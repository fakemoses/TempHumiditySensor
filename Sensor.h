#ifndef SENSOR_H
#define SENSOR_H

#include<stdlib.h>
#include<stdio.h>

#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT22

typedef enum
{
    e_red,
    e_yellow,
    e_green
} SensorValueState;

extern DHT dht;
extern float currentTempValue;
extern float currentHumidityValue;


void initSensor();
void getSensorValue();
SensorValueState evaluateSensorValue();

#endif
