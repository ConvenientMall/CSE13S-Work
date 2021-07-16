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
    printf("  A Huffman decoder.\n");
    printf("  Decompresses a file using the Huffman coding algorithm.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./decode [-h] [-i infile] [-o outfile]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h             Program usage and help.\n");
    printf("  -v             Print compression statistics.\n");
    printf("  -i infile      Input data to decompress.\n");
    printf("  -o outfile     Output of decompressed data.\n");
}
//used for traversal
static uint8_t write_Buff[60];
Node *root;

//traversal moves through tree to decode
bool traversal(Node *root, Node *org, int fi, int fo) {
    //printf("char %c\n", root->symbol);
    write_Buff[0] = root->symbol;
    if (root->left == NULL && root->right == NULL) {
        //printf("nodefound\n");
        write(fo, write_Buff, 1);
        return true;
    }
    uint8_t temp_bit = 0;
    if (!read_bit(fi, &temp_bit)) {
        return false;
    }
    //printf("temp bit %u\n", temp_bit);
    if (temp_bit == 0) {
        traversal(root->left, org, fi, fo);
        return true;
    }
    if (temp_bit == 1) {
        traversal(root->right, org, fi, fo);
        return true;
    }
    return true;
}
//writes header
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
            //verbose option
            verbose = true;
            break;
        default: synop = true; break;
        }
    }
    //prints help
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

    //header section of code
    Header h;
    read(fi, &h, 16);
    if (h.magic != MAGIC) {
        printf("Error: Magic does not match\n");
        printf("file potentialy not encoded with required huffman encoder\n");
        return 0;
    }
    struct stat statbuf;
    fstat(fi, &statbuf);
    fchmod(fo, statbuf.st_mode);

    //read bytes and creates dump tree
    uint8_t dump_Tree[h.tree_size];
    read_bytes(fi, dump_Tree, h.tree_size);

    //rebuilds tree from dump tree
    Node *root = rebuild_tree(h.tree_size, dump_Tree);

    //does traversal untill traversal does not have bytes
    //to traverse over
    bool notEmpty = true;
    while (notEmpty) {
        notEmpty = traversal(root, root, fi, fo);
    }

    bytesDe += 16 + h.tree_size; //holds calculated compresed size
    //prints out verbose
    if (verbose) {
        printf("Compressed File size: %d bytes\n", (int) bytesDe);
        printf("Decompressed fil size: %d bytes\n", (int) h.file_size);
        printf(
            "Space saving: %.2f%c\n", 100 * (1 - (((float) bytesDe) / ((float) h.file_size))), '%');
    }
    //close files
    close(fo);
    close(fi);
    return 0;
}
