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
    // Displays::update(); - update per display
    if (Timer::updateHalfSecond) {
        // DISPLAY_VALUE_ONE_ID
        if (Thermometers::devicesStatus[SENSOR_ONE]) {
            Displays::update(
                DISPLAY_VALUE_ONE_ID,
                Displays::calculateDisplayableTemp(Thermometers::temperatures[SENSOR_ONE]),
                Displays::displayMiddleDot
            );
        } else {
            Displays::noData(DISPLAY_VALUE_ONE_ID);
        }

        // DISPLAY_VALUE_TWO_ID
        if (Thermometers::devicesStatus[SENSOR_TWO]) {
            Displays::update(
                DISPLAY_VALUE_TWO_ID,
                Displays::calculateDisplayableTemp(Thermometers::temperatures[SENSOR_TWO]),
                Displays::displayMiddleDot
            );
        } else {
            Displays::noData(DISPLAY_VALUE_TWO_ID);
        }
    }
    // Lighting::update(); - nothing to update
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
