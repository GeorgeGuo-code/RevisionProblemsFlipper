#ifndef __PIN_CONFIG_H_
#define __PIN_CONFIG_H_

// motor pins; 3 motors; active high; IN1-4 for each motor
#define motor1_IN1 26
#define motor1_IN2 25
#define motor1_IN3 33
#define motor1_IN4 32

#define motor2_IN1 27
#define motor2_IN2 14
#define motor2_IN3 12
#define motor2_IN4 13

#define motor3_IN1 5
#define motor3_IN2 18
#define motor3_IN3 19
#define motor3_IN4 21

// sw pins; 4 sws; active low
#define sw1 36
#define sw2 39
#define sw3 34
#define sw4 35

// buzzer pin; control buzzer; active high
#define buzzerPin 2

// led pin; control waterfall light; active low
#define ledPin 4

// OLED pins
#define OLED_SCL 22
#define OLED_SDA 23

// constants
#define MOTOR_HALF_STEP 4096  // 4096 steps per round for 28BYJ-48 in half-step mode
#define MOTOR_NUM 3 // number of motors
#define reduction_ratio 2 // reduction ratio for the gear train

#define SCREEN_WIDTH      128   // OLED display width, in pixels
#define SCREEN_HEIGHT     64    // OLED display height, in pixels
#define OLED_RESET        -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS    0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32


#endif  