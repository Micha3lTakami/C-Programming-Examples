#include <stdio.h>

int maximum(int *nums, int len) {
	int max = 0;
    	int* i;
	for(i = &nums[0]; i <= &nums[len-1]; i++){
        	if(*i > max){
            		max = *i;
        	}
        
    	}
	return max;
}

int sum_positive(int *nums, int len){
	int sum = 0;
	int* i;
	for(i = &nums[0]; i <= &nums[len-1]; i++){
		if(*i > 0){
			sum += *i;
		}
	}

  	return sum;
}

int reduce(int *nums, int len, int (*f)(int,int), int initial){
	int accum = initial;
	int* i;
	for(i = &nums[0]; i <= &nums[len-1]; i++){
		accum = f(accum, *i);
	}

  	return accum;
}

int MaxCompare(int x, int y){
	if(x > y){
		return x;
	}
	else{
		return y;
	}
}



int maximum_with_reduce(int *nums, int size) {
  	int maxim = reduce(nums, size, MaxCompare, nums[0]);
	return maxim;

}

int SumPosComp(int accum, int x){
	if(x > 0){
		accum += x;
		return accum;
	}
	else{
		return accum;
	}
}

int sum_positive_with_reduce(int *nums, int size) {
  	int start = 0;
	int sum = reduce(nums, size, SumPosComp, start);
	return sum;
}

int NegCount(int accum, int x){
	if(x < 0){
		accum++;
		return accum;
	}
	else{
		return accum;
	}
}


int count_negative_with_reduce(int *nums, int size) {
	int start = 0;
	int count = reduce(nums, size, NegCount, start);
	return count;
}
