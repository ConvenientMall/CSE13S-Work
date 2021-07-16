#Assignment 4: The Circummnavigations of Denver Long
Jinsu Hwang  
jhwang39  
Spring 2021  

-----------
##DESCRIPTION  

Traveling Salesman Problem using DFS and utilizes graphs, paths, and stacks. 

-----------
##FILES

vertices.h  
graph.{c, h}  
stack.{c, h}  
path.{c, h}  
globalvar.{c,h}  
tsp.c  

-----------
##INSTRUCTIONS

To build: go to the directory with the above files and type "make" and press enter

To run: go to the directory with "tsp" and type "./tsp" and your desired command line arguments in the following format "./tsp [-u] [-v] [-h] [-i infile] [-o outfile]".

  -u             Use undirected graph.  
  -v             Enable verbose printing.  
  -h             Program usage and help.  
  -i infile      Input containing graph (default: stdin)  
  -o outfile     Output of computed path (default: stdout)  

