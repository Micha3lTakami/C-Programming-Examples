//-----------------------------------------------------------------------------
// List.c
// Michael Takami, mtakami
// Winter 2023
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"


// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   ListElement data;
   Node prev;
   Node next;
} NodeObj;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int curIndex; // Cursor Index
   int length;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node pN){
    if( pN!=NULL ){
      free(pN);
      
    }
}

// newList()
// Returns reference to new empty List object.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   assert( L!=NULL );
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->curIndex = -1;
   return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
    if(pL == NULL || *pL == NULL) return;

    Node temp = (*pL)->front;
    while(temp != NULL) {
        Node curr = temp;
        temp = temp->next;
        freeNode(curr);
    }
    free(*pL);
    *pL = NULL;
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L){
   if( L==NULL ){
      fprintf(stderr, "List Error: calling Length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise
int index(List L){
	if( L==NULL ){
      fprintf(stderr, "List Error: calling Index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->curIndex);
}

// front()
// Returns the value at the front of L
// Pre: length() > 0
ListElement front(List L){
   if( L==NULL ){
      fprintf(stderr, "List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(L) <= 0){
      fprintf(stderr, "List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}

// back()
// Returns the value at the back of L.
// Pre: length() > 0
ListElement back(List L){
   if( L==NULL ){
      fprintf(stderr, "List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(L) <= 0){
      fprintf(stderr, "List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data);
}

// get()
// Returns cursor element of L.
// Pre: length()>0, index()>=0
int get(List L){
	if( length(L) <= 0){
      fprintf(stderr, "List Error: calling get() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( index(L) < 0){
      fprintf(stderr, "List Error: calling get() using an out of bounds index\n");
      exit(EXIT_FAILURE);
   }
   return L->cursor->data;

}

// equals()
// Returns true if A is same int sequence as B, false otherwise.
bool equals(List A, List B){
   if( A==NULL || B==NULL ){
      fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   bool eq;
   Node N, M;

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = ( N->data==M->data );
      N = N->next;
      M = M->next;
   }
   return eq;
}

// Manipulation procedures ----------------------------------------------------
//clear()
// Resets L to its original empty state.
void clear(List L){
    if( L==NULL ){
        fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node temp = L->front;
    while(temp != NULL) {
        Node curr = temp;
        temp = temp->next;
        freeNode(curr);
    }
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->curIndex = -1;
}


//set()
//Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x){
	if( length(L) <= 0){
      fprintf(stderr, "List Error: calling set() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( index(L) < 0){
      fprintf(stderr, "List Error: calling set() using an out of bounds index\n");
      exit(EXIT_FAILURE);
   }
   L->cursor->data = x;	
}
// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
	if(length(L) > 0){
		L->cursor = L->front;
		L->curIndex = 0;
	}
}

// moveBack()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveBack(List L){
	if(length(L) > 0){
		L->cursor = L->back;
		L->curIndex = ((L->length)- 1);
	}
}

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
	 if(L->cursor != NULL && L->cursor == L->front){
      L->cursor = NULL;
      L->curIndex = -1;
      return;
   }
   if(L->cursor != NULL && L->curIndex != 0){
      L->cursor = L->cursor->prev;
      L->curIndex = ((L->curIndex)-1);
   }
   else if(L->cursor == NULL){
      return;
   }
}
// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
	if(L->cursor != NULL && L->curIndex != ((L->length)-1)){
		L->cursor = L->cursor->next;
		L->curIndex = ((L->curIndex)+1);
	}
	
	else if(L->cursor != NULL && L->cursor == L->back && L->curIndex == ((L->length) - 1)){
		L->cursor = NULL;
		L->curIndex = -1;
	}
	
	else if(L->cursor == NULL){
		return;
	}
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int x){
	Node N = newNode(x);

	if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
	
	if( length(L) == 0 ) { 
      L->front = L->back = N; 
     
   }

   else{
   		L->front->prev = N;
   		N->next = L->front;
   		L->front = N;
   }
   L->length++;
   
   if(L->curIndex!=-1){
   		L->curIndex++;
   	}

}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int x)
{
   Node N = newNode(x);

   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   
   if( length(L) == 0 ) { 
      L->front = L->back = N; 
   }
   else{ 
      L->back->next = N; 
      N->prev = L->back;
      L->back = N; 
   }
   L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x){
	if( length(L) <= 0){
    	fprintf(stderr, "List Error: calling insertBefore() on an empty List\n");
    	exit(EXIT_FAILURE);
   }
   if( index(L) < 0){
    	fprintf(stderr, "List Error: calling insertBefore() using an out of bounds index\n");
    	exit(EXIT_FAILURE);
    }
    
    else if(L->curIndex == 0){
    	prepend(L,x);
    }
    else{
    	Node N = newNode(x);
   
    	 
		N->prev = L->cursor->prev;
    	N->next = L->cursor;
    	L->cursor->prev->next = N;
    	L->cursor->prev = N;
    	L->curIndex++;
    	L->length++;


    }

}

// insertAfter(List L, int x)
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x){
	if( length(L) <= 0){
    	fprintf(stderr, "List Error: calling insertAfter() on an empty List\n");
    	exit(EXIT_FAILURE);
   }
   if( index(L) < 0 ){
    	fprintf(stderr, "List Error: calling insertAfter() using an out of bounds index\n");
    	exit(EXIT_FAILURE);
    }
    
    else if(L->curIndex == (length(L)-1)){
    	append(L,x);
    }
    else{
    	Node N = newNode(x);
   
    	
		N->prev = L->cursor;
    	N->next = L->cursor->next;
    	L->cursor->next->prev = N;
    	L->cursor->next = N;
    	L->length++;


    }
}
// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L){
   if( L==NULL ){
      fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length <= 0){
      fprintf(stderr, "List Error: calling deleteBack() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   Node temp = L->back;

   if(index(L) == length(L)-1){
      L->curIndex = -1;
   }
   if(L->front == L->back){
      L->front = L->back = NULL;
   }
   else{
      L->back = L->back->prev;
      L->back->next = NULL;
   }
   L->length--;
  
   freeNode(temp);
}
// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L){
	if( L==NULL ){
      fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length <= 0){
      fprintf(stderr, "List Error: calling deleteFront() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   Node temp = L->front;
   if(L->front == L->back){
      L->front = L->back = NULL;
   }
   if(length(L)==1){
      clear(L);
   }
   else{
      L->front = L->front->next;
      L->front->prev = NULL;
   
      L->length--;
      L->curIndex--;
      freeNode(temp);
   }
}



// delete()
// Delete cursor element, making cursor undefined.
void delete(List L) {
	if(L == NULL) {
		fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0) {
		fprintf(stderr, "List Error: calling delete() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0) {
		fprintf(stderr, "List Error: calling delete() on an undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == L->front) {
		deleteFront(L);
	} 
	else if(L->cursor == L->back) {
		deleteBack(L);
	} 
	else {
		Node temp = L->cursor;
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		L->length--;
		L->cursor = NULL;
		L->curIndex = -1;
		freeNode(temp);
	}
}



// Other Functions ------------------------------------------------------------

// printList()
// Prints a string representation of L consisting of a space separated list 
// of ints to stdout.

void printList(FILE* out, List L){
    Node temp = L->front;
    while(temp != NULL){
        fprintf(out, "%d ", temp->data);
        temp = temp->next;
    }
}

List copyList(List L) {
    List copy = newList();
    Node curr = L->front;
    while (curr != NULL) {
        append(copy, curr->data);
        curr = curr->next;
    }
    return copy;
}
