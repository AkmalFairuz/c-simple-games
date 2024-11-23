#ifndef CSG_MATH_QUIZ_H
#define CSG_MATH_QUIZ_H

#include "csg.h"

enum Operation { increment, decrement, multiply, divide };
static enum Operation get_random_operation(int mode);
static char get_operation_symbol(enum Operation operation);
static double evaluate_complex_expression(int numbers[], enum Operation operations[], int count);
static int generate_question(int min, int max, int *question_number, int max_operations);
static int game_math();

csg_game_result csg_math_quiz_start(void);

#endif
