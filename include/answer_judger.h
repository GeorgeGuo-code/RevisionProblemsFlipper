#ifndef ANSWER_JUDGER_H
#define ANSWER_JUDGER_H

#ifdef __cplusplus
extern "C" {
#endif
int judgeAnswer1(int questionNumber, int answer);
int judgeAnswer2(int questionNumber, int answer);
int judgeAnswer3(int questionNumber, int answer);
int judgeAnswer(int flipperNumber, int questionNumber, int answer);
#ifdef __cplusplus
}
#endif

#endif // ANSWER_JUDGER_H