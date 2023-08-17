#ifndef Timer_h
#define Timer_h

#include <stdint.h>
#include <TimerOne.h>

#define TIMER_INTERRUPT_DELAY 250000 // 250ms

namespace Timer {
  extern uint32_t quarterSecondsCount;
  extern uint32_t secondsCount;
  extern bool updateQuarterSecond;
  extern bool updateHalfSecond;
  extern bool updateSecond;

  void timedInterrupt();
  void setup();
  void update();
}

#endif
