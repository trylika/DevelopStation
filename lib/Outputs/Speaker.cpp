#include "Speaker.h"

namespace Speaker {
    bool enabled = true;
    const char * siren = "siren:d=8,o=5,b=100:d,e,d,e,d,e,d,e";
    const char * two_short = "two_short:d=4,o=5,b=100:16e6,16e6";

    void update() {
        rtttl::play();
    }

    void toggleEnabled() {
        enabled = !enabled;
    }

    void play() {
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
