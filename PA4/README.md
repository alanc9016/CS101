# Assignment 4

##### Table of Contents  
- [DigraphProperties.c](#DigraphProperties.c)
- [List.c](#List.c)
- [List.h](#List.h)
- [Digraph.c](#Digraph.c)
- [Digraph.h](#Digraph.h)
- [Makefile](#Makefile)
 
<a name="DigraphProperties.c"></a>
### DigraphProperties.c
- Uses operations from Digraph.c and List.c to manipulate a Digraph and print it to a file.

<a name="List.c"></a>
### List.c
- Implementation file that contains the list ADT module. 

<a name="List.h"></a>
### List.h
- Header file that contains List function declarations.

<a name="Digraph.c"></a>
### Digraph.c
-  Implementation file that contains the Digraph ADT module.

<a name="Digraph.h"></a>
### Digraph.h
-   Header file that contains Digraph function declarations.

<a name="Makefile"></a>
### Makefile
- Will create an executable called DigraphProperties includes a clean  utility that removes all object files, including DigraphProperties. 

## DigraphObj Extra Fields
- SCC: List that contains all the SCCs the Digraph has.
- SCCCount: Stores the number of SCCs the Digraph has.
      
## Instructions
- make makes DigraphProperties
- ./DigraphProperties input.txt output.txt

## Data Structures Used
- Used three list, one to build a Directed Graph, another to store the path of vertices, and one to store all the SCCs. This way I only have to recalculate the SCCs after a call to some SCC function and addEdge or deleteEdge were successful before the call. 

## Author
- **Alan Caro** 
