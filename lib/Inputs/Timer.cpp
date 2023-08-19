#include "Timer.h"

namespace Timer {
    volatile uint32_t intCount = 0;
    uint32_t lastCount = 0;

    uint32_t quarterSecondsCount = 0;
    bool updateQuarterSecond = false;
    bool updateHalfSecond = false;
    bool updateSecond = false;

    void setup() {
        Timer1.initialize(TIMER_INTERRUPT_DELAY);
        Timer1.attachInterrupt(timedInterrupt);
    }

    void update() {
        //noInterrupts();
        quarterSecondsCount = intCount;
        //interrupts();

        updateQuarterSecond = (lastCount != quarterSecondsCount);
        updateHalfSecond = (lastCount / 2 != quarterSecondsCount / 2);
        updateSecond = (lastCount / 4 != quarterSecondsCount / 4);

        lastCount = quarterSecondsCount;
    }

    void timedInterrupt() {
        intCount++;
    }
}
