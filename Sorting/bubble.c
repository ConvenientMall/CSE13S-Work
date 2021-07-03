#include "bubble.h"

#include "globalvar.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(uint32_t arr[], uint32_t n) {
    for (uint32_t i = 0; i < n - 1; i++) { //loops for the amount n-1
        for (uint32_t ii = 1; ii < n - i; ii++) { //loops for the amount n-2
            if (arr[ii] < arr[ii - 1]) { //comparison for bubble
                uint32_t temp = arr[ii]; //swap
                arr[ii] = arr[ii - 1];
                arr[ii - 1] = temp;
                movesB = movesB + 3; //for counting moves
            }
            comparesB = comparesB + 1; //for counting compares
        }
    }
}
