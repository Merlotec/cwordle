#ifndef BOARD_H
#define BOARD_H

#define NUM_GUESSES 6
#define WORD_LEN 5

#define GUESS_INVALID_WORD -1
#define GUESS_BOARD_FULL 0
#define GUESS_FAILED 1
#define GUESS_SUCCEEDED 2

#define STATE_UNKNOWN 0
#define STATE_RED 1
#define STATE_AMBER 2
#define STATE_GREEN 3

#define COL_STD "\x1B[0m"
#define COL_GREEN "\x1B[32m"
#define COL_AMBER "\x1B[33m"
#define COL_RED "\x1B[31m"

struct guess {
	char* word;
	char* states;
};
typedef struct guess guess_t;

struct board {
	int word_len;
	char* word;
	guess_t guesses[NUM_GUESSES];
	int curr_guess;
	char letter_states[26];
};
typedef struct board board_t;

board_t create_board(char* word);

int can_guess(board_t* board);

int make_guess(board_t* board, char* word);

void print_board(board_t* board);

#endif
