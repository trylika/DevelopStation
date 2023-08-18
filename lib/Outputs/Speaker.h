#ifndef Speaker_h
#define Speaker_h

#include <NonBlockingRtttl.h>

#define SPEAKER_PIN 9

namespace Speaker {
    void update();
    void toggleEnabled();
    void play();
    void playLong();
}

#endif
