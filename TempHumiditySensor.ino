#include "Sensor.h"
#include "Server.h"

#define UNIT_TEST false

#if UNIT_TEST

// Unit test test cases
// AUnit does not allow unit tests cases to be written outside the main file. No test case will be detected outside this file.

#include <AUnit.h>
using namespace aunit;

test(evaluateSensorOutput1)
{
  currentHumidityValue = 50.0f;
  currentTempValue = 40.0f;

  SensorValueState state = evaluateSensorValue();

  assertEqual(state, e_red);
}µ

test(evaluateSensorOutput2)
{
  currentHumidityValue = 25.0f;
  currentTempValue = 30.0f;

  SensorValueState state = evaluateSensorValue();

  assertEqual(state, e_yellow);
}

test(evaluateSensorOutput3)
{
  currentHumidityValue = 45.0f;
  currentTempValue = 30.0f;

  SensorValueState state = evaluateSensorValue();

  assertEqual(state, e_green);
}

#endif


void setup()
{
#if !defined(EPOXY_DUINO)
  delay(1000); // wait for stability on some boards to prevent garbage Serial
#endif
  Serial.begin(9600);

#if UNIT_TEST
  while (!Serial);
#endif
  connectWifi();
  startServer();
  initSensor();
}

void loop()
{
  getSensorValue();

  runServer();
  delay(1000);

#if UNIT_TEST
  TestRunner::run();
#endif
}
