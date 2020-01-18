#ifndef Thermometer_h
#define Thermometer_h

#include <stdint.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Displays.h"
#include "Timer.h"

#define ONEWIRE_PIN 15
#define SENSOR_RESOLUTION 12

namespace Thermometer {
  extern float temperatureCelcius;

  void setup();
  void toggleEnabled();
  void update(bool force = false);  
}

#endif
