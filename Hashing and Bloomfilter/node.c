#include "node.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//makes node struct
char *strdup_new(char *s) {
    void *new = malloc(strlen(s) + 1);
    if (new == NULL)
        return NULL;
    return (char *) memcpy(new, s, strlen(s) + 1);
}
//creates node and sets up its info inside
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->next = NULL;
    n->prev = NULL;
    if (oldspeak == NULL && newspeak == NULL) {
        n->oldspeak = NULL;
        n->newspeak = NULL;
    } else {
        n->oldspeak = strdup_new(oldspeak);
        n->newspeak = strdup_new(newspeak);
    }
    return n;
}
//deletes node
void node_delete(Node **n) {
    free((*n)->oldspeak);
    free((*n)->newspeak);
    free(*n);
    *n = NULL;
    return;
}
//debugger and printing
void node_print(Node *n) {
    printf("current\n");
    printf("oldspeak - %s	", n->oldspeak);
    printf("newspeak - %s\n", n->newspeak);
}
