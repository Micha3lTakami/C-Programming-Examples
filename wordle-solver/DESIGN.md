### Design for hw6 by Michael Takami

## Big Ideas
-in order to parse down the vocab., off of guess, if char. isn't in the word, loop over dictionary
freeing words that contain said letter on encounter

-conversely, if the letter is marked as yellow, we can loop again with different parameters, the if 
conditional will check if the word does not contain the letter or contains the letter in that exact 
spot then it will also be free'd

-green can also eliminate words that do not contasin the letter in the right spot

-combination of all three narrows down words for final guess


## score_letter

-return the number of times particular letter occurs in vocab

```
score_letter(letter, vocab, num_words){
	initalize counter;
	for(i, num_words in vocab){
		if vocab word, i is null
			continue in loop
		else if current word contains target letter
			increment counter
	return counter
```

## score_word

-add letter_scores value of all chars in the word to determine the score of the word and then return
said value

```
score_word(word, letter scores){
	calloc an array to hold seen letters of size 5
	initialize a total_score with a value of 0
		for loop through letters in word
			for loop through alphabet letter(0-26)
				set the cur char to whatever letter in the alphabet we are currently at(char cur = 'a' + loop increment
				if the current letter in the word is the same as the current alphabet letter and the seen letters array 
				doesn't contain the current alphabet letter
					add the total score to itself + the letter score for the current word letter
					add the alphabet letter to the seen letters array
		free the seen letters array
	return the total_score
```

## filter-gray

-we discard any words that contain the given letter

```
filter_vocabulary_gray(letter, vocabulary, num_words){
	initialize increment i
	initalize a remove counter
	for i less than num_words
		if current vocab word is null
			continue in loop
		else if the current vocab word contains the letter
			free the current word
			set its position in the vocabulary to NULL
			increment the remove counter
	return the remove counter
```

## filter-yellow

-filter any words that either don't contain the letter at all or does contain it but not at the specified position

```
filter_vocabulary_yellow(letter, position, vocabulary, num_words){
        initialize increment i
        initalize a remove counter
        for i less than num_words
                if current vocab word is null
                        continue in loop
                else if the current vocab word doesn't contains the letter
                        free the current word
                        set its position in the vocabulary to NULL
                        increment the remove counter
		else if the current word has the letter and the letter in the word at the specified position is the same as the target letter
			free the current word
			set its position in the vocabulary to NULL
			increment the remove counter

        return the remove counter
```

## filter-green

-filter any words that do not have the target letter at the specified psoition

```
filter_vocabulary_green(letter, position, vocabulary, num_words){
        initialize increment i
        initalize a remove counter
        for i less than num_words
                if current vocab word is null
                        continue in loop
                else if the letter at the specified position in the current word does not contain the letter
                        free the current word
                        set its position in the vocabulary to NULL
                        increment the remove counter
        return the remove counter
```
