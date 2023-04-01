/*********************************************************************************
* Michael Takami, mtakami
* 2023 Winter 
* Graph.h 
* header file for Graph ADT with function declarations and type definitions 
*********************************************************************************/ 
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#define INF -1
#define NIL -2
#define UNDEF -3
#define WHITE 0
#define GRAY 1
#define BLACK 2
#include<stdbool.h>
#include "List.h"

/*** Exported Types ***/
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

/*** Manipulation procedures ***/
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);

#endif

