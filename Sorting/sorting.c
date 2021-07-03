#include "bubble.h"
#include "globalvar.h"
#include "queue.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stack.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "absqQr:n:p:"
typedef enum OP {
    BUBBLE,
    SHELL,
    QUICKS,
    QUICKQ,
    RSEED,
    NSIZE,
    PELEMENTS,
} OP;
//tests fro bubble
void bubble(int seed, int n, int elements) {
    srand(seed);
    printf("Bubble Sort\n");
    uint32_t arr[n];
    for (int i = 0; i < n; ++i) { // fills array with rand
        arr[i] = rand();
    }
    bubble_sort(arr, n);
    printf("%d elements, %d moves, %d compares\n", elements, movesB, comparesB);
    int formCounter = 0;
    for (int i = 0; i < elements; ++i) {
        if (formCounter == 5) {
            formCounter = 0;
            printf("\n");
        }
        printf("%13d", arr[i]);
        formCounter = formCounter + 1;
    }
    printf("\n");
}
//tests for shell
void shell(int seed, int n, int elements) {
    srand(seed);
    printf("Shell Sort\n");
    uint32_t arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = rand();
    }
    shell_sort(arr, n);
    printf("%d elements, %d moves, %d compares\n", elements, movesS, comparesS);
    int formCounter = 0;
    for (int i = 0; i < elements; ++i) {
        if (formCounter == 5) {
            formCounter = 0;
            printf("\n");
        }
        printf("%13d", arr[i]);
        formCounter = formCounter + 1;
    }
    printf("\n");
}
//tests for quick stack
void quicks(int seed, int n, int elements) {
    srand(n);
    srand(seed);
    printf("Quick Sort (Stack)\n");
    uint32_t arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = rand();
    }
    quick_sort_stack(arr, n);
    printf("%d elements, %d moves, %d compares\n", elements, movesQS, comparesQS);
    printf("Max stack size: %d\n", maxStack);
    int formCounter = 0;
    for (int i = 0; i < elements; ++i) {
        if (formCounter == 5) {
            formCounter = 0;
            printf("\n");
        }
        printf("%13d", arr[i]);
        formCounter = formCounter + 1;
    }
    printf("\n");
}
//tests for quick queue
void quickq(int seed, int n, int elements) {
    srand(seed);
    printf("Quick Sort (queue)\n");
    uint32_t arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = rand();
    }
    quick_sort_queue(arr, n);
    printf("%d elements, %d moves, %d compares\n", elements, movesQQ, comparesQQ);
    printf("Max stack size: %d\n", maxQueue);
    int formCounter = 0;
    for (int i = 0; i < elements; ++i) {
        if (formCounter == 5) {
            formCounter = 0;
            printf("\n");
        }
        printf("%13d", arr[i]);
        formCounter = formCounter + 1;
    }
    printf("\n");
}
//prints what happens when not enough conditions are met to do search
void failure(void) {
    printf("SYNOPSIS\n");
    printf("   A collection of comparison-based sorting algorithms.\n");
    printf("\n");
    printf("USAGE\n");
    printf("   ./sorting [-absqQ] [-n length] [-p elements] [-r seed]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("   -a              Enable all sorts.\n");
    printf("   -b              Enable Bubble Sort.\n");
    printf("   -s              Enable Shell Sort.\n");
    printf("   -q              Enable Quick Sort (Stack).\n");
    printf("   -Q              Enable Quick Sort (Queue).\n");
    printf("   -n length       Specify number of array elements.\n");
    printf("   -p elements     Specify number of elements to print.\n");
    printf("   -r seed         Specify random seed.\n");
}
const char *names[] = { "bubble", "shell", "quicks", "quickq", "rseed", "nsize", "pelements" };

int main(int argc, char **argv) {
    Set options = set_empty();
    bool det = false;
    int opt = 0;
    int seed = 13371453;
    int num = 100;
    int elements = 100;
    void (*sort_func[4])(int seed, int n, int elements) = { bubble, shell, quicks, quickq };
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            options = set_insert(options, BUBBLE);
            options = set_insert(options, SHELL);
            options = set_insert(options, QUICKS);
            options = set_insert(options, QUICKQ);
            break;
        case 'b': options = set_insert(options, BUBBLE); break;
        case 's': options = set_insert(options, SHELL); break;
        case 'q': options = set_insert(options, QUICKS); break;
        case 'Q': options = set_insert(options, QUICKQ); break;
        case 'r': //rand
            seed = (atoi(optarg));
            if (atoi(optarg) == 0) {
                printf("./sorting: option requires an argument -- 'r'\n");
                failure();
                det = true;
                return 0;
            }
            break;
        case 'n': //number of rands
            num = (atoi(optarg));
            if (atoi(optarg) == 0) {
                printf("./sorting: option requires an argument -- 'n'\n");
                failure();
                det = true;
                return 0;
            }

            break;
        case 'p': //number of elements printed
            elements = (atoi(optarg));
            if (atoi(optarg) == 0) {
                printf("./sorting: option requires an argument -- 'p'\n");
                failure();
                det = true;
                return 0;
            }
            break;
        default: break;
        }
    }
    for (OP i = BUBBLE; i <= QUICKQ; i += 1) {
        if (set_member(options, i)) {
            det = true;
            if (elements > num) {
                elements = num;
            }
            sort_func[i](seed, num, elements);
        }
    }
    if (det == false) {
        failure();
    }
    return 0;
}
