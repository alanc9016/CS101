# Assignment 3

##### Table of Contents  
- [GraphProperties.c](#DigraphProperties.c)
- [List.c](#List.c)
- [List.h](#List.h)
- [Digraph.c](#Digraph.c)
- [Digraph.h](#Digraph.h)
- [Makefile](#Makefile)
 
<a name="GraphProperties.c"></a>
### DigraphProperties.c
- Uses operations from Digraph.c and List.c to manipulate a Digraph and print it to a file.

<a name="List.c"></a>
### List.c
- Implementation file that contains the list ADT module. 

<a name="List.h"></a>
### List.h
- Header file that contains List function declarations.

<a name="Graph.c"></a>
### Digraph.c
-  Implementation file that contains the Digraph ADT module.

<a name="List.h"></a>
### Digraph.h
-   Header file that contains Digraph function declarations.

<a name="Makefile"></a>
### Makefile
- Will create an executable called DigraphProperties includes a clean  utility that removes all object files, including DigraphProperties. 

## Instructions
- make makes DigraphProperties
- ./DigraphProperties input.txt output.txt

## DigraphObj Extra Fields
- distance: Keeps track of the distances from u to v. If another node (x) is in the way from u to v, I save this distance in index x. 

## Distance
- BFS starting at u. If node is unvisited save distances in distance array. Queue operations take O(V) since we go though all the graph. Then going through each list is O(E). Hence O(V + E).

## Acyclic
- Calls DFS_Test_Acyclic for every vertex O(V) and it iterates through the list O(E), hence O(V+E). DFS_Test_Acyclic performs DFS on graph if it encounters a node IN_PROGRESS returns 1 (indicating a cycle)

## topoSort
- Calls DFS_Test_Acyclic (to test for cycles) for every vertex O(V) and it iterates through the list O(E), hence O(V+E). In DFS_Test_Acyclic I eventually put all vertices that don't depend on other vertices in a stack then print the stack.

## Author
- **Alan Caro** 
