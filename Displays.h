#ifndef Displays_h
#define Displays_h

#include <stdint.h>
#include <TM1637Display.h>

#define DISPLAY_COUNT 2

#define DISPLAY_ONE_ID 0
#define DISPLAY_ONE_CLK 21
#define DISPLAY_ONE_DIO 20

#define DISPLAY_TWO_ID 1
#define DISPLAY_TWO_CLK 19
#define DISPLAY_TWO_DIO 18

namespace Displays {
  const uint8_t displayFull[] = {0b01111111, 0b01111111, 0b01111111, 0b01111111};
  const uint8_t displayNoData[] = {0b01000000, 0b01000000, 0b01000000, 0b01000000};
  const uint8_t displayClear[] = {0x00, 0x00, 0x00, 0x00};
  const uint8_t displayNoDot = 0b00000000;
  const uint8_t displayMiddleDot = 0b01000000;

  void setup();
  void update(uint8_t id, bool enabled, uint32_t data = 0, uint8_t dots = 0);
  int32_t calculateDisplayableTime(int32_t secondsToDisplay);
}

#endif
