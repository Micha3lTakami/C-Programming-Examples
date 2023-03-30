### DESIGN.md by Michael Takami

## Some Notes on nodes/linnked lists

-a single node contains data(value) and next(a pointer to the net node in the list)

-if next is set to null, it represents and link list being terminated

## Basic Design Summary
The linked list will perform alonmgside the stack storing the calculator item's that are numbers. Calloc will be used in order to allocate memory for these values to be stored in memory. Furthermore, when an operand is detected within CalculatorItem in main the compute step will occur. This step is really split into four steps depending on the oprtaion being one of four operands.

Traversing the calculator's link list is similar to reduce in that an accumulator is stil almost present within the stack being saved as the result which will finally be popped at the end.

## how push and pop work
```
stack_pop{
	if empty or top is empty
		return false
	set a temp item as the current top of stack
	pointer from parameters points to above item

	temp node set to the top
	set the top to next from the data at the top of the stack

	free the temnporary node
}

stack_push{
	make a node for the item about to be pushed/allocate memory for it

	if memory allocation failed, return false

	set the item value for node to the value of item(CalculatorItem)
	set the next value for node to the top of the stack

	set the top of the stack to the item being pushed
}
```

## how stack delete works
```
void stack_delete{
	set a temp item to be a pop parameter
	iterate through stack using stackempty in while loop
		with each node, pop it(which has free in the function at all)
	free the stack
	set stack pointer to null
} 
```

## What happens when item.type is not a number?
For addition and multiplication, the order doesn't matter. The top two elements will be popped off the stack. If for some reason there are not two elements to be popped available, an error is returned. Otherwise, the two elements then have the operand donewhich is set to a temporary variable. That said temporary variable will then be pushed to the top of the stack. In order to do this using linked list stack implementation, the 'next' of both the new and present top of the stack must be set to their new respective addresses.

## What happens when the operand is subtraction or division?
Here, order matters. The value of the node that has been in the stack for longer(second pop) will need to be tracked to be used as the respective denominator or bigger value. Once this is done, the correct operation can be done.

## Really small snippet of what the inside of compute step will look like

```
bool stack_compute_step(Stack *s, CalculatorItem item) {
  
	if(item is add){
		pop1 = popped value off stack
		pop2 = popped value off stack
		new = pop1 + pop2
		push new to the top of the stack(change node 'next' value's etc.)
		return true
	}
	
	else if(item is multiply){
                pop1 = popped value off stack
                pop2 = popped value off stack
                new = pop1 * pop2
                push new to the top of the stack(change node 'next' value's etc.)
                return true
	}
	
	else if(item is divide){
                denom = popped value off stack
                numer = popped value off stack
                new = denom / numer
                push new to the top of the stack(change node 'next' value's etc.)
                return true
	}

	else if(item is minus){
                pop1 = popped value off stack
                pop2 = popped value off stack
                new = pop1 - pop2
                push new to the top of the stack(change node 'next' value's etc.)
                return true
	}
 	
	else{
		return invalid item
	}

	

  
}
