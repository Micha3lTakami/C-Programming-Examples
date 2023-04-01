#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Returns true if the guess is an exact match with the secret word fills in the result with the following:
// - 'x' goes in a slot if the corresponding letter in the guess does not appear
//   anywhere in the secret word
// - 'y' goes in a slot if the corresponding letter in the guess appears in the
//   secret word, but not in the corresponding slot
// - 'g' goes in a slot if the corresponding letter in the guess appears in the
//   corresponding slot in the secret word.
//   You can assume that result points at enough memory for a string of length
//   5. (ie, at least 6 bytes long)
bool score_guess(char *secret, char *guess, char *result) {

	 for(int i = 0; i < 5; i++){
		if(secret[i] == guess[i]){
			result[i] = 'g';
		}
		else if(strchr(secret,guess[i]) != NULL){
			result[i] = 'y';
		}
		else{
			result[i] = 'x';
		}
	
	}

	if(strcmp(secret, guess) == 0){
                return true;
        }


  return false;
}

// Returns true if the specified guess is one of the strings in the vocabulary,
// and false otherwise. num_words is the length of the vocabulary.
bool valid_guess(char *guess, char **vocabulary, size_t num_words) {
  
	int encounter = 0;
	size_t i;
	
	for(i=0; i < num_words; i++){
		if(strcmp(vocabulary[i], guess) == 0){
			encounter++;
		}
	}
	
	if(encounter > 0){
		return true;
	}
	

  return false;
}

// Returns an array of strings (so, char **), where each string contains a word
// from the specified file. The file is assumed to contain 5-letter words, one
// per line.
char **load_vocabulary(char *filename, size_t *num_words) {
  char **out = (char**)malloc(sizeof(char*) * 25);
  FILE *infile = fopen(filename, "r");
  char buf[7];
  size_t size = 0;
  
  while(fgets(buf, 7, infile)){
	out[size] = strndup(buf, 5);
	if(size % 10 == 0){
		char **temp = realloc(out, (100 + size) * sizeof(char*));
		if(temp != NULL){
			out = temp;
		}
	}
	size++;
	
  }
  *num_words = size;
  out = &out[0];
  fclose(infile); 
  return out;
}

// Free each of the strings in the vocabulary, as well as the pointer vocabulary
// itself (which points to an array of char *).
void free_vocabulary(char **vocabulary, size_t num_words) {
	for(size_t i = 0; i < num_words; i++){
		free(vocabulary[i]);
	}
	free(vocabulary);
}

// Once your other functions are working, please revert your main() to its
// initial state, but please feel free to change it, during development. You'll
// want to test out each individual function!
int main(void){
    char **vocabulary;
  	size_t num_words;
  	int num_guesses = 0;

  	srand(time(NULL));

  	// load vocabulary and store the number of words in it.
  	vocabulary = load_vocabulary("vocabulary.txt", &num_words);

  	// Randomly select one of the words from the file to be the SECRET WORD.
  	int word_index = rand() % num_words;
  	char *secret = vocabulary[word_index];

  	// input buffer -- used to get a guess from the user.
  	char guess[80];

  	// buffer for scoring each guess.
  	char result[6] = {0};
  	bool success = false;

  	printf("time to guess a 5-letter word! (press ctrl-D to exit)\n");
  	while (!success) {
    		printf("guess: ");
    		if (fgets(guess, 80, stdin) == NULL) {
      			break;
    		}
    	// cut user input off at 5 characters.
    	guess[5] = '\0';

	if (!valid_guess(guess, vocabulary, num_words)) {
      		printf("not a valid guess\n");
      		continue;
    	} 
	else {
      		num_guesses++;
    	}
    	
	success = score_guess(secret, guess, result);
    	printf("%s\n", guess);
    	printf("%s\n", result);
  	
	}

  	if (success) {
    printf("you win, in %d guesses!\n", num_guesses);
  }
  free_vocabulary(vocabulary, num_words);

  return 0;
}
