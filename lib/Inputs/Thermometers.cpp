#include "Thermometers.h"

namespace Thermometers {
    uint8_t devicesCount = 0;
    bool devicesStatus[SENSOR_MAX_COUNT] = {false, false};
    float temperatures[SENSOR_MAX_COUNT] = {0.0, 0.0};

    OneWire oneWire(ONEWIRE_PIN);
    DallasTemperature sensors(&oneWire);
    DeviceAddress devices[SENSOR_MAX_COUNT];

    void setup() {
        sensors.begin();
        sensors.setResolution(SENSOR_RESOLUTION);
        sensors.setWaitForConversion(false);
        sensors.setCheckForConversion(true);

        devicesCount = sensors.getDeviceCount();
        if (devicesCount > SENSOR_MAX_COUNT) {
            devicesCount = SENSOR_MAX_COUNT;
        }
        for (int i = 0; i < devicesCount; i++) {
            sensors.getAddress(devices[i], i);
        }
    }

    void update() {
        if (!Timer::updateQuarterSecond) {
            return;
        }

        sensors.requestTemperatures();
        // sensors.isConversionComplete();

        for (int i = 0;  i < devicesCount;  i++) {
            if (sensors.isConnected(devices[i])) {
                if (devicesStatus[i]) {
                    // Moving average, with 10 readings window
                    temperatures[i] = (9.0f * temperatures[i] + sensors.getTempC(devices[i])) / 10.0f;
                } else {
                    temperatures[i] = sensors.getTempC(devices[i]);
                    devicesStatus[i] = true;
                }
            } else {
                devicesStatus[i] = false;
            }
        }
    }
}
