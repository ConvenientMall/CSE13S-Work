#include "ll.h"

#include "node.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t seeks = 0;
uint64_t links = 0;

struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};
//creates ll
LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    ll->mtf = mtf;
    ll->length = 0;
    Node *head_Node = node_create(NULL, NULL);
    Node *tail_Node = node_create(NULL, NULL);
    ll->head = head_Node;
    ll->tail = tail_Node;
    ll->head->next = ll->tail;
    ll->tail->prev = ll->head;
    return ll;
}
//delete every node
//also linked list
void ll_delete(LinkedList **ll) {
    for (uint32_t i = 0; i < ll_length(*ll); i++) {
        Node *temp = ((*ll)->head->next);
        node_delete(&(*ll)->head);
        (*ll)->head = temp;
    }
    node_delete(&(*ll)->head);
    node_delete(&(*ll)->tail);
    free(*ll);
    *ll = NULL;
}
//returns length
uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}
//looks up returns node
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    Node *temp = ll->head;
    seeks += 1;
    do {
        if (temp->oldspeak != NULL && strcmp(temp->oldspeak, oldspeak) == 0) {
            if (ll->mtf) {
                (temp->prev)->next = (temp->next);
                (temp->next)->prev = (temp->prev);
                temp->next = ll->head->next;
                temp->prev = ll->head;
                (ll->head->next)->prev = temp;
                ll->head->next = temp;
            }
            return temp;
        }
        links += 1;
        temp = temp->next;
    } while (temp->oldspeak != NULL);
    links = links - 1;
    return NULL;
}
//inserts node behind head
void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (ll_lookup(ll, oldspeak) == NULL) {
        ll->length += 1;
        Node *n = node_create(oldspeak, newspeak);
        n->next = ll->head->next;
        n->prev = ll->head;
        (ll->head->next)->prev = n;
        (ll->head->next) = n;
    }
    return;
}
//tester plus printer for banhammer
void ll_print(LinkedList *ll) {
    Node *temp = ll->head->next;
    while (temp->oldspeak != NULL) {
        printf("%s", temp->oldspeak);
        if (0 != strcmp(temp->newspeak, "")) {
            printf(" -> ");
            printf("%s", temp->newspeak);
        }
        printf("\n");
        temp = temp->next;
    }
}
