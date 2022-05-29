#include "functions.h"
#include "mazeEnv.h"

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
    return(state_row_old%rows);
}
int etage(int state_row_old) {
    return(state_row_old/rows);
}

int state_col_true(int state_col_old) {
    return(state_col_old%cols);
}
int etage4(int state_col_old) {
    return(state_col_old/cols);
}
