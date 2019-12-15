//Mythili Karra
////mmkarra
////CMPS 101
////May 27, 2019
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main (int argc, char* argv[]) {
	FILE *in;
	FILE *out;
	int size;
	int x;
	int y;
	int source;
	int destination;
	
if (argc != 3) {
		printf("Usage: File one, File two\n");
		exit(1);
	}
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if (in == NULL) {
		printf("Cannot open file %s for reading.\n", argv[1]);
		exit(1);
	} if (out == NULL) {
		printf("Cannot open file %s for writing.\n", argv[2]);
		exit(1);
	}
	fscanf(in, "%d", &size);
	Graph G = newGraph(size);
	while (fscanf(in, "%d %d", &x, &y) == 2) {
		if (x == 0 && y == 0) {
			 break;
		}
		addEdge(G,x,y);
	}
	printGraph(out, G);

	List L = newList();
	while (fscanf(in, "%d %d", &source, &destination)) {
		if (destination == 0 && source == 0){
			break;
		}
		BFS(G, source);
		getPath(L, G, destination);
		int d = getDist(G, destination);
		if (d == -1) {
			fprintf(out, "\nThe distance from %d to %d is infinity \n", source, destination);
			fprintf(out, "No %d-%d path exists\n", source, destination);
		}
		else {
			fprintf(out, "\nThe distance from %d to %d is %d \n", source, destination, d);
			fprintf(out, "A shortest %d-%d path is: ", source, destination);
			printList(out, L);
			fprintf(out, "\n");
		}
		clear(L);
	}
	freeList(&L);
	freeGraph(&G);

	fclose(in);
	fclose(out);

}
