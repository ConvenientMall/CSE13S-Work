#include "shell.h"

#include "gaps.h"
#include "globalvar.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//got sort from asgn pdf
void shell_sort(uint32_t arr[], uint32_t n) {
    for (int i = 0; i < 102; ++i) { //goes through all the gaps
        for (uint32_t ii = gaps[i]; ii < n; ++ii) {
            uint32_t j = ii;
            uint32_t temp = arr[ii];
            movesS = movesS + 1;
            comparesS = comparesS + 1;
            while (j >= gaps[i] && temp < arr[j - gaps[i]]) {
                arr[j] = arr[j - gaps[i]];
                j -= gaps[i];
                movesS = movesS + 1;
            }
            arr[j] = temp;
            movesS = movesS + 1;
        }
    }
}
