#ifndef main_h
#define main_h

#include <Arduino.h>
#include <Timer.h>
#include <Inputs.h>
#include <Speaker.h>
#include <Displays.h>
#include <Thermometer.h>
#include <StopWatch.h>
#include <Lighting.h>

void setup();
void loop();
void inputActionPressed(uint8_t input);
void inputActionReleased(uint8_t input);

#endif
