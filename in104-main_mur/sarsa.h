#ifndef SARSA_H
#define SARSA_H

#include <stdio.h>
#include <stdlib.h>

double*** Q;


void init_Q();

void tableau();

double max_Q();

action epsi_greed();


#endif /* SARSA_H */
