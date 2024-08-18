#include <stdio.h>

double execute(double args[], int num_args) {
    double result = 0;
    for (int i = 0; i < num_args; i++) {
        result += args[i];
    }
    return result;
}