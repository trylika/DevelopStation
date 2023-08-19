#ifndef Thermometers_h
#define Thermometers_h

#include <stdint.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Timer.h>

#define ONEWIRE_PIN 15
#define SENSOR_RESOLUTION 12
#define SENSOR_MAX_COUNT 2

namespace Thermometers {
    extern uint8_t devicesCount;
    extern bool devicesStatus[];
    extern float temperatures[];

    void setup();
    void update();
}

#endif
