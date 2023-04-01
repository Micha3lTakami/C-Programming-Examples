#include "search_util.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


// returns the number of words in which that particular letter occurs.
int score_letter(char letter, char **vocabulary, size_t num_words) {
	
	int encounter = 0;
	size_t i;

	for(i=0; i < num_words; i++){
		if(vocabulary[i] == NULL){
			continue;
		}
		else if(strchr(vocabulary[i], letter) != NULL){
			encounter++;
		}
	}

	return encounter;
}


// Calculate the score for a given word, where the letter_scores array has
// already been filled and is guaranteed to be of length 26. Slot 0
// contains the score for 'a', and slot 25 contains the score for 'z'.
// The score for a word is the sum of all of the letter scores, *for unique
// letters*. 
int score_word(char *word, int *letter_scores) {
		char *seen_letters = (char*) calloc(5, sizeof(char));
		int total_score = 0;
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 26; j++){
				char cur = 'a' + j;
				if(word[i] == cur && strchr(seen_letters, cur) == NULL){
					total_score += letter_scores[j];
					seen_letters[i] = cur;
				}
			}
		} 
  		free(seen_letters);
		
		return total_score;
}


// Returns the optimum guess, based on our heuristic.
char *get_guess(char **vocabulary, size_t num_words) {
  int letter_scores[26];

  for (int i = 0; i < 26; i++) {
    letter_scores[i] = score_letter('a' + i, vocabulary, num_words);
  }

  char *best_guess = NULL;
  int best_score = 0;
  int score = 0;
  for (size_t i = 0; i < num_words; i++) {
    if (vocabulary[i] == NULL) {
      continue;
    }
    score = score_word(vocabulary[i], letter_scores);
    if (score > best_score) {
      best_guess = vocabulary[i];
      best_score = score;
    }
  }
  return best_guess ? strdup(best_guess) : NULL;
}

// This function will filter down the vocabulary based on the knowledge that the
// specified letter *does not occur* in the secret word. So for any of the words
// in the vocabulary that do contain that letter, free their pointers and set
// the corresponding slot to NULL.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_gray(char letter, char **vocabulary,
                              size_t num_words) {
	size_t i;
	size_t removed = 0;
	for(i = 0; i < num_words; i++){
		if(vocabulary[i] == NULL){
			continue;
		}

		else if(strchr(vocabulary[i], letter) != NULL){
			free(vocabulary[i]);
			vocabulary[i] = NULL;
			removed++;
		}
	}
	return removed;
}
// filters down the vocabulary based on the knowledge that the
// specified letter occurs in the word, *but not at this particular position*.
// i.e. remove any words that either don't contain the letter at all, or do
// contain it, but at the specified position.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_yellow(char letter, int position, char **vocabulary,
                                size_t num_words) {

	size_t i;
	size_t removed = 0;
	for(i = 0; i < num_words; i++){
		if(vocabulary[i] == NULL){
			continue;
		}
		else if(strchr(vocabulary[i], letter) == NULL){
			free(vocabulary[i]);
			vocabulary[i] = NULL;
			removed++;
		}
		else if(strchr(vocabulary[i], letter) != NULL && vocabulary[i][position] == letter){
			free(vocabulary[i]);
			vocabulary[i] = NULL;
			removed++;
		}
	}

  return removed;

}


// filters down the vocabulary based on the knowledge that the
// specified letter *definitely* occurs as the specified position.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_green(char letter, int position, char **vocabulary,
                               size_t num_words) {
	size_t i;
	size_t removed = 0;
	for(i = 0; i < num_words; i++){
		if(vocabulary[i] == NULL){
			continue;
		}
		else if(vocabulary[i][position] != letter){
			free(vocabulary[i]);
			vocabulary[i] = NULL;
			removed++;
		}
	}

  return removed;

}

// Free each of the strings in the vocabulary, as well as the pointer vocabulary 
// itself
void free_vocabulary(char **vocabulary, size_t num_words) {
  for (size_t i = 0; i < num_words; i++) {
    free(vocabulary[i]);
  }
  free(vocabulary);
}
