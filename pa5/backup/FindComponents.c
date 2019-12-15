#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
#define MAX_LEN 255

int main(int argc, char* argv[]) {
	FILE *in, *out;
	if(argc != 3) {
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in == NULL) {
		fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
		exit(EXIT_FAILURE);	
	}

	if(out == NULL) {
		fprintf(stderr, "Unable to open file %s for writingn\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	char l[MAX_LEN];
	fgets(l, MAX_LEN, in);
	int x = 0;
	sscanf(l, "%d", &x);
	Graph g = newGraph(x);
	List list = newList();
	for(int i = 1; i < x + 1; i++){
		append(list, i);
	}


	while(fgets(l, MAX_LEN, in) != NULL){
		int a = 0;
		int b = 0;
		sscanf(l, "%d %d", &a, &b);
		if (a == 0 && b == 0){
			break;
		}
		addArc(g, a, b);
	}	

	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, g);
	fprintf(out, "\n");
	DFS(g, list);
	Graph t = transpose(g);
	DFS(t, list);

	int stronglyconnected = 0;
	for(int i = 1; i < getOrder(t) + 1; i++){
		if(getParent(t, i) == 0) {
			stronglyconnected++;
		}
	}
	fprintf(out, "G contains %d strongly connected components:\n", stronglyconnected);

	List temp = newList();
	moveBack(list);

	int q = 1;
	while(index(list) != -1){
		int num = get(list);
		prepend(temp, num);
		if(getParent(t, num) == 0){
			fprintf(out, "Component %d: ", q);
			printList(out, temp);
			fprintf(out,"\n");
			clear(temp);
			q++;
		}
		movePrev(list);
	}



	freeGraph(&g);
	freeGraph(&t);
	freeList(&list);
	fclose(in);
	fclose(out);

}
