#include "mathlib.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-10
//exponential function
double Exp(double x) {
    double term = 1, sum = 1;
    for (int k = 1; fabsl(term) > 1e-20; k += 1) {
        term *= x / k;
        sum += term;
    }
    return sum;
}
//factorial function
int factorial(int x) {
    int fac = 1;
    for (int i = 1; i <= x; ++i) {
        fac *= i;
    }
    return fac;
}
//power function
double power(double x, double n) {
    double powered = 1;
    for (int i = 0; i < n; ++i) {
        powered *= x;
    }
    return powered;
}

//sqrt function
long double Sqrt(long double x) {
    long double new = 1.0;
    long double old = 0.0;
    while (fabsl(new - old) > 1e-20) {
        old = new;
        new = 0.5 * (new + x / new);
    }
    return new;
}

//uses newton's method to calculate arcSin
double arcSin(double x) {
    double k = 0;
    double kPlus = 0;
    do {
        k = kPlus;
        kPlus = k - ((sin(k) - x) / cos(k));
    } while (fabsl(k - kPlus) > EPSILON);
    return kPlus;
}
//arcCos
double arcCos(double x) {
    double solu = M_PI / 2 - arcSin(x);
    return solu;
}
//arcTan
double arcTan(double x) {
    double solu = arcSin(x / Sqrt(power(x, 2) + 1));
    return solu;
}
//Uses newton's method to caculate Log
double Log(double x) {
    double k = 1;
    double kPlus = 1;
    do {
        k = kPlus;
        kPlus = k + ((x - Exp(k)) / Exp(k));
    } while (fabsl(k - kPlus) > EPSILON && (kPlus != 0));
    return kPlus;
}
