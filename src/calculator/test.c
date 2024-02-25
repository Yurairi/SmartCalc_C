//
// Created by Oznak Banshee on 4/20/23.
//

#include <check.h>

#include "RPN.h"
#define ACCURACY 1e-7
#define OKK 0
#define ERO 1

START_TEST(s21_simple_calc1) {
  double result = 0.0;
  char input_string[256] = "5+3+2+5+5+1+2+3+4+5+6+7+8+9";
  int check = OKK;
  check = Result_func(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 65, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc2) {
  double result = 0.0;
  char input_string[256] = "5-3-2-5-5-1-2-3-4-5-6-7-8-9";
  int check = OKK;
  check = Result_func(input_string, &result, 0);
  ck_assert_double_eq_tol(result, -55, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc3) {
  double result = 0.0;
  char input_string[256] = "5143*1213*24532/1213/1445";
  int check = OKK;
  check = Result_func(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 87313.5474048, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc4) {
  double result = 0.0;
  char input_string[256] = "12345679*9";
  int check = OKK;
  check = Result_func(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 111111111, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc5) {
  double result = 0.0;
  char input_string[256] =
      "1.23456789+2.34567890-3.45678901*4.56789012/5.67890123";
  int check = OKK;
  check = Result_func(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 0.79973842646, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc6) {
  double result = 0.0;
  char input_string[256] = "5";
  int check = OKK;
  check = Result_func(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 5, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc7) {
  double result = 0.0;
  char input_string[256] = "2^3^2";
  int check = OKK;
  check = Result_func(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 512, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc8) {
  double result = 0.0;
  char input_string[256] = "5*X";
  int check = OKK;
  check = Result_func(input_string, &result, 6);
  ck_assert_double_eq_tol(result, 30, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc9) {
  double result = 0.0;
  char input_string[256] = "2^X^X";
  int check = OKK;
  check = Result_func(input_string, &result, 3);
  ck_assert_double_eq_tol(result, 134217728, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_simple_calc10) {
  double result = 0.0;
  char input_string[256] = "2+X/X-X*(X%X)";
  int check = OKK;
  check = Result_func(input_string, &result, 3);
  ck_assert_double_eq_tol(result, 3, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

Suite *s21_simple_calc(void) {
  Suite *s = suite_create("\033[46m-=s21_simple_calc=-\033[0m");
  TCase *tc = tcase_create("calc_tc");
  tcase_add_test(tc, s21_simple_calc1);
  tcase_add_test(tc, s21_simple_calc2);
  tcase_add_test(tc, s21_simple_calc3);
  tcase_add_test(tc, s21_simple_calc4);
  tcase_add_test(tc, s21_simple_calc5);
  tcase_add_test(tc, s21_simple_calc6);
  tcase_add_test(tc, s21_simple_calc7);
  tcase_add_test(tc, s21_simple_calc8);
  tcase_add_test(tc, s21_simple_calc9);
  tcase_add_test(tc, s21_simple_calc10);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_hard_calc1) {
  double result = 0.0;
  char input_string[256] =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  int check = OKK;
  check = Result_func(input_string, &result, 0);
  ck_assert_double_eq_tol(result, -30.0721649, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_hard_calc2) {
  double result = 0.0;
  char input_string[256] = "cos(2-sin(3+0.26*7+1))";
  int check = OKK;
  check = Result_func(input_string, &result, 0);
  ck_assert_double_eq_tol(result, -0.7681865, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_hard_calc3) {
  double result = 0.0;
  char input_string[256] = "10*(-5+log(2+(9/3)))";
  int check = OKK;
  check = Result_func(input_string, &result, 0);
  ck_assert_double_eq_tol(result, -43.0102999, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_hard_calc4) {
  double result = 0.0;
  char input_string[256] = "-ln(tan(sqrt(50-1)))";
  int check = OKK;
  check = Result_func(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 0.1375991, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_hard_calc6) {
  double result = 0.0;
  char input_string[256] = "sin(sin(sin(sin(sin(90)))))";
  int check = OKK;
  check = Result_func(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 0.6023926, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

START_TEST(s21_hard_calc7) {
  double result = 0.0;
  char input_string[256] = "-(3)*(-3.141592-(7*(-(-(-(-7))))))";
  int check = OKK;
  check = Result_func(input_string, &result, 0);
  ck_assert_double_eq_tol(result, 156.424776, ACCURACY);
  ck_assert_int_eq(check, OKK);
}

Suite *s21_hard_calc(void) {
  Suite *s = suite_create("\033[46m-=s21_hard_calc=-\033[0m");
  TCase *tc = tcase_create("calc_tc");
  tcase_add_test(tc, s21_hard_calc1);
  tcase_add_test(tc, s21_hard_calc2);
  tcase_add_test(tc, s21_hard_calc3);
  tcase_add_test(tc, s21_hard_calc4);
  tcase_add_test(tc, s21_hard_calc6);
  tcase_add_test(tc, s21_hard_calc7);
  suite_add_tcase(s, tc);
  return s;
}

// START_TEST(s21_ERO_calc1) {
//   double result = 0.0;
//   char input_string[256] = "";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc2) {
//   double result = 0.0;
//   char input_string[256] = {0};
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc3) {
//   double result = 0.0;
//   char input_string[256] = "5+(3";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc4) {
//   double result = 0.0;
//   char input_string[256] = "5)+3";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc5) {
//   double result = 0.0;
//   char input_string[256] = "1+()2";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc6) {
//   double result = 0.0;
//   char input_string[256] = "1+(+-2)";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc7) {
//   double result = 0.0;
//   char input_string[256] = "*";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc8) {
//   double result = 0.0;
//   char input_string[256] = "(^)";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc9) {
//   double result = 0.0;
//   char input_string[256] = ")2+3(";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc10) {
//   double result = 0.0;
//   char input_string[256] = "2..3";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc11) {
//   double result = 0.0;
//   char input_string[256] = "7.1*2.3.2";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc12) {
//   double result = 0.0;
//   char input_string[256] = "5+.2";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc13) {
//   double result = 0.0;
//   char input_string[256] = "5+1.";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc14) {
//   double result = 0.0;
//   char input_string[256] = "asin()";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc15) {
//   double result = 0.0;
//   char input_string[256] = "%3";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc16) {
//   double result = 0.0;
//   char input_string[256] = "0123";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc17) {
//   double result = 0.0;
//   char input_string[256] = "000.2";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc18) {
//   double result = 0.0;
//   char input_string[256] = "cos(*tan(2))";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc19) {
//   double result = 0.0;
//   char input_string[256] = "1%";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc20) {
//   double result = 0.0;
//   char input_string[256] = "1%(sin())";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc21) {
//   double result = 0.0;
//   char input_string[256] = "5x";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc22) {
//   double result = 0.0;
//   char input_string[256] = "xxxx";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc23) {
//   double result = 0.0;
//   char input_string[256] = "xsin(3)";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc24) {
//   double result = 0.0;
//   char input_string[256] = "x.";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// START_TEST(s21_ERO_calc25) {
//   double result = 0.0;
//   char input_string[256] = "%x";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, ERO);
// }

// Suite *s21_ERO_calc(void) {
//   Suite *s = suite_create("\033[46m-=s21_ERO_calc=-\033[0m");
//   TCase *tc = tcase_create("calc_tc");
//   tcase_add_test(tc, s21_ERO_calc1);
//   tcase_add_test(tc, s21_ERO_calc2);
//   tcase_add_test(tc, s21_ERO_calc3);
//   tcase_add_test(tc, s21_ERO_calc4);
//   tcase_add_test(tc, s21_ERO_calc5);
//   tcase_add_test(tc, s21_ERO_calc6);
//   tcase_add_test(tc, s21_ERO_calc7);
//   tcase_add_test(tc, s21_ERO_calc8);
//   tcase_add_test(tc, s21_ERO_calc9);
//   tcase_add_test(tc, s21_ERO_calc10);
//   tcase_add_test(tc, s21_ERO_calc11);
//   tcase_add_test(tc, s21_ERO_calc12);
//   tcase_add_test(tc, s21_ERO_calc13);
//   tcase_add_test(tc, s21_ERO_calc14);
//   tcase_add_test(tc, s21_ERO_calc15);
//   tcase_add_test(tc, s21_ERO_calc16);
//   tcase_add_test(tc, s21_ERO_calc17);
//   tcase_add_test(tc, s21_ERO_calc18);
//   tcase_add_test(tc, s21_ERO_calc19);
//   tcase_add_test(tc, s21_ERO_calc20);
//   tcase_add_test(tc, s21_ERO_calc21);
//   tcase_add_test(tc, s21_ERO_calc22);
//   tcase_add_test(tc, s21_ERO_calc23);
//   tcase_add_test(tc, s21_ERO_calc24);
//   tcase_add_test(tc, s21_ERO_calc25);
//   suite_add_tcase(s, tc);
//   return s;
// }

// START_TEST(s21_1_inf_calc1) {
//   double result = 0.0;
//   char input_string[256] = "1/0";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, 1);
// }

// START_TEST(s21_1_inf_calc2) {
//   double result = 0.0;
//   char input_string[256] = "sqrt(-3)";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, 1);
// }

// START_TEST(s21_1_inf_calc3) {
//   double result = 0.0;
//   char input_string[256] = "acos(-5)";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, 1);
// }

// START_TEST(s21_1_inf_calc4) {
//   double result = 0.0;
//   char input_string[256] = "asin(1153.21)";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, 1);
// }

// START_TEST(s21_1_inf_calc5) {
//   double result = 0.0;
//   char input_string[256] = "6/sqrt(-9)";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, 1);
// }

// START_TEST(s21_1_inf_calc6) {
//   double result = 0.0;
//   char input_string[256] = "2/x";
//   int check = OKK;
//   check = Result_func(input_string, &result, 0);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, 1);
// }

// START_TEST(s21_1_inf_calc7) {
//   double result = 0.0;
//   char input_string[256] = "asin(x)";
//   int check = OKK;
//   check = Result_func(input_string, &result, 20);
//   ck_assert_double_eq_tol(result, 0, ACCURACY);
//   ck_assert_int_eq(check, 1);
// }

// Suite *s21_1_inf_calc(void) {
//   Suite *s = suite_create("\033[46m-=s21_1_inf_calc=-\033[0m");
//   TCase *tc = tcase_create("calc_tc");
//   tcase_add_test(tc, s21_1_inf_calc1);
//   tcase_add_test(tc, s21_1_inf_calc2);
//   tcase_add_test(tc, s21_1_inf_calc3);
//   tcase_add_test(tc, s21_1_inf_calc4);
//   tcase_add_test(tc, s21_1_inf_calc5);
//   tcase_add_test(tc, s21_1_inf_calc6);
//   tcase_add_test(tc, s21_1_inf_calc7);
//   suite_add_tcase(s, tc);
//   return s;
// }

// START_TEST(s21_credit_calc1) {
//   double total_amount = 30000;
//   int term = 10;
//   double percents = 14;
//   double monthly_pay = 0;
//   double first_pay = 0;
//   double overpay = 0;
//   double total_pay = 0;
//   credit(&total_amount, term, percents, &monthly_pay, &first_pay, &overpay,
//          &total_pay, 1);
//   ck_assert_double_eq_tol(monthly_pay, 3195.85, 0.01);
//   ck_assert_double_eq_tol(overpay, 1958.5, 0.1);
//   ck_assert_double_eq_tol(total_pay, 31958.5, 0.1);
// }

// START_TEST(s21_credit_calc2) {
//   double total_amount = 30000;
//   int term = 10;
//   double percents = 14;
//   double monthly_pay = 0;
//   double first_pay = 0;
//   double overpay = 0;
//   double total_pay = 0;
//   credit(&total_amount, term, percents, &monthly_pay, &first_pay, &overpay,
//          &total_pay, 0);
//   ck_assert_double_eq_tol(first_pay, 3350.00, 0.01);
//   ck_assert_double_eq_tol(monthly_pay, 3035.00, 0.01);
//   ck_assert_double_eq_tol(overpay, 1925.00, 0.1);
//   ck_assert_double_eq_tol(total_pay, 31925.00, 0.1);
// }

// START_TEST(s21_credit_calc3) {
//   double total_amount = 123456;
//   int term = 300;
//   double percents = 5;
//   double monthly_pay = 0;
//   double first_pay = 0;
//   double overpay = 0;
//   double total_pay = 0;
//   credit(&total_amount, term, percents, &monthly_pay, &first_pay, &overpay,
//          &total_pay, 1);
//   ck_assert_double_eq_tol(monthly_pay, 721.71, 0.01);
//   ck_assert_double_eq_tol(overpay, 93057, 0.5);
//   ck_assert_double_eq_tol(total_pay, 216513, 0.5);
// }

// START_TEST(s21_credit_calc4) {
//   double total_amount = 123456;
//   int term = 300;
//   double percents = 5;
//   double monthly_pay = 0;
//   double first_pay = 0;
//   double overpay = 0;
//   double total_pay = 0;
//   credit(&total_amount, term, percents, &monthly_pay, &first_pay, &overpay,
//          &total_pay, 0);
//   ck_assert_double_eq_tol(first_pay, 925.92, 0.01);
//   ck_assert_double_eq_tol(monthly_pay, 413.23, 0.01);
//   ck_assert_double_eq_tol(overpay, 77417.20, 0.1);
//   ck_assert_double_eq_tol(total_pay, 200873.20, 0.1);
// }

// START_TEST(s21_credit_calc5) {
//   double total_amount = 1400;
//   int term = 1;
//   double percents = 40;
//   double monthly_pay = 0;
//   double first_pay = 0;
//   double overpay = 0;
//   double total_pay = 0;
//   credit(&total_amount, term, percents, &monthly_pay, &first_pay, &overpay,
//          &total_pay, 1);
//   ck_assert_double_eq_tol(monthly_pay, 1446.67, 0.01);
//   ck_assert_double_eq_tol(overpay, 46.67, 0.01);
//   ck_assert_double_eq_tol(total_pay, 1446.67, 0.01);
// }

// START_TEST(s21_credit_calc6) {
//   double total_amount = 1400;
//   int term = 1;
//   double percents = 40;
//   double monthly_pay = 0;
//   double first_pay = 0;
//   double overpay = 0;
//   double total_pay = 0;
//   credit(&total_amount, term, percents, &monthly_pay, &first_pay, &overpay,
//          &total_pay, 0);
//   ck_assert_double_eq_tol(first_pay, 1446.67, 0.01);
//   ck_assert_double_eq_tol(monthly_pay, 1446.67, 0.01);
//   ck_assert_double_eq_tol(overpay, 46.67, 0.01);
//   ck_assert_double_eq_tol(total_pay, 1446.67, 0.01);
// }

// Suite *s21_credit_calc(void) {
//   Suite *s = suite_create("\033[46m-=s21_credit_calc=-\033[0m");
//   TCase *tc = tcase_create("calc_tc");
//   tcase_add_test(tc, s21_credit_calc1);
//   tcase_add_test(tc, s21_credit_calc2);
//   tcase_add_test(tc, s21_credit_calc3);
//   tcase_add_test(tc, s21_credit_calc4);
//   tcase_add_test(tc, s21_credit_calc5);
//   tcase_add_test(tc, s21_credit_calc6);
//   suite_add_tcase(s, tc);
//   return s;
// }

int main() {
  int failed = 0;
  Suite *s21_smart_calc_test[] = {s21_simple_calc(), s21_hard_calc(), NULL};

  for (int i = 0; s21_smart_calc_test[i] != NULL; i++) {  // (&& failed == 0)
    SRunner *sr = srunner_create(s21_smart_calc_test[i]);

    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}