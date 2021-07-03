## Assignment 3: Sorting   
Jinsu Hwang  
jhwang39  
Spring 2021  

-----------
# DESCRIPTION  

The programs are a collection of sorts as well as a tester that creates arrays that the sorting algorithims sort through.

-----------
# FILES

bubble.{c, h}  
gaps.h  
shell.{c, h}  
quick.{c, h}  
stack.{c, h}  
queue.{c, h}  
set.{c,h}  
sorting.c  
Makefile  
DESIGN.pdf  
WRITEUP.pdf  

-----------
# INSTRUCTIONS

To build: go to the directory with the above files and type "make" and press enter

To run: go to the directory with "sorting" and type "./sorting" and your desired command line arguments in the following format "./sorting [-habsqQo] [-n length] [-p elements] [-r seed]".

   -h              Display program help and usage.  
   -a              Enable all sorts.  
   -b              Enable Bubble Sort.  
   -s              Enable Shell Sort.  
   -q              Enable Quick Sort (Stack).  
   -Q              Enable Quick Sort (Queue).  
   -n length       Specify number of array elements.  
   -p elements     Specify number of elements to print.  
   -r seed         Specify random seed.  
   -o              Use sorted arrays.  

