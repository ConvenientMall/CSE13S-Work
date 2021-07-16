#include "io.h"

#include "code.h"
#include "globalvar.h"

#include <assert.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

//wrapper function that calls read()
//does it untill nbytes are read.
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int total = 0;
    int bytes = 0;
    while (bytes > 0 || total != nbytes) {
        bytes = read(infile, buf, nbytes - total);
        total += bytes;
        if (bytes == 0) {
            return total;
        }
    }
    return total;
}

//wrapper function that calls write()
//writes until total = nbytes or no more bytes to read
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int total = 0;
    int bytes = 0;
    while (bytes > 0 || total != nbytes) {
        bytes = write(outfile, buf, nbytes - total);
        total += bytes;
    }
    return total;
}

static uint8_t write_Buff[BLOCK]; //write buffer for write_code()
static int buffer_Index = 0; // index for write buffer
static uint8_t bit_Buffer = 0; // bit buffer for read_bit
static int bit_Index = 0; // bit index for read bit

//read bits until empty golding values in
//bit buffer and bit index
bool read_bit(int infile, uint8_t *bit) {
    if (bit_Index % 8 == 0) {
        int c = read_bytes(infile, &bit_Buffer, 1);
        bytesDe += 1;
        if (c == 0) {
            return false;
        }
    }
    *bit = (bit_Buffer >> (((bit_Index) % 8)) & 1);
    bit_Index += 1;
    return true;
}

//writes the code used in encoder
void write_code(int outfile, Code *c) {
    // need to buffer bits
    // when buffer is full
    // write out entire buffer.
    for (uint32_t i = 0; i < c->top; i++) {
        if ((c->bits[i / 8] >> (i % 8) & 1) == 1) {
            write_Buff[buffer_Index / 8]
                = write_Buff[buffer_Index / 8] | (1 << buffer_Index % 8); //set bit
        } else {
            write_Buff[buffer_Index / 8]
                = write_Buff[buffer_Index / 8] & ~(1 << buffer_Index % 8); //clr bit
        }
        buffer_Index += 1;
        if (buffer_Index == BLOCK * 8) {
            write_bytes(outfile, write_Buff, BLOCK);
            bytesEn += BLOCK;
            buffer_Index = 0;
        }
    }
}
//when flushed writes the rest stores in write buffer
void flush_codes(int outfile) {
    if (buffer_Index % 8 - 1 != 0) {
        write_Buff[buffer_Index / 8] = write_Buff[buffer_Index / 8] & ~(1 << buffer_Index % 8);
        buffer_Index += 1;
    }
    int nbytes = (buffer_Index) / 8;
    write_bytes(outfile, write_Buff, nbytes + 1);
    bytesEn += nbytes;
}
