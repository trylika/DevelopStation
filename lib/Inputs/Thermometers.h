#ifndef Thermometers_h
#define Thermometers_h

#include <stdint.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Timer.h>
#include <Displays.h>

#define ONEWIRE_PIN 15
#define SENSOR_RESOLUTION 12
#define SENSOR_MAX_COUNT 2
#define SENSOR_ONE 0
#define SENSOR_TWO 1

#define CAL_DEVICES_COUNT 2
#define CAL_REFERENCE_LOW 0
#define CAL_REFERENCE_HIGH 1
#define CAL_RAW_LOW 2
#define CAL_RAW_HIGH 3

namespace Thermometers {
    extern uint8_t devicesCount;
    extern bool devicesStatus[];
    extern float temperatures[];

    void setup();
    void update();
    void updateDisplay();
    bool compareDeviceAddresses(DeviceAddress device1, DeviceAddress device2);
    float getTempCalibrated(DeviceAddress device);
}

#endif
