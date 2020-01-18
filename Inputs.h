#ifndef Inputs_h
#define Inputs_h

#include <stdint.h>
#include <Arduino.h>
#include <Type4067Mux.h>
#include <Encoder.h>

#define BUTTON_DEBOUNCE_DELAY 25

#define BUTTON_LIGHTING_TOGGLE 2
#define BUTTON_THERMOMETER_TOGGLE 1
#define BUTTON_STOP_WATCH_TOGGLE 0

#define BUTTON_STOP_WATCH_START_PAUSE 14
#define BUTTON_STOP_WATCH_STOP 13
#define BUTTON_STOP_WATCH_ALARM_SELECTOR_PRECISION 15


#define ENCODER_TIME_PIN_1 0
#define ENCODER_TIME_PIN_2 1

namespace Inputs {
  const uint8_t buttonCount = 6;
  const uint8_t buttonPins[buttonCount] = {
    BUTTON_THERMOMETER_TOGGLE,
    BUTTON_STOP_WATCH_TOGGLE,
    BUTTON_STOP_WATCH_START_PAUSE,
    BUTTON_STOP_WATCH_STOP,
    BUTTON_STOP_WATCH_ALARM_SELECTOR_PRECISION,
    BUTTON_LIGHTING_TOGGLE,
  };
  
  void update();
  void processPressed(void (*action)(uint8_t));
  void processReleased(void (*action)(uint8_t));
  void processToggled(void (*action)(uint8_t));
  int32_t readEncoder();
  void resetEncoder();
}

#endif
