#ifndef SMART_CALC_MAIN_H
#define SMART_CALC_MAIN_H

#endif  // SMART_CALC_MAIN_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR 0
#define OK 1

typedef struct Stack {
  double data;
  int type;
  struct Stack* next;
  int priority;
} Stack;

typedef enum Operation {
  s21_num,
  s21_x,
  s21_open,
  s21_close,
  // бинарные
  s21_plus,
  s21_minus,
  s21_mult,
  s21_div,
  s21_pow,
  s21_mod,
  // унарные
  s21_cos,
  s21_sin,
  s21_tan,
  s21_acos,
  s21_asin,
  s21_atan,
  s21_sqrt,
  s21_log,
  s21_ln,
  s21_un_plus,
  s21_un_minus
} Operations;

typedef enum Priorities {
  unan_oper,
  pow_oper,
  first_binar_oper,   // div mult mod
  second_binar_oper,  // plus minus
  numbers_bracks
} Priorities;

int Check_operation(char* str);
int Check_dots(char* str);
void Push_to_stack(Stack** head, double data, int type, int priority);
void Pop_from_stack(Stack** head);
double Pop_from_stack_for_calculation(Stack** head);
Stack* Reverse_stack(Stack** old_s);
Stack* Parcer(char* str);
Stack* RPN(Stack* str);
double Cal_culating(Stack* rpn);
int Result_func(char* str, double* res_num, double resX);
