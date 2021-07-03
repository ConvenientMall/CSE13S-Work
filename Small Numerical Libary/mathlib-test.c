#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "asctl"
//what is printed for testing arcsin
int arSin(void) {
    printf("  x            arcSin           Libary         Diffrence\n");
    printf("  -            ------           ------         ---------\n");
    for (double i = -1; i < 1; i = i + .1) { //from negative one to one
        printf(
            " % 7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, arcSin(i), asin(i), (arcSin(i) - asin(i)));
    }
    return 0;
}
//what is printed for testing arccos
int arCos(void) {
    printf("  x            arcCos           Libary         Diffrence\n");
    printf("  -            ------           ------         ---------\n");
    for (double i = -1; i < 1; i = i + .1) { //from negative one to one
        printf(
            " % 7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, arcCos(i), acos(i), (arcCos(i) - acos(i)));
    }
    return 0;
}
//what is printed for testing arctan
int arTan(void) {
    double ten = 10;
    printf("  x            arcTan           Libary         Diffrence\n");
    printf("  -            ------           ------         ---------\n");
    for (double i = -1; i < 9.9; i = i + .1) { //from negative one to ten
        printf(
            " % 7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, arcTan(i), atan(i), (arcTan(i) - atan(i)));
    }
    printf("% 7.4lf % 16.8lf % 16.8lf % 16.10lf\n", ten, arcTan(10), atan(10),
        (arcTan(10) - atan(10))); //have to print last here for formatting issues
    return 0;
}
//what is printed for testing log
int arLog(void) {
    double ten = 10;
    printf("  x            Log              Libary         Diffrence\n");
    printf("  -            ---              ------         ---------\n");
    for (double i = 1; i < 9.9; i = i + .1) { //from one to ten
        printf(" % 7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Log(i), log(i), (Log(i) - log(i)));
    }
    printf("% 7.4lf % 16.8lf % 16.8lf % 16.10lf\n", ten, Log(10), log(10),
        (Log(10) - log(10))); //have to print last here for formatting issues
    return 0;
}

int main(int argc, char **argv) {
    int opt = 0;
    int sFlag = 0; // flag for printing arcsin test
    int cFlag = 0; // flag for printing arccos test
    int tFlag = 0; // flag for printing arctan test
    int lFlag = 0; // flag for printing log test
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': //if -a prints all tests
            sFlag = 1;
            cFlag = 1;
            tFlag = 1;
            lFlag = 1;
            break;
        case 's': //if -s prints arcsin test
            sFlag = 1;
            break;
        case 'c': //if -c prints arcos test
            cFlag = 1;
            break;
        case 't': // if -t prints arctan test
            tFlag = 1;
            break;
        case 'l': //if -l prints log test
            lFlag = 1;
            break;
        }
    }
    if (sFlag == 1) {
        arSin();
    }
    if (cFlag == 1) {
        arCos();
    }
    if (tFlag == 1) {
        arTan();
    }
    if (lFlag == 1) {
        arLog();
    }
    if (sFlag == 0 && cFlag == 0 && tFlag == 0
        && lFlag == 0) { //what is printed if no arguments are put in cmd
        printf("Program usage: ./mathlib-test -[asctl]\n");
        printf("  -a   Runs all tests (arcsin, arccos, arctan, log)\n");
        printf("  -s   Runs arcsin tests\n");
        printf("  -c   Runs arccos tests\n");
        printf("  -t   Runs arctan tests\n");
        printf("  -l   Runs log tests\n");
    }
    return 0;
}
