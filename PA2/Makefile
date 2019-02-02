#------------------------------------------------------------------------------
# Makefile for CMPS 101-01 Programming Assignment 2
#
#       make                   makes GraphProperties
#------------------------------------------------------------------------------

GraphProperties : GraphProperties.o List.o Graph.o
	gcc -o GraphProperties GraphProperties.o List.o Graph.o

GraphProperties.o : GraphProperties.c List.h Graph.h
	gcc -c -std=c99 -Wall GraphProperties.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

Graph.o : Graph.c Graph.h
	gcc -c -std=c99 -Wall Graph.c

clean :
	rm -f GraphProperties GraphProperties.o List.o Graph.o
