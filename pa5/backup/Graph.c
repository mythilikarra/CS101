//Mythili Karra
//////mmkarra
//////CMPS 101
//////May 27, 2019
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#define WHITE 1
#define GRAY 2
#define BLACK 3
#define INF -1
#define NIL 0
typedef struct GraphObj {
	List* lists;
	int* colors;
	//white = 1; gray = 2; black = 3
	int* parents;
	//null state is defined as 0
	int* discover;
	int* finish;
	//default is -1

	int order;
	int size;
	int source;

}GraphObj;

Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G -> order = n;
	G -> size = 0;
	G -> source = 0;
	G -> lists = malloc(sizeof(List)*(n+1));
	G -> colors = malloc(sizeof(int)*(n+1));
	G -> parents = malloc(sizeof(int)*(n+1));
	G -> discover = malloc(sizeof(int)*(n+1));
	G -> finish = malloc(sizeof(int)*(n+1));
	for(int i = 0; i<n+1; i++) {
		G -> lists[i] = newList();
		G -> colors[i] = 1;
		G -> parents[i] = 0;
		G -> discover[i] = -5;
		G -> finish[i] = -5;
	}
	return G;
}
void freeGraph(Graph *pG){
	for (int i=0; i<getOrder(*pG) + 1; i++){
		freeList(&(*pG)->lists[i]);
	}
	free((*pG)->lists);
	free((*pG)->parents);
	free((*pG)->discover);
	free((*pG)->finish);
	free((*pG)->colors);
	free(*pG);
	*pG = NULL;
}
int getOrder(Graph G) {
	return G -> order;
}
int getSize(Graph G) {
	return G -> size;
}
int getSource(Graph G) {
	return G-> source;
}

int getParent(Graph G, int u) {
	if (G == NULL){
		printf("getParent() Error: BFS has not been called");
		exit(EXIT_FAILURE);

	}
	else if( !(u >= 1) || !(u <= getOrder(G)) ) {
		exit(EXIT_FAILURE);
	}
	else {
		return G -> parents[u];
	}
}
int getDiscover(Graph G, int u) {
	if (G == NULL){
		printf("getDiscover() Error: BFS has not been called");
		exit(EXIT_FAILURE);
	}
	else if( !(u >= 1) || !(u <= getOrder(G)) ) {
		exit(EXIT_FAILURE);
	}
	return G -> discover[u];
}

int getFinish(Graph G, int u) {
	if (G == NULL){
		printf("getDiscover() Error: BFS has not been called");
		exit(EXIT_FAILURE);
	}
	else if( !(u >= 1) || !(u <= getOrder(G)) ) {
		exit(EXIT_FAILURE);
	}
	return G -> finish[u];


}

void addEdge(Graph G, int u, int v) {
	if (G == NULL){
		printf("addEdge() Error: BFS has not been called");
		exit(EXIT_FAILURE);

	}
	else if( !(u >= 1) || !(u <= getOrder(G)) ) {
		exit(EXIT_FAILURE);
	}
	moveFront( G -> lists[u]);
	while(index(G -> lists[u]) != -1 && get(G -> lists[u]) < v) {
		moveNext(G -> lists[u]);
	}
	if(index(G -> lists[u]) != -1) {
		insertBefore(G -> lists[u],v);
	}
	else {
		append(G -> lists[u],v);
	}

	moveFront(G -> lists[v]);
	while(index(G -> lists[v]) != -1 && get(G -> lists[v]) < u) {
		moveNext(G -> lists[v]);
	}

	if(index(G -> lists[v]) != -1) {
		insertBefore(G -> lists[v], u);
	}
	else {
		append(G -> lists[v], u);
	}
	G -> size++;
}
void addArc(Graph G, int u, int v) {
	if (G == NULL){
		printf("addArc() Error: BFS has not been called");
		exit(EXIT_FAILURE);

	}
	else if( !(u >= 1) || !(u <= getOrder(G)) ) {
		printf("addArc() Error");
		exit(EXIT_FAILURE);
	}
	moveFront(G -> lists[u]);
	while(index(G -> lists[u]) != -1 && get(G -> lists[u]) < v) {
		moveNext(G -> lists[u]);
	}
	if(index(G -> lists[u]) != -1) {
		insertBefore(G -> lists[u], v);
	}
	else {
		append(G -> lists[u], v);
	}
	G->size++;
}
int Visit(Graph G, List L, int u, int t);
void DFS(Graph G, List S) {
	int l;
	if(length(S) != getOrder(G)) {
		printf("rip");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < 1 + getOrder(G); i++) {
		G -> colors[i] = 1;
		G -> parents[i] = 0;
		//	G -> discover[i] = -5;
		//	G -> finish[i] = -5;
	}
	int time = 0;
	moveFront(S);
	for(int j = 1; j <= G -> order; j++) {
		//	while(index(S) != -1) {
		int x = get(S);
		if(G -> colors[x] == 1) {
			time = Visit(G,S,x,time);
		}
		moveNext(S);
	}
	//getting rid of half

	l = 0.5*length(S);
	printf("LEN %d", length(S));
	while(l>0) {
		deleteBack(S);
		l--;
	}

	}

	int Visit(Graph G, List L, int u, int t) {
		int x;
		//	(t)++;
		G -> discover[u] = ++t;
		G -> colors[u] = 2;
		moveFront(G -> lists[u]);
		//	for(int i = 0; i < length(G -> lists[u]); i++) {
		while(index(G -> lists[u]) != -1) {
			x = get(G -> lists[u]);
			if(G -> colors[x] == 1) {
				G -> parents[x] = u;
				t = Visit(G, L, x, t);
			}
			moveNext(G -> lists[u]);
		}
		G -> colors[u] = 3;
		//	(t)++;
		G -> finish[u] = ++t;

		prepend(L, u);
		//	printf("SIZE %d", length(L));
		return t;

	}


	Graph transpose(Graph G){
		if(G == NULL){
			printf("Transpose cannot be performed because Graph doesn't exist\n");
			exit(EXIT_FAILURE);
		}
		Graph g = newGraph(getOrder(G));

		for(int i = 1; i < 1 + getOrder(G); i++){

			moveFront(G->lists[i]);

			while(index(G->lists[i]) > -1){
				addArc(g, get(G->lists[i]), i);
				moveNext(G -> lists[i]);

			}
		}
		return g;

	}
	Graph copyGraph(Graph G) {
		if( G == NULL) {
			printf("Cannot call copyGraph when graph doesn't exist");
			exit(EXIT_FAILURE);
		}
		Graph g = newGraph(getOrder(G));
		int x = 1;
		while(x < 1 + getOrder(G)) {
			moveFront(G->lists[x]);
			while(index(G->lists[x]) >= 0) {
				addArc(g, x, get(G->lists[x]));
				moveNext(G->lists[x]);

			}
			x++;
		}
		return g;
	}





	void printGraph(FILE *out, Graph G) {
		if(out == NULL || G == NULL) {
			printf("Graph Error: called printGraph() on a null reference");
			exit(EXIT_FAILURE);
		}
		for(int i = 1; i < getOrder(G)+1; i++) {
			fprintf(out, "%d: ", i);
			printList(out, G->lists[i]);
			fprintf(out, "\n");
		}
	}
