/*********************************************************************************
* Michael Takami, mtakami 
* 2023 Winter CSE101 PA# 2
* GraphTest.c 
* Personal Test client for Graph ADT 
*********************************************************************************/                                                                                                                                                                     

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
int n = 8;
Graph G = newGraph(n);

// TEST 1
printf("\n**********\nTEST #1\n");
int order = getOrder(G);
printf("\n");
int size = getSize(G);
printf("order: %d\n", order);
printf("size: %d\n", size);
printf("**********\n");

//TEST 2
printf("**********\nTEST #2\n");
addArc(G, 1, 2);
addArc(G, 2, 3);
addArc(G, 2, 3);
addArc(G, 2, 5);
addArc(G, 2, 6);
addArc(G, 3, 4);
addArc(G, 3, 7);
addArc(G, 4, 3);
addArc(G, 4, 8);
addArc(G, 5, 1);
addArc(G, 5, 6);
addArc(G, 6, 7);
addArc(G, 7, 6);
addArc(G, 7, 8);
addArc(G, 8, 8);
printf("\nGraph G\n");
printGraph(stdout, G);
Graph TPose = transpose(G);
printf("\nG Transpose\n");
printGraph(stdout, TPose);
printf("**********\n");

// TEST 3
printf("**********\nTEST #3\n");
List stack = newList();
for(int x = 1; x<=getOrder(G) ; x++){
	append(stack,x);
}
printf("Initial Stack: ");
printList(stdout, stack);
DFS(G, stack);
printf("\nDFS completed\n");
printList(stdout, stack); // Stack for this graph should be: 1 2 5 3 7 6 4 8
printf("\n");
DFS(TPose, stack);
printf("\nSecond DFS completed successfuly.\n");
printList(stdout, stack); // 2nd Stack for this Graph should be: 8 7 6 3 4 1 5 2
printf("\n**********\n");

// TEST 4
printf("**********\nTEST #4\n");
printf("Adjacency list representation of G:\n");
printGraph(stdout, G);
int part = 0;
moveFront(stack);
while(index(stack)>=0){
	int cur = get(stack);
	if(getParent(TPose, cur) == NIL){
		part++;
	}
	moveNext(stack);
}
printf("\nG contains %d strongly connected components:\n", part);
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
		printf("Component %d: ", comp);
		printList(stdout, component);
		printf("\n");
		clear(component);
	}
	movePrev(stack);

}
printf("\n");
printf("**********\n");

freeGraph(&TPose);
freeList(&component);
freeList(&stack);
freeGraph(&G);
}
