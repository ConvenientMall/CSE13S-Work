#include "quick.h"

#include "globalvar.h"
#include "queue.h"
#include "stack.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//got from pdf
int64_t partition(uint32_t *arr, uint32_t lo, uint32_t hi) { //jdvallad helped me debug
    int64_t pivot = arr[lo + ((hi - lo) / 2)];
    int64_t i = lo;
    int64_t j = hi;
    while (i < j) {
        comparesQQ += 2;
        comparesQS += 2;
        while (arr[i] < pivot) {
            i = i + 1;
        }
        while (arr[j] > pivot) {
            j = j - 1;
        }
        if (i < j) {
            int64_t temp;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            movesQQ += 3;
            movesQS += 3;
        }
    }
    return j;
}
//got from asgn pdf
void quick_sort_stack(uint32_t *A, uint32_t n) {
    int64_t pop;
    int lo = 0;
    int hi = n - 1;
    movesQQ = 0;
    comparesQQ = 0;
    Stack *s = stack_create(n * 2);
    stack_push(s, lo);
    stack_push(s, hi);
    while (stack_empty(s) != true) {
        stack_pop(s, &pop);
        hi = pop;
        stack_pop(s, &pop);
        lo = pop;
        int64_t p = partition(A, lo, hi);
        if (lo < p) {
            stack_push(s, lo);
            stack_push(s, p);
        }
        if (hi > p + 1) {
            stack_push(s, p + 1);
            stack_push(s, hi);
        }
        if (maxStack < stack_size(s)) {
            maxStack = stack_size(s);
        }
    }
}
//got from asgn pdf
void quick_sort_queue(uint32_t *A, uint32_t n) {
    int64_t deq;
    int lo = 0;
    int hi = n - 1;
    movesQQ = 0;
    comparesQQ = 0;
    maxQueue = 0;
    Queue *q = queue_create(n * 2);
    enqueue(q, lo);
    enqueue(q, hi);
    while (!queue_empty(q)) {
        dequeue(q, &deq);
        lo = deq;
        dequeue(q, &deq);
        hi = deq;
        int64_t p = partition(A, lo, hi);
        if (lo < p) {
            enqueue(q, lo);
            enqueue(q, p);
        }
        if (hi > (p + 1)) {
            enqueue(q, p + 1);
            enqueue(q, hi);
        }
        if (queue_size(q) > maxQueue) {
            maxQueue = queue_size(q);
        }
    }
}
