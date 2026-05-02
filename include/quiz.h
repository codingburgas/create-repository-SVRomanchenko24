#ifndef QUIZ_H
#define QUIZ_H

#include <cstdint>

// testing
#define getQuizName(id) "Testing"
#define cleanUpQuizData()
#define getTotalQuestions(id) (2)
#define getQuizNameList(id) {"Testing 1", "Testing 2", "Testing 3"}

uint8_t getQuizQuestionContent(int quizId, int questionId, char *&questionText, char *options[4]);

#endif
