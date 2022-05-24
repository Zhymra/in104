#ifndef QLEARNINGMUR_H
#define QLEARNINGMUR_H

#include <stdio.h>
#include <stdlib.h>

double*** Q;
double alpha;
double gamma_temp;
double epsilon;

void init_Q();

void tableau();

double max_Q();


#endif /* QLEARNINGMUR_H */
