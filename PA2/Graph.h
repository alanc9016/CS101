/*********************************************
 *  Name: Alan Caro
 * ID: 1650010
 * Assignment Name:  Assignment 2
 **********************************************/

#ifndef ALCARO_GRAPH_H
#define ALCARO_GRAPH_H

#include "List.h"

#define UNVISITED 0
#define IN_PROGRESS 2
#define ALL_DONE 3
#define FOUND 4
#define NOTFOUND -1

typedef struct GraphObj
{
    int numVertices; //order
    int numEdges; //size
    int* visited;
    List neighbors[];
}GraphObj;

typedef GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int numVertices);
// Returns a Graph that points to a newly created GraphObj representing a graph which has
// n vertices and no edges.

void freeGraph(Graph* pG);
// Frees all dynamic memory associated with its Graph* argument, and sets
// *pG to NULL.

/*** Acess functions ***/
int getOrder(Graph G);
// Returns the size of G, the number of edges in G.

int getSize(Graph G);
// Returns the size of G, the number of edges in G.

int getNeighborCount(Graph G, int v);
// Returns the number of neighbors that vertex v has in G. Returns -1 if v is not a legal vertex.

List getNeighbors(Graph G, int v);
// Returns a list that has all the vertices that are neighbors of u. There is no input operation
// that corresponds to getNeighbors.

/*** Manipulation procedures ***/
int addEdge(Graph G, int u, int v);
// Adds v to the adjacency list of u and u to the adjacency list of v, if that edge doesn’t
// already exist.  If the edge does already exist, does nothing.  Used when edges are entered.
// Returns 0 if u and v are legal vertices, otherwise returns -1.

void unvisitAll(Graph G);
//marks all vertices of the graph as UNVISITED.

int getMark(Graph G, int u);
// Returns the mark for vertex u, which will be UNVISITED, IN_PROGRESS or ALL_DONE.

void setMark(Graph G, int u, int theMark);
// Sets the mark for vertex u to be theMark.
// theMark must be UNVISITED, IN_PROGRESS, or ALL_DONE.

int pathExistsRecursive(Graph G, int w, int v);
// Described below; returns FOUND or NOTFOUND which are (different) constants.

/*** Other operations ***/
void printGraph(FILE* out, Graph G);
// Prints the Graph G in the same format as an input line, so all that a client need to do is a single
// call to PrintGraph(). But it should not print out an edge twice. Achieve this by only printing
// the edge for {j,k} when j < k.



#endif //ALCARO_GRAPH_H
