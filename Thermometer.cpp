#include "Thermometer.h"

namespace Thermometer {
  OneWire oneWire(ONEWIRE_PIN);
  DallasTemperature sensor(&oneWire);
  DeviceAddress sensorAddress = {0x28, 0x5F, 0x57, 0x77, 0x91, 0x3, 0x2, 0x94};
  bool enabled = true;
  float temperatureCelcius = 0.0;  
    
  void setup() {  
    sensor.begin();
    sensor.setResolution(sensorAddress, SENSOR_RESOLUTION);
  } 

  void toggleEnabled() {
    enabled = !enabled;
    if (enabled) {
      update(true);
    } else {
      Displays::update(DISPLAY_ONE_ID, false);
    }    
  }

  void update(bool force = false) {
    if (!force && (!enabled || !Timer::updateHalfSecond)) {
      return;
    }

    sensor.requestTemperaturesByAddress(sensorAddress);
    temperatureCelcius = sensor.getTempC(sensorAddress);
    uint16_t temperatureCelciusDisplayable = (uint16_t)(temperatureCelcius * 100.0);
    temperatureCelciusDisplayable = constrain(temperatureCelciusDisplayable, 0, 9999);    

    Displays::update(DISPLAY_ONE_ID, true, temperatureCelciusDisplayable, Displays::displayMiddleDot);
  }
}
