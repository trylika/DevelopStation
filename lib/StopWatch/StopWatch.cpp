#include "StopWatch.h"

namespace StopWatch {
    const uint8_t alarmSelectorPrecisions[STOP_WATCH_ALARM_SELECTOR_PRECISIONS] = {60, 10, 1};

    uint8_t mode = STOP_WATCH_MODE_SELECT;
    bool blinking = false;

    int32_t timePassed = 0;
    int32_t timeStartedAt = 0;
    int32_t timePausedAt = 0;
    uint8_t timeDisplayableDot = Displays::displayMiddleDot;

    uint8_t alarmSelectorPrecisionSelected = 0;
    int32_t alarmInputLast = 0;
    int32_t alarmTime = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////

    void update() {
        switch (mode) {
            case STOP_WATCH_MODE_SELECT:
                updateTimeDisplay();
                break;
            case STOP_WATCH_MODE_RUNNING:
                advanceTime();
                updateTimeDisplay();
                processAlarm();
                break;
            case STOP_WATCH_MODE_PAUSED:
                updateTimeDisplay();
                break;
            case STOP_WATCH_MODE_STOPPED:
                updateTimeDisplay();
                break;
        }
    }

////////////////////////////////////////////////////////////////////////////////////////////////////

    void updateTimeDisplay(bool force) {
        if (mode != STOP_WATCH_MODE_RUNNING) {
            timeDisplayableDot = Displays::displayMiddleDot;
        } else if (Timer::updateHalfSecond) {
            timeDisplayableDot = timeDisplayableDot == Displays::displayNoDot ? Displays::displayMiddleDot : Displays::displayNoDot;
        }

        if (mode == STOP_WATCH_MODE_STOPPED && Timer::updateHalfSecond) {
            blinking = !blinking;
        }

        if (force || Timer::updateQuarterSecond) {
            if (blinking && mode == STOP_WATCH_MODE_STOPPED) {
                Displays::clear(DISPLAY_CLOCK_ID);
            } else {
                Displays::update(
                    DISPLAY_CLOCK_ID,
                    Displays::calculateDisplayableTime(getTimeToShow()),
                    timeDisplayableDot
                );
            }
        }
    }

////////////////////////////////////////////////////////////////////////////////////////////////////

    void advanceTime() {
        timePassed = (Timer::quarterSecondsCount - timeStartedAt) / 4;
    }

    int32_t getTimeToShow() {
        if (alarmTime == 0) {
            return timePassed;
        } else {
            return alarmTime - timePassed;
        }
    }

    void processAlarm() {
        if ((timePassed % 60) > 50 && Timer::updateSecond) {
            Speaker::playShort();
        }

        if (alarmTime == 0) {
            return;
        }

        if (timePassed >= alarmTime) {
            stop();
            Speaker::playLong();
        }
    }

////////////////////////////////////////////////////////////////////////////////////////////////////

    void startPauseAction() {
        switch (mode) {
            case STOP_WATCH_MODE_SELECT:
                start();
                break;
            case STOP_WATCH_MODE_RUNNING:
                pause();
                break;
            case STOP_WATCH_MODE_PAUSED:
                resume();
                break;
            case STOP_WATCH_MODE_STOPPED:
                reset();
                break;
        }
    }

    void stopResetAction() {
        switch (mode) {
            case STOP_WATCH_MODE_RUNNING:
            case STOP_WATCH_MODE_PAUSED:
                stop();
                break;
            case STOP_WATCH_MODE_SELECT:
            case STOP_WATCH_MODE_STOPPED:
                reset();
                break;
        }
    }

    void alarmSelectorPrecisionAction() {
        switch (mode) {
            case STOP_WATCH_MODE_SELECT:
                alarmSelectorPrecisionSelected++;
                if (alarmSelectorPrecisionSelected == STOP_WATCH_ALARM_SELECTOR_PRECISIONS) {
                    alarmSelectorPrecisionSelected = 0;
                }

                alarmInputLast = 0;
                Inputs::resetEncoder();
                break;
            case STOP_WATCH_MODE_RUNNING:
            case STOP_WATCH_MODE_PAUSED:
                break;
            case STOP_WATCH_MODE_STOPPED:
                reset();
                break;
        }
    }

    void alarmSelectorAction() {
        if (mode != STOP_WATCH_MODE_SELECT && mode != STOP_WATCH_MODE_STOPPED) {
            return;
        }

        int32_t alarmInput = Inputs::readEncoder() * alarmSelectorPrecisions[alarmSelectorPrecisionSelected];
        if (alarmInput == alarmInputLast) { //Encoder did not change
            return;
        }

        if (mode == STOP_WATCH_MODE_STOPPED) {
            reset();
            return;
        }

        if (mode == STOP_WATCH_MODE_SELECT) {
            int32_t alarmInputDiff = alarmInput - alarmInputLast;
            alarmInputLast = alarmInput;

            alarmTime = constrain(alarmTime + alarmInputDiff, 0, 5999); // Max displayable time 99minutes 59seconds
            updateTimeDisplay(true);
        }
    }

////////////////////////////////////////////////////////////////////////////////////////////////////

    void start() {
        resetTimeData();
        mode = STOP_WATCH_MODE_RUNNING;
        timeStartedAt = Timer::quarterSecondsCount;
    }

    void pause() {
        mode = STOP_WATCH_MODE_PAUSED;
        timePausedAt = Timer::quarterSecondsCount;
    }

    void resume() {
        mode = STOP_WATCH_MODE_RUNNING;
        timeStartedAt = timeStartedAt + Timer::quarterSecondsCount - timePausedAt;
    }

    void stop() {
        mode = STOP_WATCH_MODE_STOPPED;
    }

    void reset() {
        resetTimeData();
        resetAlarmData();
        mode = STOP_WATCH_MODE_SELECT;
    }

////////////////////////////////////////////////////////////////////////////////////////////////////

    void resetTimeData() {
        timePassed = 0;
        timeStartedAt = 0;
        timePausedAt = 0;
    }

    void resetAlarmData() {
        alarmSelectorPrecisionSelected = 0;
        alarmInputLast = 0;
        alarmTime = 0;
        Inputs::resetEncoder();
    }
}
