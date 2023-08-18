#include "Displays.h"

namespace Displays {
    const uint8_t displayFull[] = {0b01111111, 0b01111111, 0b01111111, 0b01111111};
    const uint8_t displayNoData[] = {0b01000000, 0b01000000, 0b01000000, 0b01000000};
    const uint8_t displayClear[] = {0x00, 0x00, 0x00, 0x00};
    const uint8_t displayNoDot = 0b00000000;
    const uint8_t displayMiddleDot = 0b01000000;

    TM1637Display displays[DISPLAY_COUNT] = {
        TM1637Display (DISPLAY_CLOCK_CLK, DISPLAY_CLOCK_DIO),
        TM1637Display (DISPLAY_VALUE_ONE_CLK, DISPLAY_VALUE_ONE_DIO),
        TM1637Display (DISPLAY_VALUE_TWO_CLK, DISPLAY_VALUE_TWO_DIO),
    };

    void setup() {
        for (uint8_t i = 0; i < DISPLAY_COUNT; i++) {
            displays[i].setBrightness(3); // 1 - 7
            displays[i].setSegments(displayFull);
        }
    }

    void update(uint8_t id, uint32_t data, uint8_t dots) {
        displays[id].showNumberDecEx(data, dots, true);
    }

    void clear(uint8_t id) {
        displays[id].setSegments(displayClear);
    }

    void noData(uint8_t id) {
        displays[id].setSegments(displayNoData);
    }

    int32_t calculateDisplayableTime(int32_t secondsToDisplay) {
        uint32_t seconds = (int)(secondsToDisplay % 60);
        uint32_t minutes = (int)(secondsToDisplay / 60);

        return minutes * 100 + seconds;
    }
}
