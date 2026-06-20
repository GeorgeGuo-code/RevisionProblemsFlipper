#ifndef POSITION_KEEPER_H
#define POSITION_KEEPER_H

void saveMotorPosition(int motorChoice, int steps);
int readMotorPosition(int motorChoice);
void resetMotorPosition(int motorChoice);
void resetMotorPositionByRotation(int motorChoice);

#endif // POSITION_KEEPER_H