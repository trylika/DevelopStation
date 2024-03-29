#ifndef Speaker_h
#define Speaker_h

#include <NonBlockingRtttl.h>

#define SPEAKER_PIN 9

namespace Speaker {
    void setup();
    void update();
    void setEnabled(bool value);
    void playShort();
    void playLong();
}

#endif
