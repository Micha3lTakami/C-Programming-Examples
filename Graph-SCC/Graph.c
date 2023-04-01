/********************************************************************************* 
* Michael Takami, mtakami 
* 2023 Winter 
* Graph.c 
* Graph ADT featuring a depth-first-search
*********************************************************************************/ 
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "Graph.h"
#include "List.h"

// structs --------------------------------------------------------------------

//private GraphObj type
typedef struct GraphObj{
	int order;	//number of vertices
	int size;	//number of edges
	int *color;
	int *discover;
	int *finish;
	int *parent;
	int *distance;
	int source;
	List *adj;
} GraphObj;

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// returns a Graph pointing to a newly created GraphObj representing a graph having
// n vertices and no edges
Graph newGraph(int n){
   Graph G;
   G = malloc(sizeof(GraphObj));
   G->order = n;
   G->size = 0;
   G->source = NIL;
   G->color = calloc(n+1, sizeof(int));
   G->discover = calloc(n+1, sizeof(int));
   G->finish = calloc(n+1, sizeof(int));
   G->parent = calloc(n+1, sizeof(int));
   G->distance = calloc(n+1, sizeof(int));
   G->adj = calloc(n+1, sizeof(List*));
    
   for(int x = 1; x <= n; x++){
   		G->adj[x] = newList();
   		G->parent[x] = NIL;
   		G->discover[x] = UNDEF;
   		G->finish[x] = UNDEF;
   		G->distance[x] = INF;
   }

   return G;
}

// freeGraph()
// frees all heap memory associated with the Graph *pG,
// then sets the handle *pG to NULL
void freeGraph(Graph* pG){
    if (pG == NULL || *pG == NULL) return;

    Graph G = *pG;
    free(G->color);
    free(G->parent);
    free(G->distance);
    free(G->finish);
    free(G->discover);

    if(G->adj != NULL){
        int order = getOrder(G);
        for(int x = 1; x <= order; x++){
            freeList(&(G->adj[x]));
        }
        free(G->adj);
    }
    free(G);
    *pG = NULL;
}

// Access functions -----------------------------------------------------------

// getOrder()
// returns the order(number of vertices) of the graph being called 
int getOrder(Graph G){
	if( G==NULL ){
      fprintf(stderr, "Graph Error: calling getOrder() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->order);
}

// getSize()
// returns the size(number of edges) of the graph being called
int getSize(Graph G){
	if( G==NULL ){
      fprintf(stderr, "Graph Error: calling getSize() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->size);
}

// getSource()
// returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called
int getSource(Graph G){
	if( G==NULL ){
      fprintf(stderr, "Graph Error: calling getSource() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->source);
}

// getParent()
// return the parent of vertex u in the BFS tree
// created by BFS(), or NIL if BFS() has not yet been called
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: calling getParent() on invalid vertex reference\n");
      exit(EXIT_FAILURE);
	}
	return(G->parent[u]);
}

// getDiscover()
// returns the discover time for the given vertex
// Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u){
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: calling getDiscover() on invalid vertex reference\n");
      exit(EXIT_FAILURE);
	}
	return(G->discover[u]);
}

// getFinish()
// returns the finish time for the given vertex
// Pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u){
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: calling getFinish() on invalid vertex reference\n");
        exit(EXIT_FAILURE);
	}
	return(G->finish[u]);
}

// Manipulation procedures ----------------------------------------------------


// addEdge()
// inserts a new edge joining u to v, 
// i.e. u is added to the adjacency List of v, and v to the adjacency List of u. 
// Pre: 1 <= u & v <= getOrder(G)
void addEdge(Graph G, int u, int v){
	if(u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)){
		fprintf(stderr, "Graph Error: calling addEdge() on invalid vertex reference\n");
	}
	else{
		// Check if edge already exists
		List L = G->adj[u];
		moveFront(L);
		while (index(L) >= 0) {
			if (get(L) == v) return;
			moveNext(L);
		}	
		
		// Add u to v adjacency list
		L = G->adj[v];
		moveFront(L);

		while(index(L) >= 0 && get(L) < u){
			moveNext(L);
		}

		if(index(L) == -1){
			append(L, u);
			
		}
		else{
			insertBefore(L, u);
			
		}

		// Add v to u adjacency lisst
		L = G->adj[u];
		moveFront(L);

		while(index(L) >= 0 && get(L) < v){
			moveNext(L);
		}

		if(index(L) == -1){
			append(L, v);
			
			
		}
		else{
			insertBefore(L, v);
			
			
		}
		
		G->size++;
	}

}

// addArc()
// inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency
// List of v).
// Pre: 1 <= u & v <= getOrder(G)
void addArc(Graph G, int u, int v){
	///add v to u adjacency lisst
	if(u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)){
		fprintf(stderr, "Graph Error: calling addEdge() on invalid vertex reference\n");
	}
	else{
		List L = G->adj[u];
		moveFront(L);

		while(index(L) >= 0 && get(L) < v){
			moveNext(L);
		}
		if(index(L) >= 0 && get(L) == v){
			// duplicate found, return
			return;
		}		
		else{
			if(index(L) == -1){
				append(L, v);
			}
			else{
				insertBefore(L, v);
			}
			G->size++;
		}
	}
}


// Visit()
// Helper function for DFS, recursively visits all the nodes down from the vertex it is called on
// this version utilizes time being a local static variable in DFS and thus treats it as an input output variable
void Visit(Graph G,List S, int x, int* time){

	G->color[x] = GRAY;
	G->discover[x] = (*time)++;
	List adj = G->adj[x];

	for(moveFront(adj); index(adj) >= 0; moveNext(adj)){
		int y = get(adj);
		if(G->color[y] == WHITE){
			G->parent[y] = x;
			Visit(G, S, y, time);
		}	
	}

	G->color[x] = BLACK;
	G->finish[x] = (*time)++;
	prepend(S, x);

}

// DFS()
// Performs the depth first search algorithm on 𝐺. The List argument 𝑆 has two purposes
// in this function. First it defines the order in which vertices are to be processed in the main loop (5-7) of
// DFS. Second, when DFS is complete, it will store the vertices by decreasing finish times (hence 𝑆 is
// considered to be a stack).
// Pre: length(S)==getOrder(G)
void DFS(Graph G, List S){
	for(int x = 1; x <= getOrder(G); x++){
		G->parent[x] = NIL;
		G->color[x] = WHITE;
		G->discover[x] = UNDEF;
		G->finish[x] = UNDEF;
	}

	if(length(S) != getOrder(G)){
		fprintf(stderr, "Graph Error: Stack length is not equal to Order\n");
	}
	static int time = 1;
	time = 1;
	for(moveFront(S); index(S) >= 0; moveNext(S)){
		int u = get(S);
		if(G->color[u] == WHITE){
			Visit(G, S, u, &time);
		}
	}
	
	for(int sub = (length(S)/2); sub>0; sub--){
		deleteBack(S);
	}
}




// Other Functions ------------------------------------------------------------

// printGraph()
// prints the adjacency list of the graph to the designated output stream
void printGraph(FILE* out, Graph G){
	int order = getOrder(G);

	for(int i = 1;i<=order;i++){
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");
	}
}

// transpose()
// returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G){
	Graph tpose = newGraph(getOrder(G));
	for(int x = 1; x <= getOrder(G); x++){
		List cur = G->adj[x];
		moveFront(cur);
		while(index(cur) >= 0){
			int y = get(cur);
			addArc(tpose, y, x);
			moveNext(cur);
		}
	}
	return tpose;
}

// copyGraph()
// returns a reference to a graph that is a copy of G
Graph copyGraph(Graph G){
	Graph copy = newGraph(getOrder(G));
	for(int x = 1; x <= getOrder(G); x++){
		List cur = G->adj[x];
		moveFront(cur);
		while(index(cur) >= 0){
			int y = get(cur);
			addArc(copy, x, y);
			moveNext(cur);
		}
	}
	return copy;
}
