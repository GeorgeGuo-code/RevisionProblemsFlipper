#include <Arduino.h>
#include "pin_config.h"
#include "motor_driver.h"

// #define MOTOR_ROUND_STEP 2048  // 2048 steps per round for 28BYJ-48; not used in current code but may be useful for future features
#define MOTOR_HALF_STEP 4096  // 4096 steps per round for 28BYJ-48 in half-step mode
#define ROTATION_SPEED 2  // ms per step

// half-step sequence for 28BYJ-48
void motor_control(int step, int motorChoice) {
  int IN1, IN2, IN3, IN4;
  switch (motorChoice) {
    case 1:
      IN1 = motor1_IN1;
      IN2 = motor1_IN2;
      IN3 = motor1_IN3;
      IN4 = motor1_IN4;
      break;
    case 2:
      IN1 = motor2_IN1;
      IN2 = motor2_IN2;
      IN3 = motor2_IN3;
      IN4 = motor2_IN4;
      break;
    case 3:
      IN1 = motor3_IN1;
      IN2 = motor3_IN2;
      IN3 = motor3_IN3;
      IN4 = motor3_IN4;
      break;
  }
  switch (step) {
    case 0:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 1:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 2:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 3:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 4:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 5:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      break;
    case 6:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    case 7:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
  }
}

// rotate appointed steps backward
void motor_rotateBackward(int steps, int motorChoice) {
  for (int i = 0; i < steps; i++) {
    motor_control(i % 8, motorChoice);
    delay(ROTATION_SPEED);
  }
}

// rotate appointed steps forward
void motor_rotateForward(int steps, int motorChoice) {
  for (int i = 0; i < steps; i++) {
    motor_control(7 - (i % 8), motorChoice);
    delay(ROTATION_SPEED);
  }
}

// rotate signed steps; only allows move forward; if steps < 0, steps += 4096; -4096 <= steps <= 4096
void motor_rotateSteps(int steps, int motorChoice) {
  if (steps > 0) {
    motor_rotateForward(steps, motorChoice);
  } else if (steps < 0) {
    motor_rotateForward(steps + 4096 * reduction_ratio, motorChoice);
  }
}

// rotate appointed angles; 0 to move forward, 1 to move backward
void motor_rotateAngle(float angle, int motorChoice, bool back) {
  int steps = (int)(MOTOR_HALF_STEP * (angle / 360.0));
  if (back) {
    motor_rotateBackward(steps, motorChoice);
  } else {
    motor_rotateForward(steps, motorChoice);
  }
}