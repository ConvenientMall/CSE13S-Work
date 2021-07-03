#include "bv.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};
//creates vector
BitVector *bv_create(uint32_t length) {
    BitVector *v = calloc(1, sizeof(BitVector));
    v->length = length;
    v->vector = calloc(((v->length + 7) / 8), sizeof(int8_t)); //add items as much as needed.
    return v;
}
//delete bitvector
void bv_delete(BitVector **v) {
    if (*v && ((*v)->vector)) {
        free((*v)->vector);
        free(*v);
        *v = NULL;
    }
    return;
}
//returns length
uint32_t bv_length(BitVector *v) {
    return v->length;
}
//sets the bit vector
void bv_set_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] = v->vector[i / 8] | (1 << i % 8);
    return;
}
//clrs the bit at i
void bv_clr_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] = v->vector[i / 8] & ~(1 << i % 8);
    return;
}

//get bit at i
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    return (v->vector[i / 8] >> (i % 8) & 1);
}
//print the bv
void bv_print(BitVector *v) {
    for (uint32_t i = 0; i < v->length; i++) {
        if (i % 8 == 0 && i != 0) {
            printf("\n");
        }
        int print = v->vector[i / 8] & (1 << i % 8);
        printf("%u ", !!print);
    }
    printf("\n");
    return;
}
