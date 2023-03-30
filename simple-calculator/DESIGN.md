### DESIGN.md by Michael Takami

## Some notes on pointers
-Pointers: special variables that store(point) to addresses rather than values

-&: gives a variable's address in memory

-star: gives that memory address's value, it is the dereference operator

## basic outline for max/add all positive function
```
maximum/adder(pointer, length):
	int max to save the max;
	int temp to temporarlily save the new index value;
	for(x < length):
		temp = value of x in array/memory
		for maximum:will compare itself to 4 bytes down in memory, if bigger then will set itself to max and increment throughout entire array
		for positive adder: will first check to see if the integer is positive and if so add itself to a running tally to be returned at the end
```

## basic understanding of how reduce works

-reduce does the same thing as the above function but in a more organized and concise way

-a one-step function that applies the function to ana ccumulator located at the next index in the array

## Pseudo for functions in num_arrays.c
```
int maximum(int *nums, int len){
	iterate through the array constantly setting an integer to the new/current maximum;
	return maximum at the end
}

int sum_positive(
	iterate through the array, on each index check if the number is posiitive
		if it is, add it to the running sum and then return sum
		if it is not, just return the sum
}

int reduce{
	an accumulator is set toan initial value from the call;
	a pointer helps iterate through the array
	in this loop the accumulator is constantly updated with a function call of the function from the reduce call parameters using the current value of the accumulator and current index
}

int maxcompare{
	returns the bigger of two integers
}

int maximum_with_reduce{
	sets an intger maxim to the value of reduce with the maxcompare function
	returns maxim
}

int SumPosComp{
	checks if the second integer is greater than 0
		if so, adds itself to the running accumulator tally
			returns accumulator
		if not, immediately returns accumualator, unchanged
}

int sum_positive_with_reduce{
	initializes the starting sum as 0;
	int sum = reduce using the functions parameters, start, and the SumPosComp function;
	return sum;
}

int NegCount{
	first number in parameter acts as accumulator like SumPosComp
	checks if second number in parameter is negative
		if so, increments the accumulator and then returns it;
		if not, returns the accumulator, unchanged
}

int count_negative_with_reduce{
	initialize starting count as 0;
	int count = reduce using the functions parameters, count, and the NegCount function;
	return count;
}

```
