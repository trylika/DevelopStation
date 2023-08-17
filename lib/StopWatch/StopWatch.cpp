#include "StopWatch.h"

namespace StopWatch {
    bool enabled = true;

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

    void update(bool force) {
        if (!enabled) {
            return;
        }

        switch (mode) {
            case STOP_WATCH_MODE_SELECT:
                alarmSelector();
                updateAlarmDisplay(force);
                break;
            case STOP_WATCH_MODE_RUNNING:
                advanceTime();
                updateDisplayableDot();
                updateTimeDisplay(force);
                processAlarm();
                break;
            case STOP_WATCH_MODE_PAUSED:
            case STOP_WATCH_MODE_STOPPED:
                alarmSelector();
                updateStaticTimeDisplay(force);
                break;
        }
    }

////////////////////////////////////////////////////////////////////////////////////////////////////

    void updateDisplayableDot() {
        if (mode != STOP_WATCH_MODE_RUNNING || !Timer::updateHalfSecond) {
            return;
        }

        timeDisplayableDot = timeDisplayableDot == Displays::displayNoDot ? Displays::displayMiddleDot : Displays::displayNoDot;
    }

    void updateTimeDisplay(bool force) {
        if (!force && !Timer::updateQuarterSecond) {
            return;
        }

        Displays::update(
            DISPLAY_TWO_ID,
            true,
            Displays::calculateDisplayableTime(getTimeToShow()),
            timeDisplayableDot
        );
    }

    void updateStaticTimeDisplay(bool force) {
        if (!force && !Timer::updateHalfSecond) {
            return;
        }

        if (mode == STOP_WATCH_MODE_STOPPED) {
            blinking = !blinking;
        }

        if (blinking && mode == STOP_WATCH_MODE_STOPPED) {
            Displays::update(DISPLAY_TWO_ID, false);
        } else {
            Displays::update(
                DISPLAY_TWO_ID,
                true,
                Displays::calculateDisplayableTime(getTimeToShow()),
                Displays::displayMiddleDot
            );
        }
    }

    void updateAlarmDisplay(bool force) {
        if (!force && !Timer::updateHalfSecond) {
            return;
        }

        Displays::update(
            DISPLAY_TWO_ID,
            true,
            Displays::calculateDisplayableTime(alarmTime),
            Displays::displayMiddleDot
        );
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
            Speaker::play();
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

    void toggleAlarmSelectorPrecision() {
        if (!enabled || (mode != STOP_WATCH_MODE_SELECT && mode != STOP_WATCH_MODE_STOPPED)) {
            return;
        }

        if (mode == STOP_WATCH_MODE_STOPPED) {
            reset();
            return;
        }

        alarmSelectorPrecisionSelected++;
        if (alarmSelectorPrecisionSelected == STOP_WATCH_ALARM_SELECTOR_PRECISIONS) {
            alarmSelectorPrecisionSelected = 0;
        }
        alarmInputLast = 0;
        Inputs::resetEncoder();
    }

    void alarmSelector() {
        if (!enabled || (mode != STOP_WATCH_MODE_SELECT && mode != STOP_WATCH_MODE_STOPPED)) {
            return;
        }

        int32_t alarmInput = Inputs::readEncoder() * alarmSelectorPrecisions[alarmSelectorPrecisionSelected];
        int32_t alarmInputDiff = 0;
        if (alarmInput != alarmInputLast) {
            if (mode == STOP_WATCH_MODE_STOPPED) {
                reset();
                return;
            }

            alarmInputDiff = alarmInput - alarmInputLast;
            alarmInputLast = alarmInput;

            alarmTime = constrain(alarmTime + alarmInputDiff, 0, 5999); // 99minutes 59seconds
            updateAlarmDisplay(true);
        }
    }

////////////////////////////////////////////////////////////////////////////////////////////////////

    void toggleEnabled() {
        enabled = !enabled;
        if (enabled) {
            reset();
            update(true);
        } else {
            Displays::update(DISPLAY_TWO_ID, false);
        }
    }

    void startPauseAction() {
        if (!enabled) {
            return;
        }

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

    void stopAction() {
        if (!enabled) {
            return;
        }

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
