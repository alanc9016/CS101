/*********************************************
 *  Name: Alan Caro
 * ID: 1650010
 * Assignment Name:  Assignment 1
 **********************************************/

#include "List.h"
#include <limits.h>
void InsertionSort(ListObj* L);

int main(int argc, char* argv[])
{
    FILE *in, *out;
    char line[128];

    if(argc != 3)
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if(in == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    if(out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    ListObj* A = newList();
    while(fgets(line, sizeof(line), in) != NULL)
    {
        int a, b, c;

        if (sscanf(line, "%d %d %d", &a, &b, &c) == 3)
        {
            append(A,a);
            append(A,b);
            append(A,c);
        }


        InsertionSort(A);
        printList(out, A);
        freeList(A);
        A = newList();
    }

    freeList(A);
    fclose(in);
    fclose(out);

    return 0;
}

void InsertionSort(ListObj* L)
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


