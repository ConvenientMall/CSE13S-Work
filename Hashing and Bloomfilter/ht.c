#include "ht.h"

#include "ll.h"
#include "speck.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};
//ht create
HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        // Leviathan
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}
// deletes the hashtable
void ht_delete(HashTable **ht) {
    for (uint32_t i = 0; i < (*ht)->size; i++) {
        if ((*ht)->lists[i] != 0) {
            ll_delete(&(*ht)->lists[i]);
        }
    }
    free((*ht)->lists);
    (*ht)->lists = NULL;
    free(*ht);
    (*ht) = NULL;
}
//return hash size
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}
//looks up hash table and returns coresponing node
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    if (ht->lists[index] == 0) {
        return NULL;
    }
    return ll_lookup(ht->lists[index], oldspeak);
}
//inserts into hash table as node
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    if (ht->lists[index] == 0) {
        ht->lists[index] = ll_create(ht->mtf);
    }
    ll_insert(ht->lists[index], oldspeak, newspeak);
    return;
}
//return ht count
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->lists[i] != 0) {
            count += 1;
        }
    }
    return count;
}
//debugger and ht printer
void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->lists[i] != 0) {
            ll_print(ht->lists[i]);
            printf("\nnext\n");
        }
    }
}
