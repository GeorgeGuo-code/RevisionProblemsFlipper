#include <Arduino.h>
#include "pin_config.h"
#include "correct_answer.h"
#include "motor_driver.h"
#include "sw_reader.h"
#include "answer_judger.h"
#include "position_keeper.h"

// OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 构造对象 连接到I2C(SDA、SCL引脚)的SSD1306声明
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// structure for motors
struct Motor {
  int current_angle; // current angle in degrees
  int current_steps; // current steps

  int current_question; // current question number
  int current_score; // current score
};

// initialize motors
Motor motor1 = {0, 0, 1, 0}; // motor 1 for flipper 1
Motor motor2 = {0, 0, 1, 0}; // motor 2 for flipper 2
Motor motor3 = {0, 0, 1, 0}; // motor 3 for flipper 3

struct Motor motors[MOTOR_NUM] = {motor1, motor2, motor3};

// current manipulated motor
int currentMotor = 1; // default to motor 1

void setup() {
  // pinMode
  // 3 motors
  pinMode(motor1_IN1, OUTPUT);
  pinMode(motor1_IN2, OUTPUT);
  pinMode(motor1_IN3, OUTPUT);
  pinMode(motor1_IN4, OUTPUT);
  pinMode(motor2_IN1, OUTPUT);
  pinMode(motor2_IN2, OUTPUT);
  pinMode(motor2_IN3, OUTPUT);
  pinMode(motor2_IN4, OUTPUT);
  pinMode(motor3_IN1, OUTPUT);
  pinMode(motor3_IN2, OUTPUT);
  pinMode(motor3_IN3, OUTPUT);
  pinMode(motor3_IN4, OUTPUT);

  // sws
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);
  pinMode(sw4, INPUT_PULLUP);

  // buzzer
  pinMode(buzzerPin, OUTPUT);

  // led
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  // OLED
  Wire.begin(OLED_SDA, OLED_SCL);

  // 检查初始化是否成功
  if(!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C 是常见的I2C地址，也尝试0x3D
  Serial.println(F("SSD1306 allocation failed"));
  for(;;); // 停止在这里，防止后续崩溃
  }

  // 只有初始化成功，才执行以下操作
  OLED.clearDisplay();
  OLED.setCursor(1, 1);
  OLED.setTextColor(SSD1306_WHITE);
  OLED.println("Resetting...");
  OLED.display();

  // serial; debug use
  Serial.begin(115200);
  Serial.println("步进电机控制初始化完毕：");

  // reset position
  resetMotorPositionByRotation(1);
  resetMotorPositionByRotation(2);
  resetMotorPositionByRotation(3);
}

void loop() {
  OLED.clearDisplay();
  OLED.setCursor(1, 1);
  OLED.println((String)"Current score: " + motors[currentMotor-1].current_score);
  OLED.println((String)"Question number: " + currentMotor + "-" + motors[currentMotor-1].current_question);
  OLED.println("Press SW1, SW2, SW3");
  OLED.println("to answer");
  OLED.println("Or press SW4 to");
  OLED.println("switch question set");
  OLED.display();

  Serial.println("等待按键输入...");
  int pressedSW;
  // sw control test
  while ((pressedSW = readSW()) == 0) {
    // wait for sw press
  }

  if (pressedSW == 5) { // if sw3 and sw4 are both pressed, save current motor position
    OLED.clearDisplay();
    OLED.setCursor(1, 1);
    OLED.println((String)"Motor" + currentMotor + (String)"position saved!");
    OLED.display();

    delay(1000);

    saveMotorPosition(currentMotor, motors[currentMotor - 1].current_steps);
    Serial.println("保存电机 " + String(currentMotor) + " 位置");
  }

  else if (pressedSW == 4) { // if sw4 is pressed, switch to next motor
    currentMotor = (currentMotor % MOTOR_NUM) + 1; // switch to next motor
    Serial.println("切换到电机 " + String(currentMotor));
  } 

  else if (motors[currentMotor - 1].current_question <= 20) { // if sw1-3 is pressed, answer question and rotate
    int result = judgeAnswer(currentMotor, motors[currentMotor - 1].current_question, pressedSW); // judge answer and give feedback
    Serial.println("第 " + String(motors[currentMotor - 1].current_question) + " 题");
    if (result) {
      motors[currentMotor - 1].current_score++; // update score
      Serial.println("回答正确！当前分数：" + String(motors[currentMotor - 1].current_score));
      
      OLED.clearDisplay();
      OLED.setCursor(1, 1);
      OLED.println("Correct! Score + 1");
      OLED.display();

      digitalWrite(ledPin, LOW); // turn on led
      digitalWrite(buzzerPin, LOW); // turn off buzzer
      delay(1000); // delay for 1 second
      digitalWrite(ledPin, HIGH); // turn off led

    } else {
      Serial.println("回答错误！当前分数：" + String(motors[currentMotor - 1].current_score));

      OLED.clearDisplay();
      OLED.setCursor(1, 1);
      OLED.println("Wrong!");
      OLED.display();

      digitalWrite(buzzerPin, HIGH); // turn on buzzer
      digitalWrite(ledPin, HIGH); // turn off led
      delay(1000); // delay for 1 second
      digitalWrite(buzzerPin, LOW); // turn off buzzer
    }
    motors[currentMotor - 1].current_question++; // move to next question

    // rotate to the next position; 18 degrees; reduction ratio 2
    motor_rotateAngle(18.0 * reduction_ratio, currentMotor, false); // rotate 18 degrees forward to the next question
    motors[currentMotor - 1].current_angle += 18 * reduction_ratio; // update current angle
    motors[currentMotor - 1].current_steps += (int)(MOTOR_HALF_STEP * (18 * reduction_ratio / 360.0)); // update current steps

    // when finishing all questions, the position is 0 again
    if (motors[currentMotor - 1].current_question == 20 + 1) {
      Serial.println("电机 " + String(currentMotor) + " 已完成所有问题！");
      Serial.println("最终分数：" + String(motors[currentMotor - 1].current_score));

      OLED.clearDisplay();
      OLED.setCursor(1, 1);
      OLED.println("All questions finished");
      OLED.println((String)"in set" + currentMotor);
      OLED.println((String)"Your score: " + motors[currentMotor].current_score);
      OLED.display();

      motor_rotateAngle(18.0 * reduction_ratio, currentMotor, false); // move to position 0
      saveMotorPosition(currentMotor, 0); // save position after finishing all questions
    }
  }
}