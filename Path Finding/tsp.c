#include "globalvar.h"
#include "graph.h"
#include "path.h"
#include "vertices.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "hvui:o:"

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    recursivesG++;
    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);
    //recursion
    for (uint32_t i = 0; i < graph_vertices(G); i++) {
        if (graph_has_edge(G, v, i) && graph_visited(G, i) == false) {
            dfs(G, i, curr, shortest, cities, outfile);
        }
    }

    //all visited bool
    bool visited_All = true;
    for (uint32_t i = 0; i < graph_vertices(G); i++) {
        if (!graph_visited(G, i)) {
            visited_All = false;
        }
    }
    uint32_t temp = 0;

    //all visited and has an edge from v to the start
    if (visited_All && graph_has_edge(G, v, START_VERTEX)) {
        path_push_vertex(curr, START_VERTEX, G);
        //if verbose enabled
        if (verboseG) {
            printf("Path length: %d\n", path_length(curr));
            printf("Path: ");
            path_print(curr, outfile, cities);
        }
        //checks if length curr is less then shortest
        //iff it is copy curr to shortest
        if (path_length(curr) < path_length(shortest)) {
            path_copy(shortest, curr);
        }
        path_pop_vertex(curr, &temp, G);
    }
    graph_mark_unvisited(G, v);
    path_pop_vertex(curr, &temp, G);
    return;
}

void synopsis(void) {
    printf("SYNOPSIS\n");
    printf("  Traveling Salesman Problem using DFS.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -u             Use undirected graph.\n");
    printf("  -v             Enable verbose printing.\n");
    printf("  -h             Program usage and help.\n");
    printf("  -i infile      Input containing graph (default: stdin)\n");
    printf("  -o outfile     Output of computed path (default: stdout)\n");
}

int main(int argc, char **argv) {
    int opt = 0;
    char *fileIn = (char *) malloc(20 * sizeof(char));
    char *fileOut = (char *) malloc(20 * sizeof(char));

    //flags
    bool undir = false;
    bool verbose = false;
    bool infileDef = true;
    bool outfileDef = true;
    bool synop = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': synop = true; break;
        case 'v': verbose = true; break;
        case 'u': undir = true; break;
        case 'i':
            //gets input file name
            strcpy(fileIn, optarg);
            infileDef = false;
            break;
        case 'o':
            //gets output file name
            strcpy(fileOut, optarg);
            outfileDef = false;
            break;
        default: break;
        }
    }
    if (synop == true) {
        synopsis();
        return 0;
    }
    verboseG = verbose;
    //file in
    FILE *fi_File;
    //file out
    FILE *fo_File;
    //if in file Def = true, use stdin
    if (infileDef) {
        fi_File = stdin;
    } else {
        fi_File = fopen(fileIn, "r");
    }

    //if file out default = true, use stdout
    if (outfileDef) {
        fo_File = stdout;
    } else {
        fo_File = fopen(fileOut, "w");
    }

    //buffer for vnum
    char vectNumBuff[20];
    //gets first line
    fgets(vectNumBuff, 20, fi_File);
    int vNum = atoi(vectNumBuff);
    //creates graph of vertices vnum and undir(tru/false)
    Graph *G = graph_create(vNum, undir);
    char *city_arr[vNum];

    char buff[100];
    for (int i = 0; i < vNum; i++) {
        fgets(buff, 100, fi_File);
        buff[strlen(buff) - 1] = '\0';
        city_arr[i] = strdup(buff);
    }
    //scans file untill format no longer mathces three
    uint32_t i;
    uint32_t j;
    uint32_t w;
    while (fscanf(fi_File, "%u %u %u", &i, &j, &w) == 3) {
        graph_add_edge(G, i, j, w);
    }

    //creates path and calls dfs
    Path *current = path_create();
    Path *shortest = path_create();
    dfs(G, START_VERTEX, current, shortest, city_arr, fo_File);

    printf("Path length: %d\n", path_length(shortest));
    printf("Path: ");
    path_print(shortest, fo_File, city_arr);
    printf("Total recursive calls: %d\n", recursivesG);
    path_print(shortest, fo_File, city_arr);
}
