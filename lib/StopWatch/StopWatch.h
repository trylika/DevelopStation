#ifndef StopWatch_h
#define StopWatch_h

#include <stdint.h>
#include <Inputs.h>
#include <Timer.h>
#include <Displays.h>
#include <Speaker.h>

#define STOP_WATCH_MODE_SELECT 0
#define STOP_WATCH_MODE_RUNNING 1
#define STOP_WATCH_MODE_PAUSED 2
#define STOP_WATCH_MODE_STOPPED 3

#define STOP_WATCH_ALARM_SELECTOR_PRECISIONS 3

namespace StopWatch {
    void update();

    void updateTimeDisplay(bool force = false);

    void advanceTime();
    int32_t getTimeToShow();
    void processAlarm();

    void startPauseAction();
    void stopResetAction();
    void alarmSelectorPrecisionAction();
    void alarmSelectorAction();

    void start();
    void pause();
    void resume();
    void stop();
    void reset();

    void resetTimeData();
    void resetAlarmData();
}

#endif
