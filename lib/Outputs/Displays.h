#ifndef Displays_h
#define Displays_h

#include <Arduino.h>
#include <stdint.h>
#include <TM1637Display.h>

#define DISPLAY_COUNT 3

#define DISPLAY_CLOCK_ID 0
#define DISPLAY_CLOCK_CLK 19
#define DISPLAY_CLOCK_DIO 18

#define DISPLAY_VALUE_ONE_ID 1
#define DISPLAY_VALUE_ONE_CLK 21
#define DISPLAY_VALUE_ONE_DIO 20

#define DISPLAY_VALUE_TWO_ID 2
#define DISPLAY_VALUE_TWO_CLK 18
#define DISPLAY_VALUE_TWO_DIO 19

namespace Displays {
    extern const uint8_t displayFull[];
    extern const uint8_t displayNoData[];
    extern const uint8_t displayClear[];
    extern const uint8_t displayNoDot;
    extern const uint8_t displayMiddleDot;

    void setup();
    void update(uint8_t id, int32_t data = 0, uint8_t dots = 0);
    void clear(uint8_t id);
    void noData(uint8_t id);
    int32_t calculateDisplayableTime(int32_t secondsToDisplay);
    int32_t calculateDisplayableTemp(float temperature);
}

#endif
