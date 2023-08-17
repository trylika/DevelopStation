#include "Inputs.h"

namespace Inputs {
  bool buttonState[buttonCount] = {false, false, false, false, false, false};
  bool buttonLastState[buttonCount] = {false, false, false, false, false, false};
  bool buttonChanged[buttonCount] = {false, false, false, false, false, false};
  uint32_t buttonLastChange[buttonCount] = {0, 0, 0, 0, 0, 0};
//   Type4067Mux mux(4, INPUT_PULLUP, DIGITAL, 8, 7, 6, 5); // can be reduced to one input pin
//   Encoder rotaryEncoder(ENCODER_TIME_PIN_1, ENCODER_TIME_PIN_2);

  void update() {
    for (int i = 0; i < buttonCount; i++) {
      uint32_t ms = millis();
      int buttonValue = 0; //(bool)mux.read(buttonPins[i]);
      buttonValue = !buttonValue;

      if ((ms - buttonLastChange[i]) < BUTTON_DEBOUNCE_DELAY) {
        buttonChanged[i] = false;
      } else {
        buttonLastState[i] = buttonState[i];
        buttonState[i] = buttonValue;
        buttonChanged[i] = buttonState[i] != buttonLastState[i];
        if (buttonChanged[i]) {
          buttonLastChange[i] = ms;
        }
      }
    }
  }

  void processPressed(void (*action)(uint8_t)) {
    for(int i = 0; i < buttonCount; i++) {
      if(buttonState[i] && buttonChanged[i]) {
        action(buttonPins[i]);
      }
    }
  }

  void processReleased(void (*action)(uint8_t)) {
    for(int i = 0; i < buttonCount; i++) {
      if(!buttonState[i] && buttonChanged[i]) {
        action(buttonPins[i]);
      }
    }
  }

  void processToggled(void (*action)(uint8_t)) {
    for(int i = 0; i < buttonCount; i++) {
      if(buttonChanged[i]) {
        action(buttonPins[i]);
      }
    }
  }

  int32_t readEncoder() {
    // return (int)(rotaryEncoder.read() / 4);
    return 0;
  }

  void resetEncoder() {
    // rotaryEncoder.write(0);
  }
}
