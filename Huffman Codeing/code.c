#include "code.h"

#include "defines.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//builds code
//does not need to be deleted
Code code_init(void) {
    Code c;
    c.top = 0;
    for (int i = 0; i < MAX_CODE_SIZE; i++) {
        c.bits[i] = 0;
    }
    return c;
}
//return size of code stack
uint32_t code_size(Code *c) {
    return c->top;
}
//tells if code stack is empty or not
bool code_empty(Code *c) {
    return c->top == 0;
}
//tells if code stack is full or not
bool code_full(Code *c) {
    return c->top / 8 == MAX_CODE_SIZE - 1;
}
//pushes bit in bit into c
bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    }
    if (bit == 0) {
        c->bits[c->top / 8] = c->bits[c->top / 8] & ~(1 << c->top % 8);
    } else {
        c->bits[c->top / 8] = c->bits[c->top / 8] | (1 << c->top % 8);
    }
    c->top += 1;
    return true;
}
//pops bit from c and pushes it into bit
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_full(c)) {
        return false;
    }
    c->top -= 1;
    *bit = c->bits[c->top / 8] >> (c->top % 8) & 1;
    c->bits[c->top / 8] = c->bits[c->top / 8] & ~(1 << c->top % 8);
    return true;
}
//debugg fucntion that prints code stack
void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        if (i % 8 == 0 && i != 0) {
            printf("\n");
        }
        int print = c->bits[i / 8] & (1 << i % 8);
        printf("%u ", !!print);
    }
    printf("\n");
    return;
}
