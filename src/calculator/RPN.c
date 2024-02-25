#include "RPN.h"

int Check_operation(char* str) {
  int correct = OK;
  int brack_fl = 0;
  int len = (int)strlen(str);
  for (int i = 0; i < len && correct == OK; i++) {
    // проверка скобок
    if (str[i] == '(') {
      if (i + 1 != len && str[i + 1] == ')') correct = ERROR;
      brack_fl += 1;
    } else if (str[i] == ')') {
      if (brack_fl == 0) {
        correct = ERROR;
      } else
        brack_fl -= 1;
      if (str[i + 1] == 'X' || isdigit(str[i + 1])) correct = ERROR;
    }
    // проверка функций
    // mult div pow mod
    else if (str[i] == '/' || str[i] == '*' || str[i] == '^' || str[i] == '%') {
      if (i == 0 || i == len - 1)
        correct = ERROR;
      else {
        if (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '^' ||
            str[i + 1] == '-' || str[i + 1] == '+' || str[i + 1] == ')' ||
            str[i + 1] == '%')
          correct = ERROR;
        if (str[i - 1] == '*' || str[i - 1] == '/' || str[i - 1] == '^' ||
            str[i - 1] == '-' || str[i - 1] == '+' || str[i - 1] == '(' ||
            str[i - 1] == '%')
          correct = ERROR;
      }
    }
    // plus minus
    else if (str[i] == '-' || str[i] == '+') {
      if (i == len - 1)
        correct = ERROR;
      else if (i != 0) {
        if (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '^' ||
            str[i + 1] == '-' || str[i + 1] == '+' || str[i + 1] == ')' ||
            str[i + 1] == '%')
          correct = ERROR;
        if (str[i - 1] == '*' || str[i - 1] == '/' || str[i - 1] == '^' ||
            str[i - 1] == '-' || str[i - 1] == '+' || str[i - 1] == '%')
          correct = ERROR;
      }
    }
    // cos sin tan log
    else if (str[i] == 'c' || (str[i] == 's' && str[i + 2] == 'n') ||
             str[i] == 't' || (str[i] == 'l' && str[i + 2] == 'g')) {
      // if(i + 4 == ')') correct = ERROR;
      if (i != 0 &&
          (str[i - 1] == ')' || isdigit(str[i - 1]) || str[i - 1] == 'X'))
        correct = ERROR;
      i += 2;
    }
    // asin atan acos sqrt
    else if (str[i] == 'a' || (str[i] == 's' && str[i + 3] == 't')) {
      if (i + 7 == ')') correct = ERROR;
      if (i != 0 &&
          (str[i - 1] == ')' || isdigit(str[i - 1]) || str[i - 1] == 'X'))
        correct = ERROR;
      i += 3;
    }
    // ln
    else if (str[i] == 'l' && str[i + 1] == 'n') {
      if (i + 3 == ')') correct = ERROR;
      if (i != 0 &&
          (str[i - 1] == ')' || isdigit(str[i - 1]) || str[i - 1] == 'X'))
        correct = ERROR;
      i++;
    } else if (isdigit((str[i])) && (str[i + 1] == '(' || (str[i + 1] == 'X')))
      correct = ERROR;
    else if (str[i] == 'X' && (str[i + 1] == '(' || isdigit(str[i + 1])))
      correct = ERROR;
    else if ((str[i] == 'i' && str[i + 1] == 'n') ||
             (str[i] == 'n' && str[i + 1] == 'a') ||
             (str[i] == 'E' && str[i + 1] == 'R'))
      correct = ERROR;
  }
  if (brack_fl != 0) correct = ERROR;
  return correct;
}

int Check_dots(char* str) {
  int correctStr = OK;
  int strLength = (int)strlen(str);
  for (int i = 0; i < strLength && correctStr == OK; i++) {
    int dotsCount = 0;
    if ((str[i] >= '0' && str[i] <= '9')) {
      while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
        if (str[i] == '.') dotsCount++;
        i++;  // двигаем цикл while
      }
      i--;  // цикл закончился не на цифре, поэтому двинем на 1 назад чтоб сам
            // цикл for сделал перемещение указателя
    }
    if (dotsCount > 1) correctStr = ERROR;
    if (str[i] == '.') correctStr = ERROR;
  }
  return correctStr;
}

void Push_to_stack(Stack** head, double data, int type, int priority) {
  Stack* new_node = malloc(sizeof(Stack));
  if (new_node != NULL) {
    new_node->data = data;
    new_node->type = type;
    new_node->priority = priority;
    new_node->next = *head;
    *head = new_node;
  }
}

void Pop_from_stack(Stack** head) {
  Stack* dop = *head;
  *head = dop->next;
  free(dop);
}

double Pop_from_stack_for_calculation(Stack** head) {
  double ret = (*head)->data;
  Stack* dop = *head;
  *head = dop->next;
  free(dop);
  return ret;
}

Stack* Reverse_stack(Stack** old_s) {
  Stack* new_s = NULL;
  while (*old_s != NULL) {
    Push_to_stack(&new_s, (*old_s)->data, (*old_s)->type, (*old_s)->priority);
    Pop_from_stack(old_s);
  }
  if (*old_s) Pop_from_stack(old_s);
  return new_s;
}

Stack* Parcer(char* str) {
  Stack* head = NULL;
  int i = 0;
  int len = (int)strlen(str);
  while (i < len) {
    // numbers
    if (isdigit(str[i])) {
      char dop_str[256];
      for (int i = 0; i < 256; i++) dop_str[i] = '\0';
      int counter = 0;
      while (isdigit(str[i]) || str[i] == '.') {
        dop_str[counter] = str[i];
        counter++;
        i++;
      }
      i--;
      Push_to_stack(&head, atof(dop_str), s21_num, numbers_bracks);
    } else if (str[i] == 'X')
      Push_to_stack(&head, 0, s21_x, numbers_bracks);
    // bracks
    else if (str[i] == '(')
      Push_to_stack(&head, 0, s21_open, numbers_bracks);
    else if (str[i] == ')')
      Push_to_stack(&head, 0, s21_close, numbers_bracks);
    // mod
    else if (str[i] == '^')
      Push_to_stack(&head, 0, s21_pow, pow_oper);
    // div mult mod
    else if (str[i] == '*')
      Push_to_stack(&head, 0, s21_mult, first_binar_oper);
    else if (str[i] == '/')
      Push_to_stack(&head, 0, s21_div, first_binar_oper);
    else if (str[i] == '%')
      Push_to_stack(&head, 0, s21_mod, first_binar_oper);
    // minus plus
    else if (str[i] == '+' || str[i] == '-') {
      if (i == 0 || str[i - 1] == '(')
        Push_to_stack(&head, 0, s21_num, numbers_bracks);
      if (str[i] == '+') Push_to_stack(&head, 0, s21_plus, second_binar_oper);
      if (str[i] == '-') Push_to_stack(&head, 0, s21_minus, second_binar_oper);
    }
    // asin atan acos sqrt
    else if (str[i] == 'a' || (str[i] == 's' && str[i + 3] == 't')) {
      if (str[i] == 'a' && str[i + 1] == 'c')
        Push_to_stack(&head, 0, s21_acos, unan_oper);
      else if (str[i] == 'a' && str[i + 1] == 's')
        Push_to_stack(&head, 0, s21_asin, unan_oper);
      else if (str[i] == 'a' && str[i + 1] == 't')
        Push_to_stack(&head, 0, s21_atan, unan_oper);
      else if (str[i] == 's' && str[i + 1] == 'q')
        Push_to_stack(&head, 0, s21_sqrt, unan_oper);
      i += 3;
    }
    // cos sin tan log
    else if (str[i] == 'c' || (str[i] == 's' && str[i + 2] == 'n') ||
             str[i] == 't' || (str[i] == 'l' && str[i + 2] == 'g')) {
      if (str[i] == 'c')
        Push_to_stack(&head, 0, s21_cos, unan_oper);
      else if (str[i] == 's')
        Push_to_stack(&head, 0, s21_sin, unan_oper);
      else if (str[i] == 't')
        Push_to_stack(&head, 0, s21_tan, unan_oper);
      else if (str[i] == 'l')
        Push_to_stack(&head, 0, s21_log, unan_oper);
      i += 2;
    }
    // ln
    else if (str[i] == 'l' && str[i + 1] == 'n') {
      Push_to_stack(&head, 0, s21_ln, unan_oper);
      i++;
    }
    i++;
  }
  head = Reverse_stack(&head);
  return (head);
}

Stack* RPN(Stack* str) {
  Stack* rpn = NULL;
  Stack* operations = NULL;
  Stack* curr = str;
  int priora = 10;
  while (curr != NULL) {
    if (curr->type == s21_num || curr->type == s21_x) {
      Push_to_stack(&rpn, curr->data, curr->type, curr->priority);
      Pop_from_stack(&str);
    } else if (curr->priority < priora || curr->type == s21_open ||
               curr->type == s21_pow) {
      Push_to_stack(&operations, curr->data, curr->type, curr->priority);
      Pop_from_stack(&str);
      priora = curr->priority;
    } else if (curr->type == s21_close || curr->priority >= priora) {
      if (curr->type == s21_close) {
        while (operations != NULL && operations->type != s21_open) {
          Push_to_stack(&rpn, operations->data, operations->type,
                        operations->priority);
          Pop_from_stack(&operations);
        }
        Pop_from_stack(&operations);
        if (operations) priora = operations->priority;
      } else {
        while (operations != NULL && operations->priority <= curr->priority) {
          Push_to_stack(&rpn, operations->data, operations->type,
                        operations->priority);
          Pop_from_stack(&operations);
        }
        priora = curr->priority;
        Push_to_stack(&operations, curr->data, curr->type, curr->priority);
      }
    }
    curr = curr->next;
  }
  while (str != NULL) Pop_from_stack(&str);
  curr = operations;
  while (curr != NULL) {
    Push_to_stack(&rpn, operations->data, operations->type,
                  operations->priority);
    curr = curr->next;
    Pop_from_stack(&operations);
  }
  return rpn;
}

double Cal_culating(Stack* rpn) {
  Stack* curr = rpn;
  Stack* result = NULL;
  while (curr != NULL) {
    if (curr->type == s21_num || curr->type == s21_x)
      Push_to_stack(&result, curr->data, curr->type, curr->priority);
    else if (curr->type >= s21_plus && curr->type <= s21_mod) {
      double var_1, var_2;
      if (result)
        var_1 = Pop_from_stack_for_calculation(&result);
      else
        break;
      if (result)
        var_2 = Pop_from_stack_for_calculation(&result);
      else
        break;
      if (curr->type == s21_plus)
        Push_to_stack(&result, var_2 + var_1, curr->type, curr->priority);
      else if (curr->type == s21_minus)
        Push_to_stack(&result, var_2 - var_1, curr->type, curr->priority);
      else if (curr->type == s21_mult)
        Push_to_stack(&result, var_2 * var_1, curr->type, curr->priority);
      else if (curr->type == s21_div)
        Push_to_stack(&result, var_2 / var_1, curr->type, curr->priority);
      else if (curr->type == s21_mod)
        Push_to_stack(&result, fmod(var_2, var_1), curr->type, curr->priority);
      else if (curr->type == s21_pow)
        Push_to_stack(&result, pow(var_2, var_1), curr->type, curr->priority);
    } else {
      double var;
      if (result)
        var = Pop_from_stack_for_calculation(&result);
      else
        break;
      if (curr->type == s21_cos)
        Push_to_stack(&result, cos(var), curr->type, curr->priority);
      else if (curr->type == s21_sin)
        Push_to_stack(&result, sin(var), curr->type, curr->priority);
      else if (curr->type == s21_tan)
        Push_to_stack(&result, tan(var), curr->type, curr->priority);
      else if (curr->type == s21_log)
        Push_to_stack(&result, log10(var), curr->type, curr->priority);
      else if (curr->type == s21_ln)
        Push_to_stack(&result, log(var), curr->type, curr->priority);
      else if (curr->type == s21_acos)
        Push_to_stack(&result, acos(var), curr->type, curr->priority);
      else if (curr->type == s21_atan)
        Push_to_stack(&result, atan(var), curr->type, curr->priority);
      else if (curr->type == s21_asin)
        Push_to_stack(&result, asin(var), curr->type, curr->priority);
      else if (curr->type == s21_sqrt)
        Push_to_stack(&result, sqrt(var), curr->type, curr->priority);
    }
    curr = curr->next;
  }
  double ret = result->data;
  while (result != NULL) Pop_from_stack(&result);
  return (ret);
}

int Result_func(char* str, double* res_num, double resX) {
  int error = 0;
  if (Check_dots(str) && Check_operation(str)) {
    Stack* rpn = Parcer(str);
    Stack* rpn_2 = RPN(rpn);
    rpn_2 = Reverse_stack(&rpn_2);
    Stack* curr = rpn_2;
    while (curr != NULL) {
      if (curr->type == s21_x) {
        curr->type = s21_num;
        curr->data = resX;
      }
      curr = curr->next;
    }
    *res_num = Cal_culating(rpn_2);
    while (rpn_2 != NULL) Pop_from_stack(&rpn_2);
  } else
    error = 1;
  return error;
}
