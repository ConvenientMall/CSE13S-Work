# Assignment 5: Hamming Codes
Jinsu Hwang  
jhwang39  
Spring 2021  

-----------
## DESCRIPTION  

A Hamming(8, 4) systematic code generator and Hamming (8,4) systematic code decoder.

-----------
## FILES

error.c  
entropy.h  
decode.c  
encode.c  
bv.{c, h}  
bm.{c, h}  
hamming.{c, h}  
globalvar.{c,h}  
Makefile  
-----------
## INSTRUCTIONS

To build: go to the directory with the above files and type "make" and press enter.

To run: go to the directory with "encode" and "decode" and type "./encode" or "./decode" and your desired command line arguments in the following format for encode 

"./encode [-h] [-i infile] [-o outfile]".

  -h             Program usage and help.  
  -i infile      Input data to encode  
  -o outfile     Output of encoded data  
  
 and the following format for decode  
 
 "./decode [-h] [-v] [-i infile] [-o outfile]".

  -h             Program usage and help.  
  -v             Print statistics of decoding to stderr.  
  -i infile      Input data to decode  
  -o outfile     Output of decoded data  
