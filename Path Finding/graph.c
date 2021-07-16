#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) malloc(sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    //sets all as not visited
    for (uint32_t i = 0; i < vertices; i++) {
        G->visited[i] = false;
    }
    //sets matrix to all zeros
    for (uint32_t x = 0; x < vertices; x++) {
        for (uint32_t y = 0; y < vertices; y++) {
            G->matrix[x][y] = 0;
        }
    }
    return G;
}
//delted graph
void graph_delete(Graph **G) {
    if (*G) {
        free(*G);
        *G = NULL;
    }
    return;
}
//returns amount of vertices
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}
//add edge in matrix
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (graph_vertices(G) >= i && graph_vertices(G) >= j) { //checks if the nums are viable
        G->matrix[i][j] = k;
        if (G->undirected) {
            G->matrix[j][i] = k;
            return true;
        }
        return true;
    } else {
        return false;
    }
}

//checks if edge has a weight if it does it has an edge
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (G->matrix[i][j] > 0 && graph_vertices(G) >= i && graph_vertices(G) >= j) {
        return true;
    } else {
        return false;
    }
}
//returns the edge weight
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (graph_vertices(G) < i && graph_vertices(G) < j) {
        return 0;
    }
    return G->matrix[i][j];
}
//returns if the graph has been visited
bool graph_visited(Graph *G, uint32_t v) {
    return G->visited[v];
}
//marks vertice v as visited
void graph_mark_visited(Graph *G, uint32_t v) {
    if (graph_vertices(G) >= v) {
        G->visited[v] = true;
    }
    return;
}
//marks vertice v as not visited
void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (graph_vertices(G) >= v) {
        G->visited[v] = false;
    }
    return;
}
//prints out the graph. Tester
void graph_print(Graph *G) {
    for (uint32_t x = 0; x < G->vertices; x++) {
        for (uint32_t y = 0; y < G->vertices; y++) {
            printf("%d   ", G->matrix[x][y]);
        }
        printf("\n");
    }
}
