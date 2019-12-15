#------------------------------------------------------------------------------
# Makefile for CMPS 101 Programming Assignment 2
#
#       make                   makes Lex
#       make ListClient        makes ListClient
#//Mythili Karra
#//mmkarra
#//CS101
#//04/18/2019
#------------------------------------------------------------------------------
Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o
submit: List.h Lex.c List.c README Makefile ListClient.c
	submit cmps101-pt.s19 pa2 List.h Lex.c List.c README Makefile ListClient.c

