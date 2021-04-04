#include <stdbool.h>

// structure with arrays of character designed to show the play board
struct game_board {
  char col_0[6]; // represents column 0
  char col_1[6]; // represents column 1
  char col_2[6]; // represents column 2
  char col_3[6]; // represents column 3
  char col_4[6]; // represents column 4
  char col_5[6]; // represents column 5
  char col_6[6]; // represents column 6
};

// is_full(game, col, h) returns true if the column col in game_board game with
//   the height h is full which means it is not allowed to put any more pieces.
// requires: 0 <= col <= 6
//           h must be positive
bool is_full(const struct game_board *game, const int col, const int h);

// is_all_full(game, h, w) returns true if all columns of game board, with the
//   height h and width w, are full with characters, and false otherwise.
// requires: h must be positive
//           w must be positive
bool is_all_full(const struct game_board *game, const int h, const int w);

// game_update(game, col, piece, h) updates the game board game with the height
//   h by putting the piece into the column col.
// effects: might modify game
// requires: piece is one of 'X' or 'O'
//           0 <= col <= 6
//           h must be positive
void game_update(struct game_board *game, const int col, const char piece,
                 const int h);

// game_print(game, h) prints the game board game with the height h to the
//   console.
// effects: produces output
// requires: h must be positive
void game_print(const struct game_board *game, const int h);

// game_winner(game, winner, h) returns true if there is a winner in the
//   game_board game with the height h and width w, and false otherwise, the
//   function modifies winner to be one of 'X' or 'O' to show who is the winner
//   if it returns true.
// effects: might modifies winner
// requires: h must be positive
bool game_winner(const struct game_board *game, char *winner, const int h);
