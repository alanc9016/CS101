//
//  ListClient.c
//  
//
//  Created by Jayanth Yetukuri on 1/21/19.
// Email me(jyetukur@ucsc.edu) if you have any concerns on this file
//

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
    
    List A = newList();
    List A_A = newList();
    List B = newList();
    List C = newList();
    
    int a[]={1,2,3,4,5,6,7,8,9};
    int a_a[]={1,2,3,4,5,6,7,8,9};
    int b[]={8,9,10,11,12,13,14};

    int i;
    
    for(i=0; i<9;  i++) append(A, a[i]);
    for(i=0; i<9; i++) append(A_A, a_a[i]);
    for(i=0; i<7;  i++) prepend(B, b[i]);
    
    for(i=0;i<15; i++){
        append(C, i);
        prepend(C, i);
    }
    
    printf("Length of A: %d\n", length(A));
    printf("Front element of A: %d\n", getValue(getFront(A)));
    printf("Second element of A: %d\n", getValue(getNextNode(getFront(A))));
    printf("New Front element of A: %d\n", frontValue(A));
    insertBefore(A, getFront(A), -1);
    insertAfter(A, getFront(A), -2);
    printf("Front element of A: %d\n", frontValue(A));
    
    printf("Length of A: %d\n", length(A));
    printf("Last element of A: %d\n", getValue(getBack(A)));
    printf("Second to last element of A: %d\n", getValue(getPrevNode(getBack(A))));
    printf("New Last element of A: %d\n", backValue(A));
    insertBefore(A, getBack(A), -3);
    insertAfter(A, getBack(A), -4);
    printf("Last element of A: %d\n", backValue(A));
    
    printf("Length of A: %d\n", length(A));
    printf("A compared to A: %d\n", equals(A, A));
    printf("A compared to A_A: %d\n", equals(A, A_A));
    printf("A compared to B: %d\n", equals(A, B));

    
    printList(stdout,A); printf("\n");
    printList(stdout,A_A); printf("\n");
    printList(stdout,B); printf("\n");
    printList(stdout,C); printf("\n");
    
    length(A);
    freeList(&A);
    freeList(&A_A);
    freeList(&B);
    freeList(&C);
    
    return(0);
}
