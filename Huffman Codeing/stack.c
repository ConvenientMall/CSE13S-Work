#include "stack.h"

#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};
//stack contructor
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->top = 0;
    s->capacity = capacity;
    s->items = (Node **) malloc(capacity * sizeof(Node));
    return s;
}
//stack delete
void stack_delete(Stack **s) {
    if (*s && ((*s)->items)) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}
//returns if stack is empty
bool stack_empty(Stack *s) {
    return s->top == 0;
}
//returns of stack is full
bool stack_full(Stack *s) {
    return s->top == s->capacity;
}
//return stack size
uint32_t stack_size(Stack *s) {
    uint32_t solution = s->top;
    return solution;
}
//pushes things onto stack, got from section
bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = n;
    s->top += 1;
    return true;
}
//pops things from stack, got from section
bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *n = s->items[s->top];
    return true;
}
//got from eugine section
//its a debugg function that prints stack
void stack_print(Stack *s) {
    printf("[");
    for (uint32_t i = 0; i < s->top; i += 1) {
        node_print(s->items[i]);
        if (i + 1 != s->top) {
            printf(", ");
        }
    }
    printf("]\n");
}
