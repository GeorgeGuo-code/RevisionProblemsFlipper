#include <Arduino.h>
#include "answer_judger.h"
#include "correct_answer.h"
#include "pin_config.h"

// judge the answer of flipper1; return 1 if correct, 0 if wrong
int judgeAnswer1(int questionNum, int sw) {
  int answer;
  switch (sw) {
    case 1:
      answer = 1;
      break;
    case 2:
      answer = 2;
      break;
    case 3:
      answer = 3;
      break;
    default:
      return 0; // invalid switch
  }

  switch (questionNum) {
    case 1:
      return answer == flipper1_answer1;
    case 2:
      return answer == flipper1_answer2;
    case 3:
      return answer == flipper1_answer3;
    case 4:
      return answer == flipper1_answer4;
    case 5:
      return answer == flipper1_answer5;
    case 6:
      return answer == flipper1_answer6;
    case 7:
      return answer == flipper1_answer7;
    case 8:
      return answer == flipper1_answer8;
    case 9:
      return answer == flipper1_answer9;
    case 10:
      return answer == flipper1_answer10;
    case 11:
      return answer == flipper1_answer11;
    case 12:
      return answer == flipper1_answer12;
    case 13:
      return answer == flipper1_answer13;
    case 14:
      return answer == flipper1_answer14;
    case 15:
      return answer == flipper1_answer15;
    case 16:
      return answer == flipper1_answer16;
    case 17:
      return answer == flipper1_answer17;
    case 18:
      return answer == flipper1_answer18;
    case 19:
      return answer == flipper1_answer19;
    case 20:
      return answer == flipper1_answer20;
    default:
      return 0; // invalid question number
  }
}

// judge the answer of flipper2; return 1 if correct, 0 if wrong
int judgeAnswer2(int questionNum, int sw) {
  int answer;
  switch (sw) {
    case 1:
      answer = 1;
      break;
    case 2:
      answer = 2;
      break;
    case 3:
      answer = 3;
      break;
    default:
      return 0; // invalid switch
  }

  switch (questionNum) {
    case 1:
      return answer == flipper2_answer1;
    case 2:
      return answer == flipper2_answer2;
    case 3:
      return answer == flipper2_answer3;
    case 4:
      return answer == flipper2_answer4;
    case 5:
      return answer == flipper2_answer5;
    case 6:
      return answer == flipper2_answer6;
    case 7:
      return answer == flipper2_answer7;
    case 8:
      return answer == flipper2_answer8;
    case 9:
      return answer == flipper2_answer9;
    case 10:
      return answer == flipper2_answer10;
    case 11:
      return answer == flipper2_answer11;
    case 12:
      return answer == flipper2_answer12;
    case 13:
      return answer == flipper2_answer13;
    case 14:
      return answer == flipper2_answer14;
    case 15:
      return answer == flipper2_answer15;
    case 16:
      return answer == flipper2_answer16;
    case 17:
      return answer == flipper2_answer17;
    case 18:
      return answer == flipper2_answer18;
    case 19:
      return answer == flipper2_answer19;
    case 20:
      return answer == flipper2_answer20;
    default:
      return 0; // invalid question number
  }
}

// judge the answer of flipper3; return 1 if correct, 0 if wrong
int judgeAnswer3(int questionNum, int sw) {
  int answer;
  switch (sw) {
    case 1:
      answer = 1;
      break;
    case 2:
      answer = 2;
      break;
    case 3:
      answer = 3;
      break;
    default:
      return 0; // invalid switch
  }

  switch (questionNum) {
    case 1:
      return answer == flipper3_answer1;
    case 2:
      return answer == flipper3_answer2;
    case 3:
      return answer == flipper3_answer3;
    case 4:
      return answer == flipper3_answer4;
    case 5:
      return answer == flipper3_answer5;
    case 6:
      return answer == flipper3_answer6;
    case 7:
      return answer == flipper3_answer7;
    case 8:
      return answer == flipper3_answer8;
    case 9:
      return answer == flipper3_answer9;
    case 10:
      return answer == flipper3_answer10;
    case 11:
      return answer == flipper3_answer11;
    case 12:
      return answer == flipper3_answer12;
    case 13:
      return answer == flipper3_answer13;
    case 14:
      return answer == flipper3_answer14;
    case 15:
      return answer == flipper3_answer15;
    case 16:
      return answer == flipper3_answer16;
    case 17:
      return answer == flipper3_answer17;
    case 18:
      return answer == flipper3_answer18;
    case 19:
      return answer == flipper3_answer19;
    case 20:
      return answer == flipper3_answer20;
    default:
      return 0; // invalid question number
  }
}

// general judge function; return 1 if correct, 0 if wrong; turn on led if correct, turn on buzzer if wrong
int judgeAnswer(int flipperNumber, int questionNum, int sw) {
  int result;
  switch (flipperNumber) {
    case 1:
      result = judgeAnswer1(questionNum, sw);
      break;
    case 2:
      result = judgeAnswer2(questionNum, sw);
      break;
    case 3:
      result = judgeAnswer3(questionNum, sw);
      break;
    default:
      return 0; // invalid flipper number
  }

  // if (result) {
  //   digitalWrite(ledPin, LOW); // turn on led
  //   digitalWrite(buzzerPin, LOW); // turn off buzzer
  //   delay(1000); // delay for 1 second
  //   digitalWrite(ledPin, HIGH); // turn off led
  // } else {
  //   digitalWrite(buzzerPin, HIGH); // turn on buzzer
  //   digitalWrite(ledPin, HIGH); // turn off led
  //   delay(1000); // delay for 1 second
  //   digitalWrite(buzzerPin, LOW); // turn off buzzer
  // }
  return result;
}