#include "List.h"
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define WHITE 1
#define GRAY 2
#define BLACK 3
#define UNDEF -5
#define INF -1
#define NIL 0
typedef struct GraphObj* Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);
/*** Other operations ***/
Graph transpose(Graph G);
 Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
#endif
