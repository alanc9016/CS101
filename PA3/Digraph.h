/*********************************************
 *  Name: Alan Caro
 * ID: 1650010
 * Assignment Name:  Assignment 3
 **********************************************/

#ifndef ALCARO_DIGRAPH_H
#define ALCARO_DIGRAPH_H

#include "List.h"

#define UNVISITED 0
#define IN_PROGRESS 2
#define ALL_DONE 3
#define FOUND 4
#define NOTFOUND -1

typedef struct DigraphObj
{
    int numVertices; //order
    int numEdges; //size
    int* visited;
    int* distance;
    List neighbors[];
}DigraphObj;

typedef struct DigraphObj* Digraph;

List B;

/*** Constructors-Destructors ***/
Digraph newDigraph(int numVertices);
    // Returns a Digraph that points to a newly created DigraphObj representing a digraph which has
    // n vertices and no edges.

void freeDigraph(Digraph* pG);
    // Frees al dynamic memory associated with its Digraph* argument, and sets
    // *pG to NULL.

/*** Access functions ***/
int getOrder(Digraph G);
    // Returns the order of G, the number of vertices in G.

int getSize(Digraph G);
    // Returns the size of G, the number of edges in G.

int getOutDegree(Digraph, int u);
    // Returns the number of outgoing neighbors that vertex u has in G, the number of vertices v such
    // that (u,v) is an edge in G. Returns -1 if v is not a legal vertex.

int getInDegree(Digraph G, int u);

List getNeighbors(Digraph G, int u);
    // Returns a list that has all the vertices that are outgoing neighbors of vertex u, i.e.,
    // a list that has all the vertices v such that (u, v) is as edge in G.
    // There is no input operation  that corresponds to getNeighbors.

/*** Manipulation procedures ***/

int addEdge(Digraph G, int u, int v);
    // Adds v to the adjacency list of u, if that edge doesn't already exist.
    // If the edge does already exist, does nothing. Used when edges are entered or added.
    // Returns 0 if (u, v) us a legal edge, and the edge didn't already exist.
    // Returns 1 if (u, v) is a legal edge and the edge did already exist.
    // Returns -1 if (u, v) is not a legal edge.

int deleteEdge(Digraph G, int u, int v);
    // Deleted v from the adjacency list of u, if that edge exists.
    // If the edge doesn't exist, does nothing. Used when edges are deleted.
    // Returns 0 if (u, v) is a legal edge, and the edge did already exist.
    // Returns 1 if (u, v) is a legal edge ad the edge didn't already exist.
    // Returns -1 if (u, v) is not a legal edge.

void unvisitAll(Digraph G);
    // Marks all vertices of the graph as UNVISITED.

int getMark(Digraph G, int u);
    // Returns the mark for vertex u, which will be UNVISITED, IN_PROGRESS or ALL_DONE.

void setMark(Digraph G, int u, int theMark);
    // Sets the mark for vertex u to be theMark.
    // theMark must be UNVISITED, IN_PROGRESS, or ALL_DONE.

void resetDistance(Digraph G);
    // Sets all vertices distance to Infinity

/*** Other operations ***/
void printDigraph(FILE* out, Digraph G);
    // Outputs the digraph G in the same format as an input line, including the number of vertices
    // and the edges. The edges should be in sorted order, as described above.

void distance(FILE* out, Digraph G, int u, int v);
    // Outputs the distance between vertices u and v if there is a directed path between them in the
    // digraph. Otherwise, outputs INF.

int DFS_Test_Acyclic(Digraph G, int u);
    // Used to see if Graph is acyclic using DFS

void acyclic(FILE* out, Digraph G);
    // Outputs YES if the digraph is acyclic Otherwise, outputs NO.

void topoSort(FILE* out, Digraph G);
    // Outputs a topological sort of the digraph. If the digraph is not acyclic, outputs IMPOSSIBLE.

void sort(ListObj* L);
    // Keeps the destination of each vertex as a sorted List

#endif //ALCARO_DIGRAPH_H
