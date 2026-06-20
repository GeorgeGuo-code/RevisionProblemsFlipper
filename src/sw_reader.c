#include <arduino.h>
#include "sw_reader.h"
#include "pin_config.h"

#define DEBOUNCE_DELAY 100 // ms

// duration detection
int swDuration(int sw) {
  // wait for sw press; do nothing
  while (digitalRead(sw) == HIGH) {
    // wait for sw press
  }

  // sw is pressed; start timing
  int currentTime = millis();
  while (digitalRead(sw) == LOW) {
    // wait for sw release
  }
  int duration = millis() - currentTime;
  return duration;
}

// read which sw is pressed; return 0 if no sw is pressed, 1-4 for sw1-4
int readSW() {
  if (digitalRead(sw1) == LOW) {
    if (swDuration(sw1) > DEBOUNCE_DELAY) {
      return 1; // debounce: ignore if duration is too short
    }
  }

  if (digitalRead(sw2) == LOW) {
    if (swDuration(sw2) > DEBOUNCE_DELAY) {
      return 2; // debounce: ignore if duration is too short
    }
  }

  if (digitalRead(sw3) == LOW) {
    if (swDuration(sw3) > DEBOUNCE_DELAY) {
      if (digitalRead(sw4) == LOW) {
        return 5; // if sw3 and sw4 are both pressed, prioritize sw4
      }
      return 3;
    }  
  }

  if (digitalRead(sw4) == LOW) {
    if (swDuration(sw4) > DEBOUNCE_DELAY) {
      if (digitalRead(sw3) == LOW) {
        return 5; // if sw3 and sw4 are both pressed, prioritize sw4
      }
      return 4;
    }
  }
  return 0; // no sw pressed
}