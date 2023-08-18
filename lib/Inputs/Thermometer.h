#ifndef Thermometer_h
#define Thermometer_h

#include <stdint.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Displays.h>
#include <Timer.h>

#define ONEWIRE_PIN 15
#define SENSOR_RESOLUTION 12
#define SENSOR_COUNT 2

namespace Thermometer {
    extern float temperatureCelcius;

    void setup();
    void update(bool force = false);
}

#endif
