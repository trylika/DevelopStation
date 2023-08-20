#include "main.h"

void setup(void) {
    // Debug
    Serial.begin(115200);

    // Inputs
    Inputs::setup();
    Timer::setup();
    Thermometers::setup();

    // Outputs
    Displays::setup();
    Lighting::setup();
    Speaker::setup();

    // StopWatch
    // StopWatch::setup();
}

void loop(void) {
    // Inputs
    Inputs::update();
    Inputs::processPressed(&inputActionPressed);
    Inputs::processReleased(&inputActionReleased);

    Thermometers::update();

    Timer::update();

    // Outputs
    if (Timer::updateHalfSecond) {
        for (uint8_t i = 0;  i < Thermometers::devicesCount;  i++) {
            if (Thermometers::devicesStatus[i]) {
                if (i == 0) {
                    Displays::update(
                        DISPLAY_VALUE_ONE_ID,
                        Displays::calculateDisplayableTemp(Thermometers::temperatures[i]),
                        Displays::displayMiddleDot
                    );
                } else {
                    Displays::update(
                        DISPLAY_VALUE_TWO_ID,
                        Displays::calculateDisplayableTemp(Thermometers::temperatures[i]),
                        Displays::displayMiddleDot
                    );
                }
            } else {
                if (i == 0) {
                    Displays::noData(DISPLAY_VALUE_ONE_ID);
                } else {
                    Displays::noData(DISPLAY_VALUE_TWO_ID);
                }
            }
        }
    }
    // Displays::update();
    // Lighting::update();
    Speaker::update();

    // StopWatch
    StopWatch::update();
}

void inputActionPressed(uint8_t input) {
    switch (input) {
        case BUTTON_STOP_WATCH_START_PAUSE:
            StopWatch::startPauseAction();
            break;
        case BUTTON_STOP_WATCH_STOP:
            StopWatch::stopAction();
            break;
        case BUTTON_STOP_WATCH_ALARM_SELECTOR_PRECISION:
            StopWatch::toggleAlarmSelectorPrecision();
            break;
        case BUTTON_LIGHTING_TOGGLE:
            Lighting::setEnabled(false);
            break;
        case BUTTON_SPEAKER_TOGGLE:
            Speaker::setEnabled(false);
            break;
    }
}

void inputActionReleased(uint8_t input) {
    switch (input) {
        case BUTTON_LIGHTING_TOGGLE:
            Lighting::setEnabled(true);
            break;
        case BUTTON_SPEAKER_TOGGLE:
            Speaker::setEnabled(true);
            break;
    }
}
