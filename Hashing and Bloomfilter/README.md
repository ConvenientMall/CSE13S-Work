##Assignment 7: Bloom Filters, Linked Lists and Hash Tables
Jinsu Hwang  
jhwang39  
Spring 2021  

-----------
#DESCRIPTION  

A word filtering program for the GPRSC. Filters out and reports bad words parsed from stdin. Uses bloom filter, linked lists and hash tables.
  
-----------
#FILES

banhammer.c  
messages.h  
speck.{c, h}  
ht.{c,h}  
bv.{c, h}  
ll.{c, h}  
node.{c, h}  
bf.{c,h}  
parser.{c, h}  
Makefile  
DESIGN.pdf  
WRITEUP.pdf
  
-----------
#INSTRUCTIONS

To build: go to the directory with the above files and type "make" and press enter.

To run: go to the directory with "banhammer" and type "./banhammer" and your desired command line arguments in the following format for banhammer.

"./banhammer  [-hsm] [-t size] [-f size]".

  -h           Program usage and help.  
  -s           Print program statistics.  
  -m           Enable move-to-front rule.  
  -t size      Specify hash table size (default: 10000).  
  -f size      Specify Bloom filter size (default: 2^20).  
