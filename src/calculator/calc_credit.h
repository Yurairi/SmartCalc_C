#ifndef SMART_CALC_CREDIT_H
#define SMART_CALC_CREDIT_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double annuityСredit(double *sums, double *months, double *procents,
                     double *overpayment, double *totalSum);
double differentiatedСredit(double *sums, double *months, double *procents,
                            double *d);

#endif  // SMART_CALC_CREDIT_H
