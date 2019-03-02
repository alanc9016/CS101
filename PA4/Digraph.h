/*********************************************
 *  Name: Alan Caro
 * ID: 1650010
 * Assignment Name:  Assignment 4
 **********************************************/

#ifndef ALCARO_DIGRAPH_H
#define ALCARO_DIGRAPH_H

#include "List.h"

#define UNVISITED 0
#define IN_PROGRESS 2
#define ALL_DONE 3
#define FOUND 4
#define NOTFOUND -1

List B;
List C;

typedef struct DigraphObj
{
    int numVertices; //order
    int numEdges; //size
    int* visited;
    List neighbors[];
}DigraphObj;

typedef struct DigraphObj* Digraph;

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

int getCountSCC(Digraph G);
    // Returns the number of Strongly Connected Components in G.

int getNumSCCVertices(Digraph G, int u);
    // Returns the number of vertices (including u) that are in the same Strongly Connected Component
    // as u in G. Returns -1 if u is not a legal vertex.

int intSameSCC(Digraph G, int u, int v);
    // Returns 1 if u and v are in the same Strongly Connected Component of G, and returns 0 if u and v
    // are not in the same Strongly Connected Component of the current digraph.
    // A vertex is always in the same Strongly Connected Component as itself.
    // Returns -1 if u is not a legal vertex.


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
    // Returns 1 if (u, v) is a legal edge and the edge didn't already exist.
    // Returns -1 if (u, v) is not a legal edge.

void unvisitAll(Digraph G);
    // Marks all vertices of the graph as UNVISITED.

int getMark(Digraph G, int u);
    // Returns the mark for vertex u, which will be UNVISITED, IN_PROGRESS or ALL_DONE.

void setMark(Digraph G, int u, int theMark);
    // Sets the mark for vertex u to be theMark.
    // theMark must be UNVISITED, IN_PROGRESS, or ALL_DONE.

void DFS(Digraph G, int w);

List getVisitOrder(Digraph G, int v);

Digraph reverseEdges(Digraph G);

/*** Other operations ***/
void printDigraph(FILE* out, Digraph G);
    // Outputs the digraph G in the same format as an input line, including the number of vertices
    // and the edges. The edges should be in sorted order, as described above.

void sort(ListObj* L);
    // Keeps the destination of each vertex as a sorted List

#endif //ALCARO_DIGRAPH_H
