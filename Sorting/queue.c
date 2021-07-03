#include "queue.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Queue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    int64_t *items;
};

Queue *queue_create(uint32_t capacity) { //got in eugines section
    Queue *q = (Queue *) malloc(sizeof(Queue));
    q->tail = 0;
    q->head = 0;
    q->size = 0;
    q->capacity = capacity;
    q->items = (int64_t *) malloc(capacity * sizeof(int64_t));
    return q;
}

void queue_delete(Queue **q) { //got in the pdf
    if (*q && ((*q)->items)) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

bool queue_empty(Queue *q) {
    if (q) {
        return (q->size == 0);
    }
    return true;
}

bool queue_full(Queue *q) {
    if (q) {
        return (q->size == q->capacity); //if size reaches capacity
    }
    return true;
}

uint32_t queue_size(Queue *q) {
    return q->size;
}

bool enqueue(Queue *q, int64_t x) { // got in eugine's section
    if (q) {
        if (queue_full(q)) {
            return false;
        }
        q->items[q->head] = x;
        q->head = q->head + 1;
        q->size = q->size + 1;
        return true;
    } else {
        return false;
    }
}

bool dequeue(Queue *q, int64_t *x) { //got in eugine's section
    if (q) {
        if (queue_empty(q)) {
            return false;
        }
        *x = q->items[q->tail];
        q->tail = (q->tail + 1 % q->capacity);
        q->size = q->size - 1;
        return true;
    } else {
        return false;
    }
}

void queue_print(Queue *q) { //eugine's section
    printf("[");
    for (uint32_t i = 0; i < q->size; i += 1) {
        printf("%" PRId64, q->items[i + q->tail]);
        if (i + 1 != q->size) {
            printf(", ");
        }
    }
    printf("]\n");
}
