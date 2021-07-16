#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//node creator for binary trees
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->left = NULL;
    n->right = NULL;
    n->symbol = symbol;
    n->frequency = frequency;
    return n;
}
//deletes node
void node_delete(Node **n) {
    free(*n);
    *n = NULL;
    return;
}
//joins nodes together and makes the joied node $
Node *node_join(Node *left, Node *right) {
    uint64_t sum = left->frequency + right->frequency;
    Node *n = node_create(0x24, sum);
    n->left = left;
    n->right = right;
    return n;
}
//prints node debugging function
static int index = 0;
void node_print(Node *n) {
    printf("symbol %c\n", n->symbol);
    printf("freq   %lu\n", n->frequency);
    if (n->left != NULL) {
        printf("%d\n", index);
        index++;
        node_print(n->left);
    }
    if (n->right != NULL) {
        printf("%d\n", index);
        index++;
        node_print(n->right);
    }
}
