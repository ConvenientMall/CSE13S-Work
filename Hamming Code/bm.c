#include "bm.h"

#include "bv.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    m->rows = rows;
    m->cols = cols;
    m->vector = bv_create(cols * rows);
    return m;
}
//delets bit matrix
void bm_delete(BitMatrix **m) {
    if (*m && ((*m)->vector)) {
        free((*m)->vector);
        free(*m);
        *m = NULL;
    }
    return;
}
//return rows of bm
uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}
//return cols of bm
uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}
//sets bit of bm at row/col
void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, r * bm_cols(m) + c); // r * a + c
}
//clears bit of bm at row/col
void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, r * bm_cols(m) + c); // r * a + c
}
//returns the bit at row/col
uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(m->vector, r * bm_cols(m) + c);
}
//returns bm of one row length coloums from byte
BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *bm = bm_create(1, length);
    for (uint32_t i = 0; i < length; i++) { //loops through byte
        if ((byte & (1 << i % 8)) == 1 << i % 8) {
            bv_set_bit(bm->vector, i);
        }
    }
    return bm;
}
//gets byte from bm of the first row.
uint8_t bm_to_data(BitMatrix *m) {
    uint8_t data = 0;
    for (uint32_t i = 0; i < bm_cols(m); i++) {
        if (bm_get_bit(m, 0, i) == 1) {
            data += 1 << i;
        }
    }
    return data;
}
//matrix multiplication.
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    assert(bm_rows(B) == bm_cols(A));
    BitMatrix *bm = bm_create(bm_rows(A), bm_cols(B)); //creates bm for after mult
    for (uint32_t i = 0; i < bm_rows(A); i++) { //got from presentation
        for (uint32_t j = 0; j < bm_cols(B); j++) {
            int sol = 0;
            for (uint32_t k = 0; k < bm_cols(A); k++) {
                sol = sol + (bm_get_bit(A, i, k) * bm_get_bit(B, k, j));
            }
            if (sol % 2 == 1) {
                bm_set_bit(bm, i, j);
            }
            sol = 0;
        }
    }
    return bm;
}

void bm_print(BitMatrix *m) {
    bv_print(m->vector);
}
