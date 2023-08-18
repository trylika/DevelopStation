#include "Speaker.h"

namespace Speaker {
    bool enabled = true;
    const char * siren = "siren:d=8,o=5,b=100:d,e,d,e,d,e,d,e";
    const char * two_short = "two_short:d=4,o=5,b=100:16e6,16e6";

    void setup() {
        pinMode(SPEAKER_PIN, OUTPUT);
        digitalWrite(SPEAKER_PIN, LOW);
    }

    void update() {
        rtttl::play();
    }

    void setEnabled(bool value) {
        enabled = value;

        if (!enabled) {
            rtttl::stop();
        }
    }

    void playShort() {
        if (!enabled) {
            return;
        }

        rtttl::begin(SPEAKER_PIN, two_short);
    }

    void playLong() {
        if (!enabled) {
            return;
        }

        rtttl::begin(SPEAKER_PIN, siren);
    }
}
