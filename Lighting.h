#ifndef Lighting_h
#define Lighting_h

#include <stdint.h>
#include <Arduino.h>

#define LIGHTING_PIN 10

namespace Lighting {
  void setup();
  void toggleEnabled();
}

#endif
