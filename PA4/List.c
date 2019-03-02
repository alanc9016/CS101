/*********************************************
 *  Name: Alan Caro
 * ID: 1650010
 * Assignment Name:  Assignment 4
 **********************************************/

#include "List.h"

Node createNode(int data)
{
    NodeObj* node = malloc(sizeof(NodeObj));
    node->next = NULL;
    node->prev = NULL;
    node->data = data;
    return node;
}

List newList(void)
{
    ListObj* L = malloc(sizeof(ListObj));
    L->head = NULL;
    L->tail = NULL;
    L->size = 0;
    return L;
}

void freeList(List *pL)
{
    clear(*pL);
    free(*pL);
}

int length(List L)
{
    return L->size;
}

int frontValue(List L)
{
    if(length(L) == 0)
    {
        printf("LCan't get Front since List is Empty!");
        exit(1);
    }
    else
    {
        return L->head->data;
    }
}

int backValue(List L)
{
    if(length(L) == 0)
    {
        printf(" Can't get Back Value Since List is Empty!");
        exit(1);
    }
    else
    {
        return L->tail->data;
    }
}

int getValue(Node N)
{
    if(N == NULL)
    {
        printf("Node Doesn't Exist!\n");
        exit(1);
    }

    return N->data;
}

int equals(List A, List B)
{
    NodeObj* headA = A->head;
    NodeObj* headB = B->head;

    while(headA != NULL && headB != NULL)
    {
        if(headA->data != headB->data)
            return 0;

        headA = headA->next;
        headB = headB->next;

        if(headA == NULL && headB != NULL)
            return 0;
        if(headA != NULL && headB == NULL)
            return 0;
    }

    return 1;
}

void clear(List L)
{
    while(length(L) != 0)
    {
        deleteFront(L);
    }
}

Node getFront(List L)
{
    if(L->size == 0)
    {
        printf(" Can't get Front since list is Empty!\n");
        exit(1);
    }
    else
        return L->head;
}

Node getBack(List L)
{
    if(L->size == 0)
    {
        printf("Can't get Back since list is Empty!\n");
        exit(1);
    }
    else
        return L->tail;
}

Node getPrevNode(Node N)
{
    if(N->prev == NULL)
        N = NULL;
    else
        N = N->prev;

    return N;
}

Node getNextNode(Node N)
{
    if(N->next == NULL)
        N = NULL;
    else
        N = N->next;

    return N;
}

void prepend(List L, int data)
{
    NodeObj* node = createNode(data);

    if(L->size == 0)
    {
        L->head = node;
        L->tail = node;
    }
    else
    {
        node->next = L->head;
        L->head->prev = node;
        L->head = node;
    }

    L->size++;
}

void append(List L, int data)
{
    NodeObj* node = createNode(data);

    if(L->size == 0)
    {
        L->head = node;
        L->tail = node;
    }
    else
    {
        node->prev = L->tail;
        L->tail->next = node;
        L->tail = node;
    }

    L->size++;
}

void insertBefore(List L, Node N, int data)
{
    NodeObj* new = createNode(data);

    if(N->next == NULL && N->prev != NULL)
    {
        new->prev = N->prev;
        new->next = N;
        N->prev->next = new;
        N->prev = new;
    }
    else if(N->prev == NULL)
    {
        new->next = N;
        N->prev = new;
        L->head = new;
    }
    else
    {
        new->next = N;
        new->prev = N->prev;
        N->prev->next = new;
        N->prev = new;
    }


    L->size++;
}

void insertAfter(List L, Node N, int data)
{
    NodeObj* new = createNode(data);

    if(N->next == NULL)
    {
        N->next = new;
        new->prev = N;
        L->tail = new;
    }
    else
    {
        new->next = N->next;
        new->prev = N;
        N->next->prev = new;
        N->next = new;
    }

    L->size++;
}

void deleteFront(List L)
{
    NodeObj* head = L->head;

    if(head == NULL)
    {
        printf("(deletefront)List is Empty");
        exit(1);
    }
    else if(L->size == 1)
    {
        free(L->head);
        L->head = NULL;
        L->tail = NULL;
        L->size--;
        return;
    }
    else
    {
        NodeObj* temp = L->head;
        L->head = head->next;
        L->head->prev = NULL;
        free(temp);
        L->size--;
        return;
    }
}

void deleteBack(List L)
{
    if(L->head == NULL)
    {
        printf("(deleteBack)List is Empty!\n");
        exit(1);
    }
    else if(L->size == 1)
    {
        free(L->head);
        L->head = NULL;
        L->tail = NULL;
        L->size--;
        return;
    }
    else
    {
        L->tail = L->tail->prev;
        free(L->tail->next);
        L->tail->next = NULL;
        L->size--;
    }
}

void deleteNode(List L, int v)
{
    if(L->head == NULL)
    {
        printf("(deleteBack)List is Empty!\n");
        exit(1);
    }
    else if(L->size == 1)
    {
        free(L->head);
        L->head = NULL;
        L->tail = NULL;
        L->size--;
        return;
    }
    else if(L->tail->data == v)
    {
        deleteBack(L);
    }
    else if(L->head->data == v)
    {
        deleteFront(L);
    }
    else
    {
        NodeObj *t = L->head;

        while(t != NULL)
        {
            if(t->data == v)
            {
                detachNode(L, t);

                free(t);
                L->size--;
                return;
            }

            t = getNextNode(t);
        }
    }
}

void detachNode(List L, Node N)
{
    if(N == L->head)
    {
        L->head = N->next;
        N->next = NULL;
        L->head->prev = NULL;

    }
    else if(N == L->tail)
    {
        L->tail = N->prev;
        N->prev = NULL;
        L->tail->next = NULL;

    }
    else
    {
        N->prev->next = N->next;
        N->next->prev = N->prev;
        N->next = NULL;
        N->prev = NULL;
    }

}

int search(List L, int u)
{
    NodeObj* head = L->head;

    while(head != NULL)
    {
        if(head->data == u)
            return 1;

        head = getNextNode(head);
    }

    return -1;
}

void printList(FILE* out, List L)
{
    NodeObj* head = L->head;

    if(L->head == NULL)
    {
        printf("Can't print List since it's empty");
        exit(1);
    }
    else
    {
        while(head != NULL)
        {
            fprintf(out,"%d ", head->data);
            head = getNextNode(head);
        }
        fprintf(out,"\n");
    }
}