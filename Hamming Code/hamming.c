#include "bm.h"
#include "bv.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum HAM_STATUS { HAM_OK = -3, HAM_ERR = -2, HAM_CORRECT = -1 } HAM_STATUS;
//encoder, multiplies G to msg and converts
uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    return bm_to_data(bm_multiply(bm_from_data(msg, 4), G));
}
//helper function, flips bits
void flip(BitMatrix *c, int index) {
    if (bm_get_bit(c, 0, index) == 0) {
        bm_set_bit(c, 0, index);
    } else {
        bm_clr_bit(c, 0, index);
    }
}
//hamming decode, instead of array I used case switch whoops
HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    BitMatrix *bm = bm_multiply(bm_from_data(code, 8), Ht);
    BitMatrix *c_Matrix = bm_from_data(code, 8);
    uint8_t e = bm_to_data(bm);
    switch (e) {
    case 0: //ok
        *msg = code;
        return HAM_OK;
        break;
    case 7: //bit 3 wrong
        flip(c_Matrix, 3);
        *msg = bm_to_data(c_Matrix);
        return HAM_CORRECT;
        break;
    case 11: //bit 2 wrong
        flip(c_Matrix, 2);
        *msg = bm_to_data(c_Matrix);
        return HAM_CORRECT;
        break;
    case 13: //bit 1 wrong
        flip(c_Matrix, 1);
        *msg = bm_to_data(c_Matrix);
        return HAM_CORRECT;
        break;
    case 14: //bit 0 wrong
        flip(c_Matrix, 0);
        *msg = bm_to_data(c_Matrix);
        return HAM_CORRECT;
        break;
    case 8: //bit 7 wrong
        flip(c_Matrix, 7);
        *msg = bm_to_data(c_Matrix);
        return HAM_CORRECT;
        break;
    case 4: //bit 6 wrong
        flip(c_Matrix, 6);
        *msg = bm_to_data(c_Matrix);
        return HAM_CORRECT;
        break;
    case 2: //bit 5 wrong
        flip(c_Matrix, 5);
        *msg = bm_to_data(c_Matrix);
        return HAM_CORRECT;
        break;
    case 1: //bit 1 wrong
        flip(c_Matrix, 4);
        *msg = bm_to_data(c_Matrix);
        return HAM_CORRECT;
        break;
    default: //any other situation cannot be fixed
        return HAM_ERR;
    }
}
