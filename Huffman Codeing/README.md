# Assignment 6: Huffman Coding
Jinsu Hwang
jhwang39
Spring 2021

## DESCRIPTION
A huffman file compression program and a huffman compressed decoder program.

## FILES

• encode.c   
• decode.c  
• entropy.c  
• defines.h  
• header.h  
• node.h  
• node.c  
• pq.h  
• pq.c  
• code.h  
• code.c  
• io.h  
• io.c  
• stack.h  
• stack.c  
• huffman.h  
• huffman.c  

## INSTRUCTIONS
To build: go to the directory with the above files and type "make" and press enter.  
To run: go to the directory with "encode" and "decode" and type "./encode" or "./decode" and your desired command line arguments in the   following format for encode  

"./encode [-h] [-i infile] [-o outfile]".  
-h             Program usage and help.  
-v             Print compression statistics  
-i infile      Input file to compress  
-o outfile     Output of compressed data  

and the following format for decode  
"./decode [-h] [-v] [-i infile] [-o outfile]".  
-h             Program usage and help.  
-v             Print compression statistics  
-i infile      Input data to decompress  
-o outfile     Output of decompressed data  
