/********************************************************************************* 
* Michael Takami, mtakami 
* 2023 Winter
* FindComponents.c 
* Conducts DFS in order to get the strongly connected components based on the input file
*********************************************************************************/ 
#define  _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"
#include <string.h>

int main(int argc, char *argv[]) {
	
	// Confirm correct number of arguments
	if (argc != 3) {
        	fprintf(stderr,"Error: more or less than two command line arguments given.\n");
        	return 1;
    	}
	
	// Open input file for reading
	FILE *file1 = fopen(argv[1], "r");
	if (file1 == NULL) {
        printf("Error: Unable to open file 1(input)%s\n", argv[1]);
        return 1;
    }
    
	// Read in Number of Vertex
    int n;
	fscanf(file1, "%d", &n);
	Graph G = newGraph(n);

	// Read in Edges until dumbie input detected
	int x, y;
	while (fscanf(file1, "%d %d", &x, &y) == 2 && x != 0 && y != 0) {
		addArc(G, x, y);
	}

	// Open output file to write to
	FILE *file2 = fopen(argv[2], "w");
	if (file2 == NULL) {
		printf("Error: Unable to open file 2(output)%s\n", argv[2]);
		return 1;
	}
	fprintf(file2, "Adjacency list representation of G:");
	fprintf(file2, "\n");
	printGraph(file2, G);
	

	// Find strongly connected components
	Graph TPose = transpose(G);
	List stack = newList();

	for(int x = 1; x<=getOrder(G) ; x++){
		append(stack,x);
	}
	DFS(G, stack);
	DFS(TPose, stack);

	int part = 0;
	moveFront(stack);
	while(index(stack)>=0){
		int cur = get(stack);
		if(getParent(TPose, cur) == NIL){
			part++;
		}
		moveNext(stack);
	}
	fprintf(file2, "\nG contains %d strongly connected components:\n", part);
	int comp = 0;
	moveBack(stack);
	List component = newList();
	while (index(stack) >= 0) {
		int cur = get(stack);
		
		if(getParent(TPose, cur) != NIL){
			prepend(component, cur);
		}
		else{
			prepend(component, cur);
			comp +=1;
			fprintf(file2,"Component %d: ", comp);
			printList(file2, component);
			fprintf(file2,"\n");
			clear(component);
		}
		movePrev(stack);
	}

	// free heap memory and close files
	fclose(file1);
	fclose(file2);
	freeGraph(&TPose);
	freeList(&component);
	freeList(&stack);
	freeGraph(&G);


}
