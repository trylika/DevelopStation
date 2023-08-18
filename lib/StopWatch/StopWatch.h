#ifndef StopWatch_h
#define StopWatch_h

#include <stdint.h>
#include <Displays.h>
#include <Timer.h>
#include <Inputs.h>
#include <Speaker.h>

#define STOP_WATCH_MODE_SELECT 0
#define STOP_WATCH_MODE_RUNNING 1
#define STOP_WATCH_MODE_PAUSED 2
#define STOP_WATCH_MODE_STOPPED 3

#define STOP_WATCH_ALARM_SELECTOR_PRECISIONS 3

namespace StopWatch {
    const uint8_t alarmSelectorPrecisions[STOP_WATCH_ALARM_SELECTOR_PRECISIONS] = {60, 10, 1};

    void update(bool force = false);

    void updateDisplayableDot();
    void updateTimeDisplay(bool force = false);
    void updateStaticTimeDisplay(bool force = false);
    void updateAlarmDisplay(bool force = false);

    void advanceTime();
    int32_t getTimeToShow();
    void processAlarm();

    void toggleAlarmSelectorPrecision();
    void alarmSelector();

    void startPauseAction();
    void stopAction();

    void start();
    void pause();
    void resume();
    void stop();
    void reset();

    void resetTimeData();
    void resetAlarmData();
}

#endif
