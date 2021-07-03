#include "bf.h"

#include "speck.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct BloomFilter {
    uint64_t primary[2]; // Primary hash function salt .
    uint64_t secondary[2]; // Secondary hash function salt .
    uint64_t tertiary[2]; // Tertiary hash function salt .
    BitVector *filter;
};

//bf set
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}
//deletes bf and frees memory
void bf_delete(BloomFilter **bf) {
    if (*bf && ((*bf)->filter)) {
        free((*bf)->filter);
        free(*bf);
        *bf = NULL;
    }
    return;
}
//return bf size
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}
//inserts bits so that it can later be checked for no or maybe
void bf_insert(BloomFilter *bf, char *oldspeak) {
    bv_set_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
}
// returns no or maybe for if oldpseak exists in hashtable
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    int count = 0;
    count += bv_get_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf));
    count += bv_get_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf));
    count += bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
    if (count == 3) {
        return true;
    } else {
        return false;
    }
}
//return bf count
uint32_t bf_count(BloomFilter *bf) {
    int count = 0;
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        count += bv_get_bit(bf->filter, i);
    }
    return count;
}
//prints and debugger
void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
