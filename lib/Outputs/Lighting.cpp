#include "Lighting.h"

namespace Lighting {
    bool enabled = true;

    void setup() {
        pinMode(LIGHTING_PIN, OUTPUT);
        digitalWrite(LIGHTING_PIN, HIGH);
    }

    void setEnabled(bool value) {
        enabled = value;

        if (enabled) {
            digitalWrite(LIGHTING_PIN, HIGH);
        } else {
            digitalWrite(LIGHTING_PIN, LOW);
        }
    }
}
