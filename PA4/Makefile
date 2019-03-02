#------------------------------------------------------------------------------
# Makefile for CMPS 101-01 Programming Assignment 4
#
#       make                   makes DigraphProperties
#------------------------------------------------------------------------------

DigraphProperties : DigraphProperties.o List.o Digraph.o
	gcc -o DigraphProperties DigraphProperties.o List.o Digraph.o

GraphProperties.o : DigraphProperties.c List.h Digraph.h
	gcc -c -std=c99 -Wall DigraphProperties.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

Graph.o : Digraph.c Digraph.h
	gcc -c -std=c99 -Wall Graph.c

clean :
	rm -f DigraphProperties DigraphProperties.o List.o Digraph.o
