#include "main.h"

void setup(void) {
  //Serial.begin(9600);
  //Serial.print("Temperature = "); Serial.print(temperatureCelcius); Serial.println(" Celsius");

  Timer::setup();
  Displays::setup();
  Thermometer::setup();
  Lighting::setup();
}

void loop(void) {
  Timer::update();

  Inputs::update();
  Inputs::processPressed(&inputActionPressed);
  Inputs::processToggled(&inputActionToggled);

  Thermometer::update();

  StopWatch::update();
}

void inputActionPressed(uint8_t input) {
  if (input == BUTTON_STOP_WATCH_START_PAUSE) {
    StopWatch::startPauseAction();
  } else if (input == BUTTON_STOP_WATCH_STOP) {
    StopWatch::stopAction();
  } else if (input == BUTTON_STOP_WATCH_ALARM_SELECTOR_PRECISION) {
    StopWatch::toggleAlarmSelectorPrecision();
  }
}

void inputActionToggled(uint8_t input) {
  if (input == BUTTON_THERMOMETER_TOGGLE) {
    Thermometer::toggleEnabled();
  } else if (input == BUTTON_STOP_WATCH_TOGGLE) {
    StopWatch::toggleEnabled();
  } else if (input == BUTTON_LIGHTING_TOGGLE) {
    Lighting::toggleEnabled();
  }
}
