#include "Sensor.h"

DHT dht(DHTPIN, DHTTYPE);
float currentTempValue;
float currentHumidityValue;

void initSensor(){
    dht.begin();   
}

void getSensorValue(){

    currentTempValue = dht.readTemperature();
    currentHumidityValue = dht.readHumidity();
}

SensorValueState evaluateSensorValue(){

    if((currentTempValue > 35.0f || currentTempValue < 25.0f) || currentHumidityValue > 90.0f)
        return e_red;
    else if(currentHumidityValue < 40.0f)
        return e_yellow; // probably never happens
    else
        return e_green;
}
