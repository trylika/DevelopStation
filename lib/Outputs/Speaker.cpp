#include "Speaker.h"

namespace Speaker {
    bool enabled = true;

    void toggleEnabled() {
        enabled = !enabled;
    }

    void play() {
        if (!enabled) {
            return;
        }

        // TimerFreeTone(SPEAKER_PIN, NOTE_C4, 100);
    }

    void playLong() {
        if (!enabled) {
            return;
        }

        // TimerFreeTone(SPEAKER_PIN, NOTE_C4, 500);
    }
}
