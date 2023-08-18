#include "Thermometer.h"

namespace Thermometer {
    OneWire oneWire(ONEWIRE_PIN);
    DallasTemperature sensors(&oneWire);
    DeviceAddress sensorAddress1 = {0x28, 0x5F, 0x57, 0x77, 0x91, 0x3, 0x2, 0x94};
    DeviceAddress sensorAddress2 = {0x28, 0x5F, 0xE6, 0x76, 0xE0, 0x01, 0x3C, 0xED};
    float temperatureCelcius = 0.0;

    void setup() {
        sensors.begin();
        sensors.setResolution(SENSOR_RESOLUTION);
    }

    void update(bool force) {
        if (!force && (!Timer::updateHalfSecond)) {
            return;
        }

        sensors.requestTemperaturesByAddress(sensorAddress1);
        temperatureCelcius = sensors.getTempC(sensorAddress1);
        uint16_t temperatureCelciusDisplayable = (uint16_t)(temperatureCelcius * 100.0);
        temperatureCelciusDisplayable = constrain(temperatureCelciusDisplayable, 0, 9999);
        Displays::update(DISPLAY_VALUE_ONE_ID, temperatureCelciusDisplayable, Displays::displayMiddleDot);

        sensors.requestTemperaturesByAddress(sensorAddress2);
        temperatureCelcius = sensors.getTempC(sensorAddress2);
        temperatureCelciusDisplayable = (uint16_t)(temperatureCelcius * 100.0);
        temperatureCelciusDisplayable = constrain(temperatureCelciusDisplayable, 0, 9999);
        Displays::update(DISPLAY_VALUE_TWO_ID, temperatureCelciusDisplayable, Displays::displayMiddleDot);

        // int deviceCount = sensors.getDeviceCount();
        // sensors.requestTemperatures();

        // for (int i = 0;  i < deviceCount;  i++)
        // {
        //     temperatureCelcius = sensors.getTempCByIndex(i);
        //     uint16_t temperatureCelciusDisplayable = (uint16_t)(temperatureCelcius * 100.0);
        //     temperatureCelciusDisplayable = constrain(temperatureCelciusDisplayable, 0, 9999);

        //     if (i == 0) {
        //         Displays::update(DISPLAY_ONE_ID, true, temperatureCelciusDisplayable, Displays::displayMiddleDot);
        //     } else {
        //         Displays::update(DISPLAY_THREE_ID, true, temperatureCelciusDisplayable, Displays::displayMiddleDot);
        //     }
        // }
    }
}
