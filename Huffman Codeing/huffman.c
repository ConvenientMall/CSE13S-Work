#include "huffman.h"

#include "code.h"
#include "defines.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <assert.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

//builds tree for use in encode
//builds tree from histogram of all ascii
//letters in the histogram
Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *pq = pq_create(ALPHABET);
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] != 0) {
            Node *n = node_create(i, hist[i]);
            enqueue(pq, n);
        }
    }
    Node *left;
    Node *right;
    Node *joined;
    while (pq_size(pq) > 1) {
        dequeue(pq, &left);
        dequeue(pq, &right);
        joined = node_join(left, right);
        enqueue(pq, joined);
    }
    Node *root;
    dequeue(pq, &root);
    return root;
}
//builds codes from dump table
void build_codes(Node *root, Code table[static ALPHABET]) {
    static Code c = { 0, { 0 } };
    uint8_t bit = 0;
    if (root) {
        if (root->left == NULL && root->right == NULL) {
            table[root->symbol] = c;
        } else {
            code_push_bit(&c, 0);
            build_codes(root->left, table);
            code_pop_bit(&c, &bit);

            code_push_bit(&c, 1);
            build_codes(root->right, table);
            code_pop_bit(&c, &bit);
        }
    }
}
//rebuilds tree from dumptree.
Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Stack *s = stack_create(nbytes);
    for (int i = 0; i < nbytes; i++) {
        if (tree[i] == 'L') {
            Node *n = node_create(tree[i + 1], 0);
            stack_push(s, n);
        } else if (tree[i] == 'I') {
            Node *left;
            Node *right;
            stack_pop(s, &right);
            stack_pop(s, &left);
            stack_push(s, node_join(left, right));
        }
    }
    Node *root;
    stack_pop(s, &root);
    stack_delete(&s);
    return root;
}
//deletes tree
void delete_tree(Node **root) {
    node_delete(root);
}
