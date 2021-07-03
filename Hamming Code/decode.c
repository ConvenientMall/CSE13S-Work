#include "bm.h"
#include "bv.h"
#include "globalvar.h"
#include "hamming.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define OPTIONS "hvi:o:"

//the help print function
void synopsis(void) {
    printf("SYNOPSIS\n");
    printf("  A Hamming(8, 4) systematic code decoder\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./decode [-h] [-v] [-i infile] [-o outfile]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h             Program usage and help.\n");
    printf("  -v             Print statistics of decoding to stderr.\n");
    printf("  -i infile      Input data to decode.\n");
    printf("  -o outfile     Output of decoded data.\n");
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
    bool ver = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': synop = true; break;
        case 'v': ver = true; break;
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

    //copys the file permisions
    struct stat statbuf;
    fstat(fileno(fi_File), &statbuf);
    fchmod(fileno(fo_File), statbuf.st_mode);

    //creates bm H to be used in matrix multiplication
    BitMatrix *H = bm_create(8, 4);
    for (uint32_t i = 0; i < 4; i++) {
        bm_set_bit(H, 4 + i, i);
    }
    for (uint32_t i = 0; i < 4; i++) {
        for (uint32_t j = 0; j < 4; j++) {
            if (i != j) {
                bm_set_bit(H, i, j);
            }
        }
    }

    //goes till end of file
    while (1) {
        //gets 2 bytes of file
        uint8_t firstNum = fgetc(fi_File);
        uint8_t secondNum = fgetc(fi_File);
        if (feof(fi_File)) { //if end of file break
            break;
        }
        byetesProc = byetesProc + 2;
        uint8_t msg_One;
        uint8_t msg_Two;
        int status_One = ham_decode(H, firstNum, &msg_One); //decode them
        int status_Two = ham_decode(H, secondNum, &msg_Two);
        fputc(pack_byte(lower_nibble(msg_Two), lower_nibble(msg_One)),
            fo_File); //put them back together and putc
        //global var increments for verbose
        if (status_One == -2) {
            uncorrected += 1;
        } else if (status_One == -1) {
            corrected += 1;
        }
        if (status_Two == -2) {
            uncorrected += 1;
        } else if (status_Two == -1) {
            corrected += 1;
        }
    }
    //V verbose, prints statistics of decoding process
    if (ver == true) {
        printf("\n");
        printf("Total bytes processed: %d\n", byetesProc);
        printf("Uncorrected errors: %d\n", uncorrected);
        printf("Corrected errors: %d\n", corrected);
        printf("Error rate: %f\n", (float) uncorrected / byetesProc);
    }
}
