/*********************************************
 *  Name: Alan Caro
 * ID: 1650010
 * Assignment Name:  Assignment 4
 **********************************************/

#include <malloc.h>
#include <limits.h>
#include "Digraph.h"
#include "List.h"

Digraph newDigraph(int numVertices)
{
    DigraphObj* G = malloc(sizeof(DigraphObj)  + (numVertices * sizeof(ListObj)) + (numVertices * sizeof(int)));
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

void freeDigraph(Digraph* pG)
{
    for(int i = 0; i <= (*pG)->numVertices; i++)
        freeList(&(*pG)->neighbors[i]);

    free((*pG)->visited);
    free(*pG);
}


int getOrder(Digraph G)
{
    return G->numVertices;
}

int getSize(Digraph G)
{
    return G->numEdges;
}

int getOutDegree(Digraph G, int u)
{
    if(u > G->numVertices || u <= 0)
        return -1;

    return G->neighbors[u]->size;
}

int getInDegree(Digraph G, int u)
{
    if(u > G->numVertices || u <= 0)
        return -1;

    int inDeg = 0;

    for (int i = 1; i <= G->numVertices; i++)
    {
        List A = G->neighbors[i];
        NodeObj* head = A->head;

        while (head != NULL)
        {
            if (head->data == u)
                inDeg++;

            head = getNextNode(head);
        }
    }

    return inDeg;
}

List getNeighbors(Digraph G, int u)
{
    return G->neighbors[u];
}

int getCountSCC(Digraph G)
{
    int count = 0;

    unvisitAll(G);
    for(int i = 1; i<= G->numVertices; i++)
        if(getMark(G,i) == UNVISITED)
            getVisitOrder(G,i);

    Digraph gT = reverseEdges(G);
    unvisitAll(gT);

    while(length(B) != 0 )
    {
        int v = B->head->data;
        deleteFront(B);

        if(getMark(gT,v) == UNVISITED)
        {
            DFS(gT,v);
            count++;
        }
    }


    freeDigraph(&gT);
    return count;
}

int getNumSCCVertices(Digraph G, int u)
{
    unvisitAll(G);
    for(int i = 1; i<= G->numVertices; i++)
        if(getMark(G,i) == UNVISITED)
            getVisitOrder(G,i);

    Digraph gT = reverseEdges(G);
    unvisitAll(gT);

    while(length(B) != 0 )
    {
        int v = B->head->data;
        deleteFront(B);

        if(getMark(gT,v) == UNVISITED)
        {
            DFS(gT,v);

            if(search(C, u) == 1)
            {
                freeDigraph(&gT);
                return length(C);
            }

            freeList(&C);
            C = newList();
        }
    }

    freeDigraph(&gT);
    return -1;
}

int intSameSCC(Digraph G, int u, int v)
{
    unvisitAll(G);
    for(int i = 1; i<= G->numVertices; i++)
        if(getMark(G,i) == UNVISITED)
                getVisitOrder(G,i);

    Digraph gT = reverseEdges(G);
    unvisitAll(gT);

    while(length(B) != 0 )
    {
        int w = B->head->data;
        deleteFront(B);

        if(getMark(gT,w) == UNVISITED)
        {
            DFS(gT,w);

            if(search(C, u) == 1 && search(C, v) == 1)
            {
                freeDigraph(&gT);
                return 1;
            }

            freeList(&C);
            C = newList();
        }
    }

    freeDigraph(&gT);
    return 0;

}

int addEdge(Digraph G, int u, int v)
{
    if(u > G->numVertices|| v > G->numVertices)
        return -1;
    else if(u <= 0 || v <= 0)
        return -1;

    NodeObj* head = G->neighbors[u]->head;

    while(head != NULL)
    {
        if(head->data == v)
            return 1;

        head = getNextNode(head);
    }

    append(G->neighbors[u],v);
    sort(G->neighbors[u]);
    G->numEdges++;

    return 0;
}

int deleteEdge(Digraph G, int u, int v)
{
    if(u > G->numVertices|| v > G->numVertices)
        return -1;
    else if(u <= 0 || v <= 0)
        return -1;

    NodeObj* head = G->neighbors[u]->head;

    while(head != NULL)
    {
        if(head->data == v)
        {
            deleteNode(G->neighbors[u], v);
            G->numEdges--;
            return 0;
        }

        head = getNextNode(head);
    }

    return 1;
}

void unvisitAll(Digraph G)
{
    for(int i = 1; i <= G->numVertices; i++)
        G->visited[i] = UNVISITED;
}

int getMark(Digraph G, int u)
{
    return G->visited[u];
}

void setMark(Digraph G, int u, int theMark)
{
    G->visited[u] = theMark;
}

void DFS(Digraph G, int w)
{
    setMark(G,w, IN_PROGRESS);

    for(NodeObj* v = getNeighbors(G,w)->head; v != NULL; v = getNextNode(v))
    {
        if(getMark(G,v->data) == UNVISITED)
            DFS(G,v->data);
    }


    prepend(C, w);
    setMark(G,w,ALL_DONE);
}

List getVisitOrder(Digraph G, int u)
{
    setMark(G,u,IN_PROGRESS);

    for(NodeObj* v = getNeighbors(G,u)->head; v != NULL; v = getNextNode(v))
    {
        if(getMark(G,v->data) == UNVISITED)
            getVisitOrder(G, v->data);
    }

    prepend(B, u);
    setMark(G,u,ALL_DONE);

}

Digraph reverseEdges(Digraph G)
{
    Digraph g = newDigraph(G->numVertices);

    for(int i = 1; i <= G->numVertices; i++)
    {
        NodeObj* tail = G->neighbors[i]->tail;

        while(tail != NULL)
        {
            addEdge(g, tail->data, i);
            tail = getPrevNode(tail);
        }
    }

    return g;
}

void printDigraph(FILE* out, Digraph G)
{
    fprintf(out, "%d, ", G->numVertices);
    int j = 1;

    for(int i = 0; i <= G->numVertices; i++)
    {
        prepend(G->neighbors[i],i);
        NodeObj* head = G->neighbors[i]->head;
        NodeObj* temp = G->neighbors[i]->head->next;

        while(temp != NULL)
        {
            if(j < G->numEdges)
                fprintf(out, "%d %d, ", head->data, temp->data);
            else
                fprintf(out, "%d %d ", head->data, temp->data);
            j++;
            temp = getNextNode(temp);
        }
        deleteFront(G->neighbors[i]);
    }
}

void sort(ListObj* L)
{
    NodeObj* i;
    insertBefore(L, L->head, INT_MIN);
    for(NodeObj* j = L->head->next; j != NULL; j = j->next)
    {
        int key = j->data;
        i = j->prev;

        while(i != NULL && i->data > key)
        {
            i->next->data = i->data;
            i = i->prev;
        }

        i->next->data = key;
    }

    deleteFront(L);
}