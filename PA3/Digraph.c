/*********************************************
 *  Name: Alan Caro
 * ID: 1650010
 * Assignment Name:  Assignment 3
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
    G->distance = malloc(sizeof(int) + (numVertices * sizeof(ListObj)));

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
    free((*pG)->distance);
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

void resetDistance(Digraph G)
{
    for(int i = 1; i <= G->numVertices; i++)
        G->distance[i] = INT_MAX;
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

void distance(FILE* out, Digraph G, int u, int v)
{
    unvisitAll(G);
    resetDistance(G);

    setMark(G,u,IN_PROGRESS);
    G->distance[u] = 0;
    List Q = newList();
    append(Q,u);

    while(length(Q) != 0)
    {
        int x = Q->head->data;
        deleteFront(Q);

        for(NodeObj* w = getNeighbors(G, x)->head; w != NULL; w = getNextNode(w))
        {
            if(getMark(G,w->data) == UNVISITED)
            {
                setMark(G,w->data, IN_PROGRESS);
                G->distance[w->data] = G->distance[x] + 1;
                append(Q, w->data);
            }
        }

        setMark(G,x,ALL_DONE);
    }

    freeList(&Q);

    if(G->distance[v] == INT_MAX)
        fprintf(out,"INF");
    else
        fprintf(out,"%d",G->distance[v]);
}

int DFS_Test_Acyclic(Digraph G, int u)
{
    setMark(G,u,IN_PROGRESS);

    for(NodeObj* v = getNeighbors(G,u)->head; v != NULL; v = getNextNode(v))
    {
        if(getMark(G,v->data) == IN_PROGRESS)
            return 1;
        if(getMark(G,v->data) == UNVISITED)
        {
            if(DFS_Test_Acyclic(G, v->data))
                return 1;
        }
    }

    prepend(B, u);
    setMark(G,u,ALL_DONE);

    return 0;
}

void acyclic(FILE* out, Digraph G)
{
    unvisitAll(G);

    for(int i = 1; i <= G->numVertices; i++)
    {
        if(DFS_Test_Acyclic(G, i))
        {
            fprintf(out, "NO");
            return;
        }
    }

   freeList(&B);
   B = newList();

   fprintf(out, "YES");
}

void topoSort(FILE* out, Digraph G)
{
    unvisitAll(G);

    for(int i = 1; i <= G->numVertices; i++)
    {
        if(G->visited[i] == UNVISITED)
        {
            if(DFS_Test_Acyclic(G, i))
            {
                fprintf(out, "IMPOSSIBLE\n");
                return;
            }
        }
    }

    unvisitAll(G);

    for(int i = 1; i <= G->numVertices; i++)
        prepend(G->neighbors[i],i);

    for(int i = 1; i <= G->numVertices; i++)
    {
        if(getInDegree(G,i) == 1)
        {
            DFS_Test_Acyclic(G, i);
            break;
        }
    }

    printList(out, B);

    for(int i = 1; i <= G->numVertices; i++)
        deleteFront(G->neighbors[i]);
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