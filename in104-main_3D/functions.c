#include "functions.h"

double mind(double a, double b){
    return (a>b) ? b : a;
}

int min(int a, int b){
    return (a>b) ? b : a;
}

double maxd(double a, double b){
    return (a>b) ? a : b;
}

int max(int a, int b){
    return (a>b) ? a : b;
}

int state_row_true(int state_row_old) {
    return(state_row_old%12);
}
int etage(int state_row_old) {
    return(state_row_old/12);
}
