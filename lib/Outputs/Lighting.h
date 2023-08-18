#ifndef Lighting_h
#define Lighting_h

#include <Arduino.h>
#include <stdint.h>

#define LIGHTING_PIN 10

namespace Lighting {
    void setup();
    void setEnabled(bool value);
}

#endif
