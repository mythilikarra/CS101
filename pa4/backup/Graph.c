//Mythili Karra
////mmkarra
////CMPS 101
////May 27, 2019

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
	int* distance;
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
	G -> distance = malloc(sizeof(int)*(n+1));
	for(int i = 0; i<n+1; i++) {
		G -> lists[i] = newList();
		G -> colors[i] = 1;
		G -> parents[i] = 0; 
		G -> distance[i] = -1;
	}
	return G;
}
void freeGraph(Graph *pG){
	for (int i=0; i<getOrder(*pG) + 1; i++){
		freeList(&(*pG)->lists[i]);
	}
	free((*pG)->lists);
	free((*pG)->parents);
	free((*pG)->distance);
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
int getDist(Graph G, int u) {
	if (G == NULL){
		printf("getDist() Error: BFS has not been called");
		exit(EXIT_FAILURE);

	}
	else if( !(u >= 1) || !(u <= getOrder(G)) ) {
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == 0) {
		return -1;
	}	
	else {
		return G -> distance[u];
	}
}

void getPath(List L, Graph G, int u) {
	if (G == NULL){
		printf("getPath() Error: BFS has not been called");
		exit(EXIT_FAILURE);

	}
	else if( !(u >= 1) || !(u <= getOrder(G)) ) {
		exit(EXIT_FAILURE);
	}
	else if(getSource(G) == NULL) {
		exit(EXIT_FAILURE);
	}

	else {
		if(getSource(G) == u) {
			append(L,u);
		}
		else if(getParent(G,u) == 0) {
			prepend(L,0);
		}
		else {
			//backtracking from the parent to get shortest path
			getPath(L, G, getParent(G,u));
			append(L,u);
		}
	}
}

void makeNull(Graph G) {
	if (G == NULL){
		printf("makeNull() Error: BFS has not been called");
		exit(EXIT_FAILURE);

	}
	for(int i = 1; i < getOrder(G) + 1; i++) {
		clear(G -> lists[i]);
		G -> colors[i] = 1;
		G -> parents[i] = 0;
		G -> distance[i] = -1;
	}
	G -> size = 0;
	G -> source = 0;
}


void addEdge(Graph G, int u, int v) {
	if (G == NULL){
		printf("addEdge() Error: BFS has not been called");
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
void BFS(Graph G, int s) {
	G->source = s;
	for(int i = 0; i < getOrder(G) + 1; i++) {
		G -> colors[i] = 1;
		G -> distance[i] = -1;
		G -> parents[i] = 0; 
	}	
	G -> colors[s] = 2;
	G -> distance[s] = 0;
	G -> parents[s] = 0;
	List x = newList();

	append(x,s); //here - I had lists -> append...
	int u;
	int v;
	while(length(x) != 0) {
		//	moveFront(x);
		u = front(x);
		//	delete(x);
		deleteFront(x);
		moveFront(G->lists[u]);
		//	for(int i = 0; i < length( G -> lists[u]); i++) {
		while(index(G->lists[u])!=-1){
			v = get(G -> lists[u]);
			if(G -> colors[v] == 1) {
				G -> parents[v] = u;
				G -> colors[v] = 2;
				G -> distance[v] =  G -> distance[u] + 1;
				append(x,v);
			}
			moveNext(G->lists[u]);
		}
		G -> colors[u] = 3;
	}
	freeList(&x);
	x = NULL;
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

