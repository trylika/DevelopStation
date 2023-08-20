#include "Thermometers.h"

namespace Thermometers {
    uint8_t devicesCount = 0;
    bool devicesStatus[SENSOR_MAX_COUNT] = {false, false};
    float temperatures[SENSOR_MAX_COUNT] = {0.0, 0.0};

    OneWire oneWire(ONEWIRE_PIN);
    DallasTemperature sensors(&oneWire);
    DeviceAddress devices[SENSOR_MAX_COUNT];

    DeviceAddress knownDevices[2] = {
        {0x28, 0x5F, 0x57, 0x77, 0x91, 0x3, 0x2, 0x94},
        {0x28, 0x5F, 0xE6, 0x76, 0xE0, 0x01, 0x3C, 0xED},
    };
    // ReferenceLow, ReferenceHigh, RawLow, RawHigh
    const float sensorCalibration[2][4] = {
        {0.0f, 100.0f, 0.0f, 100.0f},
        {0.0f, 100.0f, 0.0f, 100.0f},
    };

    void setup() {
        sensors.begin();
        sensors.setResolution(SENSOR_RESOLUTION);
        sensors.setWaitForConversion(false);
        sensors.setCheckForConversion(true);

        devicesCount = sensors.getDeviceCount();
        if (devicesCount > SENSOR_MAX_COUNT) {
            devicesCount = SENSOR_MAX_COUNT;
        }
        for (uint8_t i = 0; i < devicesCount; i++) {
            sensors.getAddress(devices[i], i);
        }
    }

    void update() {
        if (!Timer::updateQuarterSecond) {
            return;
        }

        sensors.requestTemperatures();
        // sensors.isConversionComplete();

        for (uint8_t i = 0;  i < devicesCount;  i++) {
            if (sensors.isConnected(devices[i])) {
                if (devicesStatus[i]) {
                    // Moving average, with 10 readings window
                    temperatures[i] = (9.0f * temperatures[i] + getTempCalibrated(devices[i])) / 10.0f;
                } else {
                    temperatures[i] = getTempCalibrated(devices[i]);
                    devicesStatus[i] = true;
                }
            } else {
                devicesStatus[i] = false;
            }
        }
    }

    bool compareDeviceAddresses(DeviceAddress device1, DeviceAddress device2) {
        bool equal = true;
        for (uint8_t i = 0; i < 8; i++) {
            if (device1[i] != device2[i]) {
                equal = false;
                break;
            }
        }

        return equal;
    }

    float getTempCalibrated(DeviceAddress device) {
        uint8_t foundIndex = 255;
        for (uint8_t i = 0; i < sizeof(knownDevices)/sizeof(knownDevices[0]); i++) {
            if (compareDeviceAddresses(knownDevices[i], device)) {
                foundIndex = i;
                break;
            }
        }

        float temperature = sensors.getTempC(device);

        if (foundIndex != 255) {
            float rawRange =
                sensorCalibration[foundIndex][CAL_RAW_HIGH] - sensorCalibration[foundIndex][CAL_RAW_LOW];
            float referenceRange =
                sensorCalibration[foundIndex][CAL_REFERENCE_HIGH] - sensorCalibration[foundIndex][CAL_REFERENCE_LOW];

            temperature =
                (((temperature - sensorCalibration[foundIndex][CAL_RAW_LOW]) * referenceRange) / rawRange)
                + sensorCalibration[foundIndex][CAL_REFERENCE_LOW];
        }

        return temperature;
    }
}
