#include "board.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define COL_STD "\x1B[0m"
#define COL_GREEN "\x1B[32m"
#define COL_AMBER "\x1B[33m"
#define COL_RED "\x1B[31m"

#define EMPTY_CHAR '_'

void make_uppercase(char* s) {
	int i;
	for (i = 0; i < strlen(s); i++) {
		s[i] = toupper(s[i]);
	}
}

board_t create_board(char* word) {
        board_t board;
	char* cloned_word;
	memset(&board.guesses, 0, sizeof(board.guesses));

	board.curr_guess = 0;
        board.word_len = strlen(word);
	cloned_word = strdup(word);
	make_uppercase(cloned_word);
        board.word = cloned_word;
	memset(&board.letter_states, 0, sizeof(board.letter_states));

	return board;
}

int can_guess(board_t* board) {
        return board->curr_guess < NUM_GUESSES;
}

void set_letter_state(board_t* board, char letter, char state) {
	char c_idx = letter - 'A';
	assert(c_idx >= 0 && c_idx < 26);
	if (board->letter_states[c_idx] < state)
		board->letter_states[c_idx] = state;
}

guess_t fill_letters(board_t* board, char* word, int word_len) {
	int i;
	guess_t guess;
	guess.word = word;
	guess.states = malloc((board->word_len + 1) * sizeof(char));
	for (i = 0; i < word_len; i++) {
		char state = STATE_RED;
		char c = word[i];
		if (c == board->word[i]) { 
			state = STATE_GREEN;
		} else {
			int j;
			for (j = 0; j < board->word_len; j++) {
				if (c == board->word[j]) {
					state = STATE_AMBER;
				}
			}
		}
		guess.states[i] = state;
		set_letter_state(board, c, state); 
	}
	return guess;
}

int make_guess(board_t* board, char* word) {
        int wlen = strlen(word);

        if (wlen != board->word_len) {
                return GUESS_INVALID_WORD;
        } else if (!can_guess(board)) {
                return GUESS_BOARD_FULL;
        } else {
		char* cloned_word;
		cloned_word = strdup(word);
		make_uppercase(cloned_word);
                board->guesses[board->curr_guess] = fill_letters(board, cloned_word, wlen);
                board->curr_guess += 1;
                if (strcmp(cloned_word, board->word) == 0) {
                        return GUESS_SUCCEEDED;
                } else {
                        return GUESS_FAILED;
                }
        }
}

char* col_for_state(char s) {
	char* col;
	switch (s) {
		case STATE_RED:
			col = COL_RED;
			break;
		case STATE_AMBER:
			col = COL_AMBER;
			break;
		case STATE_GREEN:
			col = COL_GREEN;
			break;
		default:
			col = COL_STD;
			break;
	}
	return col;
}

void print_board(board_t* board) {
	int i;
	for (i = 0; i < NUM_GUESSES; i++) {
		int j;
		printf("        ");
		if (board->guesses[i].word != NULL) {
			for (j = 0; j < board->word_len; j++) {
				char c = board->guesses[i].word[j];	
				char s = board->guesses[i].states[j];
				if (c == 0) {
					c = '0';
				}	
				char* col = col_for_state(s);		

				printf("%s%c", col, c);	
			}
		} else {
			for (j = 0; j < board->word_len; j++) {
				printf("%s%c", COL_STD, EMPTY_CHAR);
			}
		}
		printf("\n");
	}
	
	printf("\n%sLetters: ", COL_STD);
	for (i = 0; i < 26; i++) {
		char c = 'A' + i;
		char s = board->letter_states[i];
		char* col = col_for_state(s);	
		printf("%s%c ", col, c);
	}
	printf("%s\n\n\n\n\n", COL_STD);
}
