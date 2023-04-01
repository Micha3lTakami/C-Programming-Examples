### Design by Michael Takami

## Some Extra Random Notes/niche things this hw taught me

-when allocating memory strings of n need memory for n+2 for null byte and new line. Thus, when creating the buffer, no string should be larger than 7 bytes(the 5 characters, the new line, and the null byte)

-if bytes are still reachable with no glaring leak, make sure file is closed

-accesing char off a string- string[x]

## load vocab

```
establish file pointer
open file using file pointer
establish buffer


open file
	read line using buffer
	use fgets to retrieve current word in buffer
	while fgets isnt null
		assign current word to current index in buffer
		if size is divisible by 10
			reallocate memory

assign num_words to size value which had been incremented throughout
close file
return out-pointer to vocab
```
-string array(array of char pointers) will be initalized at a size of 10

-when reallocating, size parameter is SIZE + HOW MANY BYTES YOU WANT EXPANDED

-will be allocated in blocks of 100 due to size of vocab

-word will copied using strdup() will be freed ON THE SPOT

## valid guess

iterate through vocabulary for n = num_words comparing string pointer guess to current index of vocabulary.
Boolean result just specifies whetehr the inputted string can even be compared in the first place.

```
initialize counter for number of times seen in dictionary
initiate iterator

for loop through dictionary
	if a word in the vocab is the same as the guess
		increment the counter

if encounter > 0
	return true
return false
```
## score guess

Will be called as long as valid guess returns true.
Compare char* secret to char * guess character to character via a loop comparing the same charcter index for both words. Number of if statements will then determine whether to add a 'x'. 'y', or 'g' to the same corresponding index in the char *result which will be constantly updated throughout each turn.
NOTE: DONE FROM RUBRIC LITERALLY. IF A CHAR IS IN THE WORD BUT NOT IN THE RIGHT POSITION, IT WILL MARK IT AS 'y'
```
for loop through string array char by char
	if the letetr in secret is equal to the letter in guess
		set the result corresponding letter to g
	else if the current guess character is in the secret word
		set the result corresponding letter to y
	else
		set the result corresponding letter to x
if the guess is equal to the result
	return true
return false
```

## free vocabulary 

iterate through entire array constantly setting ther current index to a char * which will be set to the current index throughout the loop. 

```
for loop through dictionary
	free string at  ccurrent index in for loop
free dictionary pointer

```
