#ifndef QUIZ_H
#define QUIZ_H

#include <cstdint>

// testing
#define cleanUpQuizData()
#define getTotalQuestions(id) (2)
#define getQuizNameList(id) {"Testing 1", "Testing 2", "Testing 3", "Testing 4", "Testing 5", "Testing 6"}

uint8_t getQuizQuestionContent(int quizId, int questionId, char *&questionText, char *options[4]);

#endif
