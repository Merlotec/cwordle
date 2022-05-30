#include <stdio.h>
#include <stdlib.h>
#include "board.h"

int main() {
	printf("Welcome to cwordle!\n");
	board_t board = create_board("quick");
	printf("Guess the %i letter word!\n", board.word_len);
	while (can_guess(&board)) {
		printf("%sEnter guess (%i letters)...\n", COL_STD, board.word_len);
		char* guess = malloc((board.word_len + 3) * sizeof(char));
		memset(guess, 0, (board.word_len + 3) * sizeof(char));
		fgets(guess, board.word_len + 3, stdin);
		size_t last = strlen(guess) - 1;
		
		if (isspace(guess[last])) {
			guess[last] = '\0';
		}
		int res = make_guess(&board, guess);
		
		print_board(&board);	
		switch (res) {
			case GUESS_SUCCEEDED:
				printf("%sYou guessed the word!\n", COL_GREEN);
				return 0;
			case GUESS_FAILED:
				printf("Incorrect, try again...\n");
				break;
			case GUESS_INVALID_WORD:
				printf("%sInvalid word entered!\n", COL_RED);
				break;
		}
		free(guess);
	}
	printf("Out of guesses - you lose!\n");
	return 0;
}
