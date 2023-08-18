#include "Displays.h"

namespace Displays {
    TM1637Display displays[DISPLAY_COUNT] = {
        TM1637Display (DISPLAY_ONE_CLK, DISPLAY_ONE_DIO),
        TM1637Display (DISPLAY_TWO_CLK, DISPLAY_TWO_DIO),
    };

    void setup() {
        for (uint8_t i = 0; i < DISPLAY_COUNT; i++) {
            displays[i].setBrightness(2); // 1 - 7
            displays[i].setSegments(displayFull);
        }
    }

    void update(uint8_t id, bool enabled, uint32_t data, uint8_t dots) {
        if (enabled) {
            displays[id].showNumberDecEx(data, dots, true);
        } else {
            displays[id].setSegments(displayClear);
        }
    }

    int32_t calculateDisplayableTime(int32_t secondsToDisplay) {
        uint32_t seconds = (int)(secondsToDisplay % 60);
        uint32_t minutes = (int)(secondsToDisplay / 60);

        return minutes * 100 + seconds;
    }
}
