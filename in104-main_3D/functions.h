#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <math.h>

extern double mind(double a, double b);

extern int min(int a, int b);

extern double maxd(double a, double b);

extern int max(int a, int b);

int state_row_true(int state_row_old);

int etage(int state_row_old);

#endif
