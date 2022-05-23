#include "functions.h"

int min(int a, int b){
    return (a>b) ? b : a;
}

int max(int a, int b){
    return (a>b) ? a : b;
}

/*une fonction de max utilisable pour des doubles*/
double maxd(double a, double b){
    return (a>b) ? a : b;
}

