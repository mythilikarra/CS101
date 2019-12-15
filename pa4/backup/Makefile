#//Mythili Karra
#//mmkarra
#//CMPS 101
#//May 27, 2019
BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

ModelGraphTest : ModelGraphTest.o $(BASE_OBJECTS)
	$(LINK) ModelGraphTest ModelGraphTest.o $(BASE_OBJECTS)

FindPath : FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

ModelGraphTest.o : ModelGraphTest.c $(HEADERS)
	$(COMPILE) ModelGraphTest.c

FindPath.o : FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) ModelGraphTest FindPath GraphClient ModelGraphTest.o FindPath.o GraphClient.o $(BASE_OBJECTS)

checkFind : FindPath
	$(MEMCHECK) FindPath in3 junk3

checkClient : GraphClient
	$(MEMCHECK) GraphClient

submit: List.h FindPath.c List.c README Makefile Graph.c Graph.h GraphClient.c
	submit cmps101-pt.s19 pa4 List.h FindPath.c List.c README Makefile Graph.h GraphClient.c Graph.c

