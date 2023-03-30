#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack_calculator.h"

// Allocate a new Stack struct and return a pointer to it.
Stack *stack_create(void) {
  Stack *out;
  out = (Stack *)calloc(1, sizeof(Stack));
  return out;
}

// Add a new node at the front of the stack. Return false if we are unable to do
// so (eg, if memory allocation fails).
bool stack_push(Stack *s, CalculatorItem item) {

  Node *pushed = (Node *)calloc(1, sizeof(Node));

  if(pushed == NULL){
	  return false;
  }
	
	pushed->item = item;
	pushed->next = s->top;

	s->top = pushed;

  return true;
}

// Pop the stack and put the result into the output pointer.
// return false if the stack is NULL or if it is empty.
bool stack_pop(Stack *s, CalculatorItem *output) {

  	if(s == NULL || s->top == NULL){
		return false;
	}
	
	CalculatorItem p0p = s->top->item;
	*output = p0p;

	Node *taken = s->top;
	s->top = s->top->next;

	free(taken);


	return true;
}

// Returns true if the specified stack is empty.
bool stack_empty(Stack *s) {
  if(s->top == NULL){
  	return true;
  }
  
  else{
	  return false;
  }
}

// Free all of the memory used by this stack, including its linked list.
// When you are done, set the pointer to NULL.
void stack_delete(Stack **s) {

	CalculatorItem flame;
	while(stack_empty((*s)) !=  true){
		stack_pop(*s, &flame);
	}
	free((*s));
	*s = NULL;


}

// Returns true if we were able to successfully perform the computation step,
// and false if there was an error of some kind.
bool stack_compute_step(Stack *s, CalculatorItem item) {

	CalculatorItem young;
	CalculatorItem old;
	
	float first;
	float second;
	float result;
	
	if(item.type == NUMBER){
                
                stack_push(s, item);
                return true;
        }


	else if(s == NULL || s->top == NULL){
	       return false;
	}

	else{
		stack_pop(s, &young);
         	stack_pop(s, &old);

         	first = young.value;
         	second = old.value;
	


		if(item.type == ADD){
			result = first + second;
			item.type = NUMBER;
			item.value = result;
			stack_push(s, item);
			
			return true;
		}

		else if(item.type == MULTIPLY){
                	result = first * second;
                	item.type = NUMBER;
                	item.value = result;
                	stack_push(s, item);
		
                	return true;
        	}

		else if(item.type == SUBTRACT){
			result = second - first;
			item.type = NUMBER;
			item.value = result;
			stack_push(s, item);
		
			return true;
		}
	
		else if(item.type == DIVIDE){
			if(first == 0){
				return false;
			}
			
			else{
				result = second / first;
				item.type = NUMBER;
				item.value = result;
				stack_push(s, item);
			
				return true;
			}
	
		}
	}
	return false;

}
