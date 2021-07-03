#include "bm.h"
#include "bv.h"
#include "hamming.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define OPTIONS "hi:o:"

//help function print
void synopsis(void) {
    printf("SYNOPSIS\n");
    printf("  A Hamming(8, 4) systematic code generator.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./encode [-h] [-i infile] [-o outfile]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h             Program usage and help.\n");
    printf("  -i infile      Input data to encode.\n");
    printf("  -o outfile     Output of encoded data.\n");
}

// Returns the lower nibble of val
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}
// Returns the upper nibble of val
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}
// Packs two nibbles into a byte
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

int main(int argc, char **argv) {
    int opt = 0;
    char *fileIn = (char *) malloc(20 * sizeof(char));
    char *fileOut = (char *) malloc(20 * sizeof(char));
    //flags
    bool infileDef = true;
    bool outfileDef = true;
    bool synop = false;

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
        default: synop = true; break;
        }
    }
    if (synop == true) {
        synopsis();
        return 0;
    }
    //file in
    FILE *fi_File;
    //file out
    FILE *fo_File;
    //if in file Def = true, use stdin
    if (infileDef) {
        fi_File = stdin;
    } else {
        fi_File = fopen(fileIn, "rb");
    }

    //if file out default = true, use stdout
    if (outfileDef) {
        fo_File = stdout;
    } else {
        fo_File = fopen(fileOut, "wb");
    }

    //copys file perms
    struct stat statbuf;
    fstat(fileno(fi_File), &statbuf);
    fchmod(fileno(fo_File), statbuf.st_mode);
    //creates transpose H matrix
    BitMatrix *G = bm_create(4, 8);
    for (uint32_t i = 0; i < 4; i++) {
        bm_set_bit(G, i, i);
    }
    for (uint32_t i = 0; i < 4; i++) {
        for (uint32_t j = 0; j < 4; j++) {
            if (i != j) {
                bm_set_bit(G, i, 4 + j);
            }
        }
    }

    //goes till last line
    while (1) {
        uint8_t enNum = fgetc(fi_File); //gets byte
        if (feof(fi_File)) {
            break;
        }
        fputc(ham_encode(G, lower_nibble(enNum)), fo_File); // encode lower nibble and puts
        fputc(ham_encode(G, upper_nibble(enNum)), fo_File); // encode upper nibble and puts
    }
}
