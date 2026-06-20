# RevisionProblemsFlipper
A project based on ESP32 (wroom32). It's a flipper, and you can review by answering questions on it.
## Basic functions
### Answer "hardcoded" questions.
- By pressing SW1, SW2, SW3 (A, B, C), the program will compare your answer with the correct answer written in "answer_judger.h".
- If the answer is right, the waterfall light will be on and you get a score. Otherwise, the buzzer will be on. Then the flipper turns to the next page.
- The OLED shows the current question. After answering all questions (in a set), OLED will tell you the final score.
- To change the questions, you can only make other boards and change correct answers accordingly. That's why I call it "hardcoded".

### Switch question set
- By pressing SW4 solely, the question set will change among 1 - 2 - 3 - 1 circularly. Actually, it means controlling another flipper. The project support up to 3 flippers.

### Reset to original position (semi-automatic)
- Remember to press SW3 and SW4 together (the maximum interval is 100ms) before cutting the power so that the postion information is saved.
- If you have controlled multiple flippers, save respectively.
- All flippers will reset to question 1 when the power is on (if you saved the positions before).

## To be improved
- For some reasons, the typeC charging port is very unstable. Chances are that your power is off unintendedly before you could save the positions. I design the reset function to be semi-automatically to reduce flash changing frequency. But for user experience, maybe saving every time it moves is better (full-automatic).
- Despite my effort, the project is still somewhat hardcoded. Some logics are still constrained to some specific situations.
