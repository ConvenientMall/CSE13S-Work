#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack { //got from pdf
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
};
//got from pdf
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->top = 0;
    s->capacity = capacity;
    s->items = (int64_t *) malloc(capacity * sizeof(int64_t));
    return s;
}
//deletes stack
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
//returns if stack is full
bool stack_full(Stack *s) {
    return s->top == s->capacity;
}
//returns stack size
uint32_t stack_size(Stack *s) {
    uint32_t solution = s->top;
    return solution;
}
//pushes things onto stack, got from section
bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}
//pops things from stack, got from section
bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}
//looks at the top of stack without popping
bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    *x = s->items[s->top - 1];
    return true;
}
//copies stack src to dst
void stack_copy(Stack *dst, Stack *src) {
    for (uint32_t i = 0; i < (src->top); i++) {
        stack_push(dst, src->items[i]);
    }
}

//got from pdf, but it prints out stack for path
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
