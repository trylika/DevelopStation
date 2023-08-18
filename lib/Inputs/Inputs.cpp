#include "Inputs.h"

namespace Inputs {
    bool buttonState[buttonCount] = {false, false, false, false, false};
    bool buttonLastState[buttonCount] = {false, false, false, false, false};
    bool buttonChanged[buttonCount] = {false, false, false, false, false};
    uint32_t buttonLastChange[buttonCount] = {0, 0, 0, 0, 0};
    Mux mux(
        Pin(MUX_SIG, INPUT_PULLUP, PinType::Digital),
        Pinset(MUX_S0, MUX_S1, MUX_S2, MUX_S3),
        MUX_EN
    );
    Encoder rotaryEncoder(ENCODER_TIME_PIN_1, ENCODER_TIME_PIN_2);

    void update() {
        for (int i = 0; i < buttonCount; i++) {
            uint32_t ms = millis();
            int buttonValue = (bool)mux.read(buttonPins[i]);
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

    void processChanged(void (*action)(uint8_t)) {
        for(int i = 0; i < buttonCount; i++) {
            if(buttonChanged[i]) {
                action(buttonPins[i]);
            }
        }
    }

    int32_t readEncoder() {
        return (int)(rotaryEncoder.read() / 4);
    }

    void resetEncoder() {
        rotaryEncoder.write(0);
    }
}
