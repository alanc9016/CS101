/*********************************************
 *  Name: Alan Caro
 * ID: 1650010
 * Assignment Name:  Assignment 2
 **********************************************/

#include <malloc.h>
#include "Graph.h"
#include "List.h"
#include <unistd.h>
#include <sys/types.h>

Graph newGraph(int numVertices)
{
    GraphObj* G = malloc(sizeof(GraphObj)  + (numVertices * sizeof(ListObj)) + (numVertices * sizeof(int)));
    G->numVertices = numVertices;
    G->visited = malloc(sizeof(int) + (numVertices * sizeof(ListObj)));
    G->numEdges = 0;

    for(int i = 0; i <= G->numVertices; i++)
    {
        G->neighbors[i] = newList();
        G->visited[i] = UNVISITED;
    }

    return G;
}

void freeGraph(Graph* pG)
{
    for(int i = 0; i <= (*pG)->numVertices; i++)
        freeList(&(*pG)->neighbors[i]);

    free((*pG)->visited);
    free(*pG);
}

int getOrder(Graph G)
{
    return G->numVertices;
}

int getSize(Graph G)
{
    return G->numEdges;
}

int getNeighborCount(Graph G, int v)
{
    if(v > G->numVertices)
        return -1;

    return G->neighbors[v]->size;
}

List getNeighbors(Graph G, int v)
{
    return G->neighbors[v];
}

int addEdge(Graph G, int u, int v)
{
    NodeObj* head = G->neighbors[u]->head;

    while(head != NULL)
    {
        if(head->data == v)
            return -1;

        head = getNextNode(head);
    }

    append(G->neighbors[u],v);
    append(G->neighbors[v],u);

    G->numEdges++;

    return 0;
}

void unvisitAll(Graph G)
{
    for(int i = 0; i <= G->numVertices; i++)
        G->visited[i] = UNVISITED;
}

int getMark(Graph G, int u)
{
    return G->visited[u];
}

void setMark(Graph G, int u, int theMark)
{
    G->visited[u] = theMark;
}

int pathExistsRecursive(Graph G, int w, int v)
{
    int theMark;
    int theFoundValue = NOTFOUND;

    if(w == v)
        return FOUND;
    setMark(G,w,IN_PROGRESS);


    List A = getNeighbors(G,w);
    NodeObj* head = A->head;

    while(head != NULL)
    {
        theMark = getMark(G,head->data);
        if(theMark == UNVISITED)
            theFoundValue = pathExistsRecursive(G,head->data,v);
        if(theFoundValue == FOUND)
            return FOUND;
        head = getNextNode(head);
    }


    setMark(G,w,ALL_DONE);
    return NOTFOUND;

}

void printGraph(FILE* out, Graph G)
{
    fprintf(out, "%d, ", G->numVertices);

    for(int i = 0; i <= G->numVertices; i++)
    {
        prepend(G->neighbors[i],i);
        NodeObj* head = G->neighbors[i]->head;
        NodeObj* temp = G->neighbors[i]->head->next;

        while(temp != NULL)
        {
            if(head->data < temp->data)
            {
                if(i+2 > G->numVertices && temp->next == NULL)
                    fprintf(out, "%d %d ", head->data, temp->data);
                else
                    fprintf(out, "%d %d, ", head->data, temp->data);
            }
            temp = getNextNode(temp);
        }
        deleteFront(G->neighbors[i]);
    }
}