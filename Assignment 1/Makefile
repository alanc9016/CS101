#------------------------------------------------------------------------------
# Makefile for CMPS 101-01 Programming Assignment 1
#
#       make                   makes InsertSortLinked
#       make ListClient        makes ListClient
#------------------------------------------------------------------------------

InsertSortLinked : InsertSortLinked.o List.o
	gcc -o InsertSortLinked InsertSortLinked.o List.o

InsertSortLinked.o : InsertSortLinked.c List.h
	gcc -c -std=c99 -Wall InsertSortLinked.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f InsertSortLinked ListClient InsertSortLinked.o ListClient.o List.o
