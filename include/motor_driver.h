#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#ifdef __cplusplus
extern "C" { 
#endif
void motor_control(int step, int motorChoice);
void motor_rotateBackward(int steps, int motorChoice);
void motor_rotateForward(int steps, int motorChoice);
void motor_rotateAngle(float angle, int motorChoice, bool back);
void motor_rotateSteps(int steps, int motorChoice);
#ifdef __cplusplus
}
#endif

#endif // MOTOR_DRIVER_H  