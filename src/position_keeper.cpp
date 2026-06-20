#include <arduino.h>
#include <Preferences.h>
#include "position_keeper.h"
#include "pin_config.h"
#include "motor_driver.h"

Preferences preferences;

// save current position; 3 motors; initialized to 0
void saveMotorPosition(int motorChoice, int steps) {
  preferences.begin("motor_positions", false); // open preferences with namespace "motor_positions"
  switch (motorChoice) {
    case 1:
      preferences.putInt("motor1_position", steps);
      break;
    case 2:
      preferences.putInt("motor2_position", steps);
      break;
    case 3:
      preferences.putInt("motor3_position", steps);
      break;
  }
  preferences.end(); // close preferences

  // buzzer prompt tone
  int saveTime = millis();
  while (millis() - saveTime < 500) { // buzz for 500 ms
    digitalWrite(buzzerPin, HIGH); // turn on buzzer
  }
  digitalWrite(buzzerPin, LOW); // turn off buzzer

  Serial.println("Saved motor " + String(motorChoice) + " position: " + String(steps) + " steps");
}

// read position
int readMotorPosition(int motorChoice) {
  preferences.begin("motor_positions", true); // open preferences with namespace "motor_positions" in read-only mode
  int position = 0;
  switch (motorChoice) {
    case 1:
      position = preferences.getInt("motor1_position", 0); // default to 0 if not set
      break;
    case 2:
      position = preferences.getInt("motor2_position", 0); // default to 0 if not set
      break;
    case 3:
      position = preferences.getInt("motor3_position", 0); // default to 0 if not set
      break;
  }
  preferences.end(); // close preferences

  Serial.println("Read motor " + String(motorChoice) + " position: " + String(position) + " steps");
  return position;
}

// reset position to 0; for testing use
void resetMotorPosition(int motorChoice) {
  preferences.begin("motor_positions", false); // open preferences with namespace "motor_positions"
  switch (motorChoice) {
    case 1:
      preferences.putInt("motor1_position", 0);
      break;
    case 2:
      preferences.putInt("motor2_position", 0);
      break;
    case 3:
      preferences.putInt("motor3_position", 0);
      break;
  }
  preferences.end(); // close preferences

  Serial.println("Reset motor " + String(motorChoice) + " position to 0");
}

// reset motor position to 0 by rotating back to 0
void resetMotorPositionByRotation(int motorChoice) {
  int current_position = readMotorPosition(motorChoice);
  motor_rotateSteps(-current_position, motorChoice); // rotate back to 0
  saveMotorPosition(motorChoice, 0); // update saved position to 0
}