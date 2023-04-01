/********************************************************************************* 
* Michael Takami, mtakami 
* 2023 Winter CSE101 PA# 1
* ListTest.c 
* Personal Test client for List ADT 
*********************************************************************************/                                                                                                                                                                     
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"


int main(int argc, char* argv[]){
   
   //make new list and tests index,length, append, and prepend functions
   List A = newList();
   int tester, tester1;
   append(A,2);
   prepend(A,1);
   append(A,3);
   append(A,4);
   
   //to test respective empty list errors
   //insertBefore(A, 0);
   //insertAfter(A, 0);
   //set(A,0);
   
   tester = length(A);
   tester1 = index(A);
   printf("\n**********\nlength: %d\ncurIndex: %d\n**********\n", tester, tester1);
   printList(stdout,A);
   printf("\n**********\n");

   //tests for get, front, back, moveFront, moveBack
   tester = front(A);
   printf("got front\n");
   tester1 = back(A);
   printf("got back\n");
   printf("front: %d\nback: %d\n",tester, tester1);
    printf("**********\n");
   
   /*int tester2 = get(A);
   tester1 = index(A);
   printf("current index(%d) value(should be out off bounds):%d\n", tester1, tester2);
   */

   //front and moveNext test
   moveFront(A);
   int tester2 = get(A);
   tester1 = index(A);	
   printf("current index(%d) value(should be front value):%d\n",tester1, tester2);
   moveNext(A);
   tester2 = get(A);
   tester1 = index(A);
   printf("current index(%d) value(should be 2nd from front value):%d\n",tester1, tester2);

   //back and movePrev test
   moveBack(A);
   tester2 = get(A);
   tester1 = index(A);	
   printf("current index(%d) value(should be back value):%d\n",tester1, tester2);
   movePrev(A);
   tester2 = get(A);
   tester1 = index(A);
   printf("current index(%d) value(should be 2nd from last value):%d\n",tester1, tester2);
   printList(stdout, A);
   printf("\n**********\n");

   //set test
   append(A,69);
   tester2 = back(A);
   printf("current back: %d\n", tester2);
   moveBack(A);
   set(A,5);
   tester1 = back(A);
   printf("new back: %d\n", tester1);
   tester1 = index(A);
   printf("cur index: %d\n", tester1);
   printList(stdout,A);
   printf("\n**********\n");

   //equals test
   List B = newList();
   append(B,1);
   append(B,2);
   append(B,3);
   append(B,4);
   append(B,5);
   bool outcome = equals(A, B);
   tester1 = index(A);
   printf("cur index: %d\n", tester1);
   if(outcome == true){
   		printf("Equals: Passed.\n");
   	}
   printf("\n**********\n");

   //insertBefore and insertAfter tests;
   printf("insertBefore and insertAfter tests");
   tester1 = index(A);
   printf("cur index: %d\n", tester1);
   tester1 = length(A);
   printf("cur length %d\n", tester1);
   moveFront(A);
   insertBefore(A,0);
   printf("inserted before.\n");
   tester1 = index(A);
   printf("cur index after insert on front: %d\n", tester1);
   
   tester1 = length(A);
   printf("cur length %d\n", tester1);
   printList(stdout, A);
   moveBack(A);
   printf("moved back.\n");
   insertAfter(A,6);
   printf("inserted after.\n");
   tester1 = index(A);
   printf("cur index: %d\n", tester1);
   tester1 = length(A);
   printf("cur length %d\n", tester1);
   printList(stdout,A);
   printf("**********\n");

   //deleteFront test
   printf("deletefront test.\n");
   tester1 = index(A);
   printf("cur index: %d\n", tester1);
   tester1 = length(A);
   printf("cur length %d\n", tester1);
   printList(stdout,A);
   deleteFront(A);
   printList(stdout,A);
   tester1 = length(A);
   printf("cur length %d\n", tester1);
   printf("**********\n");

   //deleteBack test
   printf("deleteback test.\n");
   tester1 = index(A);
   printf("cur index: %d\n", tester1);
   tester1 = length(A);
   printf("cur length %d\n", tester1);
   printList(stdout,A);
   deleteBack(A);
   printList(stdout,A);
   tester1 = length(A);
   printf("cur length %d\n", tester1);
   printf("**********\n");

   //delete test
   tester1 = index(A);
   printf("cur index: %d\n", tester1);
   movePrev(A);
   delete(A);
   printList(stdout,A);
   tester1 = index(A);
   printf("cur index: %d\n", tester1);        
   printf("**********\n");

   //copy test
   List C = copyList(A);
   printList(stdout, A);
   printf("\n");
   printList(stdout, C);
   freeList(&A);
   freeList(&B);
   freeList(&C);
}
