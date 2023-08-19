#ifndef Inputs_h
#define Inputs_h

#include <Arduino.h>
#include <stdint.h>
#include <Mux.h>
#include <Encoder.h>

using namespace admux;

#define INPUT_DEBOUNCE_DELAY 25

#define MUX_SIG 4
#define MUX_EN 9
#define MUX_S0 8
#define MUX_S1 7
#define MUX_S2 6
#define MUX_S3 5

#define BUTTON_LIGHTING_TOGGLE 0
#define BUTTON_SPEAKER_TOGGLE 1

#define BUTTON_STOP_WATCH_START_PAUSE 14
#define BUTTON_STOP_WATCH_STOP 13
#define BUTTON_STOP_WATCH_ALARM_SELECTOR_PRECISION 15

#define ENCODER_TIME_PIN_1 0
#define ENCODER_TIME_PIN_2 1

namespace Inputs {
    void setup();
    void update();
    void processPressed(void (*action)(uint8_t));
    void processReleased(void (*action)(uint8_t));
    void processChanged(void (*action)(uint8_t));
    int32_t readEncoder();
    void resetEncoder();
}

#endif
