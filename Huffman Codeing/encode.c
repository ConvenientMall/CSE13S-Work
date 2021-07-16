#include "code.h"
#include "defines.h"
#include "globalvar.h"
#include "header.h"
#include "huffman.h"
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
#define OPTIONS "hi:o:v"

//help function print
void synopsis(void) {
    printf("SYNOPSIS\n");
    printf("  A Huffman encoder.\n");
    printf("  Compresses a file using the Huffman coding algorithm.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./encode [-h] [-i infile] [-o outfile]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h             Program usage and help.\n");
    printf("  -v             Print compression statistics.\n");
    printf("  -i infile      Input file to compress.\n");
    printf("  -o outfile     Output of compressed data.\n");
}

//used in post order
static uint8_t write_Buff[60];
static int tree_Index = 0;
static int dump_Bytes = 0;

//post order helper function, recursive
int post_order(Node *root) {
    //printf("%c ", root->symbol);
    if (root->left != NULL) {
        post_order(root->left);
    }
    if (root->right != NULL) {
        post_order(root->right);
    }
    if (root->left == NULL && root->right == NULL) {
        write_Buff[tree_Index] = 'L';
        write_Buff[tree_Index + 1] = root->symbol;
        tree_Index += 2;
        dump_Bytes += 2;
        return 0;
    } else {
        write_Buff[tree_Index] = 'I';
        tree_Index += 1;
        dump_Bytes += 1;
        return 0;
    }
    return 0;
}

//write header
void write_header(int out, Header *h) {
    write(out, h, 16);
}

int main(int argc, char **argv) {
    int opt = 0;
    char *fileIn = (char *) malloc(20 * sizeof(char));
    char *fileOut = (char *) malloc(20 * sizeof(char));
    bool infileDef = true;
    bool outfileDef = true;
    bool synop = false;
    bool verbose = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': synop = true; break;
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
        case 'v':
            //verbose
            verbose = true;
            break;

        default: synop = true; break;
        }
    }
    if (synop == true) {
        synopsis();
        return 0;
    }
    //file in
    int fi;
    //file out
    int fo;
    //if in file Def = true, use stdin
    if (infileDef) {
        fi = STDIN_FILENO;
    } else {
        fi = open(fileIn, O_RDONLY);
    }

    //if file out default =fO true, use stdout
    if (outfileDef) {
        fo = STDOUT_FILENO;
    } else {
        fo = open(fileOut, O_WRONLY);
    }

    //part of code that fills out histogram
    int unique_Bytes = 0;
    int num_Bytes = 0;
    uint64_t alph_Hist[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) {
        alph_Hist[i] = 0;
    }
    do {
        uint8_t *buff = (uint8_t *) calloc(BLOCK, sizeof(char));
        num_Bytes = read_bytes(fi, buff, BLOCK);
        for (int i = 0; i < num_Bytes; i++) {
            alph_Hist[buff[i]]++;
        }
    } while (num_Bytes == BLOCK);

    //calculate unqieue bytes
    for (int i = 0; i < ALPHABET; i++) {
        if (alph_Hist[i] != 0) {
            unique_Bytes += 1;
        }
    }

    //adds to 0 and 255
    //ward against edge cases
    alph_Hist[0] += 1;
    alph_Hist[255] += 1;

    //builds tree
    Code table[ALPHABET];
    Node *root = build_tree(alph_Hist);
    build_codes(root, table);
    unique_Bytes += 2;

    //header portion
    struct stat statbuf;
    fstat(fi, &statbuf);
    fchmod(fo, statbuf.st_mode);
    struct Header h;
    h.magic = MAGIC;
    h.permissions = statbuf.st_mode;
    h.tree_size = (3 * unique_Bytes) - 1;
    h.file_size = statbuf.st_size;
    write_header(fo, &h);

    //goes through tree in post order and prints
    post_order(root);
    write_bytes(fo, write_Buff, dump_Bytes);

    //resets file
    lseek(fi, 0, SEEK_SET);

    //prints out the code version of the text
    do {
        uint8_t *buff = (uint8_t *) calloc(BLOCK, sizeof(char));
        num_Bytes = read_bytes(fi, buff, BLOCK);
        for (int i = 0; i < num_Bytes; i++) {
            write_code(fo, &table[buff[i]]);
        }
    } while (num_Bytes == BLOCK);
    //flushes code
    flush_codes(fo);

    //calculates bytes of compressed
    bytesEn += h.tree_size;
    bytesEn += 16;
    //verbose
    if (verbose) {
        printf("file size: %d bytes\n", (int) h.file_size);
        printf("Compressed file size: %d bytes\n", bytesEn);
        printf(
            "Space saving: %.2f%c\n", 100 * (1 - (((float) bytesEn) / ((float) h.file_size))), '%');
    }
    //closes files
    close(fo);
    close(fi);
    return 0;
}
