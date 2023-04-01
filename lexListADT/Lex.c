/********************************************************************************* 
* Michael Takami, mtakami 
* 2023 Winter 
* Lex.c 
* Lexicographic order and file handler
*********************************************************************************/ 
#define  _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
    fprintf(stderr,"Error: more or less than two command line arguments given.\n");
    return 1;
  }
	FILE *file1 = fopen(argv[1], "r");
  if (file1 == NULL) {
     printf("Error: Unable to open file %s\n", argv[1]);
     return 1;
  }
  
  int lineNum = 0;
  char c;
  while ((c = fgetc(file1)) != EOF) {
    if (c == '\n') {
      lineNum++;
    }
  }
  rewind(file1); //bring file stream pointer back to front
  
  //initialize array of strings
  char **lines = (char**) calloc(lineNum, sizeof(char*));
  int cur;
  //initialize each string array in said array of strings
  for(cur = 0; cur< lineNum; cur++){
    lines[cur] = (char*)calloc(300, sizeof(char));
  }   
  cur = 0;
  //inserts file strings into said array of strings
  while (fgets(lines[cur], 300, file1) != NULL) {
    cur++;
  }	
  fclose(file1);    
  List A = newList();
	append(A,0);    	
	for(int i=1;i<lineNum;i++){
		int status = 0;
		moveBack(A);	
		while(status != 1 && strcmp(lines[i], lines[get(A)]) <=0){
			if(index(A) == 0){
				insertBefore(A,i);
				status = 1;
			}
			else{
				movePrev(A);
			}
		}
		if (status ==0){
			insertAfter(A, i);
		}
	}
	
	FILE *file2 = fopen(argv[2], "w");
	moveFront(A);
	for(cur=0; cur < length(A); cur++){
   	if(length(A) >0){
		  int curIndex = get(A);
   		fprintf(file2, "%s", lines[curIndex]);
   		moveNext(A);
		}
	}
	for(int x = 0; x<lineNum;x++){
    free(lines[x]);
  }
  free(lines);
	freeList(&A);
	fclose(file2);
  return 0;
}
