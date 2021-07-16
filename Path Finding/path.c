#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create() {
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(VERTICES);
    p->length = 0;
    return p;
}

//delets path
void path_delete(Path **p) {
    if (*p && ((*p)->vertices)) {
        free((*p)->vertices);
        free(*p);
        *p = NULL;
    }
    return;
}

//pushes v into stack, and adds the edge weight with the previus in stack to length
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t peek;
    if (stack_empty(p->vertices)) {
        peek = v;
    } else {
        stack_peek(p->vertices, &peek);
    }
    stack_push(p->vertices, v);
    p->length += graph_edge_weight(G, peek, v);
    return true;
}
//removes from stack *v, and removes the edge weight the popped vector had with the previus in stack from length
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t peek;
    uint32_t pop;
    if (!stack_peek(p->vertices, &peek) || !stack_pop(p->vertices, v)) {
        return false;
    }
    stack_peek(p->vertices, &peek);
    stack_pop(p->vertices, &pop);
    p->length -= graph_edge_weight(G, peek, *v);
    return true;
}
//returns the amout of vertices at the moment
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}
//returns path length
uint32_t path_length(Path *p) {
    return p->length;
}
//copys the path from src to dst
void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
}
//prints
void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities);
}
