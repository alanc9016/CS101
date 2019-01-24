/*********************************************
 *  Name: Alan Caro
 * ID: 1650010
 * Assignment Name:  Assignment 1
 **********************************************/

#ifndef ALCARO_LIST_H
#define ALCARO_LIST_H

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


typedef struct NodeObj
{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj
{
    NodeObj* head;
    NodeObj* tail;
    int size;
}ListObj;

typedef ListObj* List;

// Constructors-Destructors -------------------------------------------------------------------
List newList(void);         // returns a List which points to a new empty list object

void freeList(List *pL);         // frees all the heap memory associated with its List* argument,
                                // and sets *pL to NULL

// Access functions ----------------------------------------------------------------------------

int length(List L);            // Returns the number of nodes in this List.

int frontValue(List L);        // Returns the integer in the front Node.
                                // Precondition: L has at least one Node on it.

int backValue(List L);         // Returns the integer in the back Node.
                                // Precondition: L has at least one Node on it.

int getValue(Node N);       // Returns the integer in Node N.
                                // Precondition: N is not NULL

int equals(List A, List B);   // Returns 1 if List A and List B are the same integer
                                // sequence, otherwise returns 0.

void clear(List L);            // Resets this List to the empty state.

Node getFront(List L);     // If List is non-empty, returns the front Node, without
                                // changing the List. Otherwise, does nothing.

Node getBack(List L);      // If List is non-empty, returns the back Node, without
                                // changing the List. Otherwise, does nothing

Node getPrevNode(Node N);    // Without changing any values, makes Node N reference
                                // the previous Node on its List. If there is no
                                // previous Node, sets N to NULL.

Node getNextNode(Node N);    // Without changing any values, makes Node N reference
                                // the next Node on its List. If there is no
                                // next Node, sets N to NULL.

void prepend(List L, int data);    // Inserts a new Node into List L before the front
                                    // Node that has data as its value. If List is empty,
                                    // makes that new Node the only Node on the list.

void append(List L, int data); // Inserts a new Node into List L after the back
                                // Node that has data as its value. If List is empty,
                                // makes that new Node the only Node on the list.

void insertBefore(List L, Node N, int data);    // Inserts a new Node into Node N's list before
                                            // Node N that has data as its value.
                                            // Precondition: Node N is not NULL

void insertAfter(List L, Node N, int data);     // Inserts a new Node into Node N's list after
                                            // Node N that has data as its value.
                                            // Precondition: Node N is not NULL

void deleteFront(List L);                  // Deletes the front Node in List L.
                                            // Precondition: L has at least one Node on it.

void deleteBack(List L);                   // Deletes the back Node in List L.
                                            // Precondition: L has at least one Node on it.

void detachNode(List L, Node N);       // Removes N from the List L by making the Node before
                                            // Node N link to the Node that's after Node N as its
                                            // next Node, and making the Node after Node N link to
                                            // the Node that's before Node N as its previous Node.
                                            //
                                            // After detachNode, Node N should have NULL as both its
                                            // next and previous Node.
                                            //
                                            // Special cases:
                                            //
                                            // If Node N is the front of the List L, then the Node after
                                            // Node N becomes the front of List L, which should have
                                            // a NULL previous Node.
                                            // If Node N is the back of List L, then the Node before
                                            // Node N becomes the back of List L, which should have
                                            // a NULL next Node.
                                            //
                                            // Precondition: N is a Node that's on List L.

// Other operations ----------------------------------------------------------------------

void printList(FILE* out, List L);         // Prints the values in List L from front to back
                                            // to the file pointed to by out, formatted as a
                                            // space-separated string.
                                            // For those familiar with Java, this is similar
                                            // to toString() in Java.


#endif //ALCARO_LIST_H
