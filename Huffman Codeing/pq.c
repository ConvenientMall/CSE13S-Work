#include "pq.h"

#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    Node *items;
};
//contructor for priority queue.
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    pq->tail = 0;
    pq->head = 0;
    pq->size = 0;
    pq->capacity = capacity;
    pq->items = (Node *) malloc(capacity * sizeof(Node));
    return pq;
}
//deletes pq
void pq__delete(PriorityQueue **pq) {
    if (*pq && ((*pq)->items)) {
        free((*pq)->items);
        free(*pq);
        *pq = NULL;
    }
    return;
}
//returns if pq is empty
bool pq_empty(PriorityQueue *pq) {
    if (pq) {
        return (pq->size == 0);
    }
    return true;
}
//return if pq is full
bool pq_full(PriorityQueue *pq) {
    if (pq) {
        return (pq->size == pq->capacity); //if size reaches capacity
    }
    return true;
}
//return pq size
uint32_t pq_size(PriorityQueue *pq) {
    return pq->size;
}
//enques node into pq and sorts it into the correct poistion
bool enqueue(PriorityQueue *pq, Node *x) { // got in eugine's section
    if (pq) {
        if (pq_full(pq)) {
            return false;
        }
        for (int i = pq->size; i >= 0; i -= 1) { // I gotta flip it so it counts down.
            if ((pq->items[i + (int) pq->tail - 1]).frequency > x->frequency
                && i + (int) pq->tail != 0) {
                pq->items[i + pq->tail] = pq->items[i + pq->tail - 1];
            } else {
                pq->items[i + pq->tail] = *x;
                break;
            }
        }
        pq->size += 1;
        return true;
    } else {
        return false;
    }
}
//deques pq into node
bool dequeue(PriorityQueue *pq, Node **x) { //got in eugine's section
    if (pq) {
        if (pq_empty(pq)) {
            return false;
        }
        *x = &pq->items[pq->tail];
        pq->tail = (pq->tail + 1 % pq->capacity);
        pq->size = pq->size - 1;
        return true;
    } else {
        return false;
    }
}
//debug function
void pq_print(PriorityQueue *pq) {
    printf("[");
    for (uint32_t i = 0; i < pq->size; i += 1) {
        node_print(&pq->items[i + pq->tail]);
        if (i + 1 != pq->size) {
            printf(", ");
        }
    }
    printf("]\n");
}
