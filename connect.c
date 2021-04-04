#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "connect.h"


// === GLOBAL READONLY ========================================================
// need to put at least 4 pieces in a verticle, horizontal or diagonal straight
//   line to win
const int win = 4;

// === HELPER FUNCTIONS =======================================================

// is_full_col(col, h) returns true if the column col with the length h is
//   full, and false otherwise.
static bool is_full_col(const char col[], const int h) {
  assert(col);

  // if the final character of the array col is one of 'X' and 'O', the col is
  //   considered to be full
  return (col[h-1] == 'X' || col[h-1] == 'O');
}

// update_col(col, piece, h) updates the column col with the length h by
//   putting the piece into the column col.
// effects: might modify col
static void update_col(char col[], const char piece, const int h) {
  assert(col);

  for (int i = 0; i < h; ++i) {
    if (!(col[i] == 'X') && !(col[i] == 'O')) {
      col[i] = piece;
      break;
    }
  }
}

// piece_print(col, p) prints '_' if the character at p position of col is not
//   one of 'X' or 'O', and prints 'X' or 'O' it the character at p position of
//   p is one of 'X' or 'O'.
// effects: produces output
static void piece_print(const char col[], const int p) {
  assert(col);

  if (col[p] == 'X' || col[p] == 'O') {
    printf("%c|", col[p]);
  } else {
    printf("_|");
  }
}

// single_col_win(col, piece, winner, h) returns true if there are at least 4
//   pieces in the column col with length h, and false otherwise, function
//   modifies the winner to be piece if function returns true.
// effects: might modify winner
static bool single_col_win(const char col[], char piece, char *winner, 
                           const int h) {
  assert(col);
  assert(winner);

  for (int i = 0; i <= h - win; ++i) {
    // define and initialize a boolean to record the game result
    bool w = 1;

    for (int j = i; j < i + win; ++j) {
      w = w && (col[j] == piece);
    }

    // if there is a winner, we modify winner
    if (w == 1) {
      *winner = piece;
      return true;
    }
  }

  return false;
}

// col_win(game, piece, winner, h) returns true if there are at least 4 pieces
//   in a column of game with height h, and false otherwise, function modifies
//   the winner to be piece if function returns true.
// effects: might modify winner
// requires: piece is one of 'X' or 'O'
static bool col_win(const struct game_board *game, char piece, char *winner,
                    const int h) {
  assert(game);
  assert(winner);
  assert(piece == 'X' || piece == 'O');

  if (single_col_win(game->col_0, piece, winner, h)) {
    return true;
  } else if (single_col_win(game->col_1, piece, winner, h)) {
    return true;
  } else if (single_col_win(game->col_2, piece, winner, h)) {
    return true;
  } else if (single_col_win(game->col_3, piece, winner, h)) {
    return true;
  } else if (single_col_win(game->col_4, piece, winner, h)) {
    return true;
  } else if (single_col_win(game->col_5, piece, winner, h)) {
    return true;
  } else if (single_col_win(game->col_6, piece, winner, h)) {
    return true;
  } else {
    return false;
  }
}

// single_row_win(col1, col2, col3, col4, piece, winner, h) returns true if
//   the 4 characters in the same position of col1, col2, col3, and col4, with
//   length h, are all equal to piece, and false otherwise, function modifies
//   winner to be piece if function returns true.
// effects: might modify winner
static bool single_row_win(const char col1[], const char col2[], 
                           const char col3[], const char col4[], char piece, 
                           char *winner, const int h) {
  assert(col1);
  assert(col2);
  assert(col3);
  assert(col4);
  assert(winner);

  for (int i = 0; i < h; ++i) {
    // define and initialize a boolean to record the game result
    bool w = 1;

    w = w && (col1[i] == piece);
    w = w && (col2[i] == piece);
    w = w && (col3[i] == piece);
    w = w && (col4[i] == piece);

    if (w == 1) {
      *winner = piece;
      return true;
    }
  }

  return false;
}

// row_win(game, piece, winner, h) returns true if there are at least 4 pieces
//   in a row of game with height h, and false otherwise, function modifies the
//   winner to be piece if function returns true.
// effects: might modify winner
// requires: piece is one of 'X' or 'O'
static bool row_win(const struct game_board *game, char piece, char *winner,
                    const int h) {
  assert(game);
  assert(winner);
  assert(piece == 'X' || piece == 'O');

  if (single_row_win(game->col_0, game->col_1, game->col_2, game->col_3, piece, 
                     winner, h)) {
    return true;
  } else if (single_row_win(game->col_1, game->col_2, game->col_3, game->col_4, 
                            piece, winner, h)) {
    return true;
  } else if (single_row_win(game->col_2, game->col_3, game->col_4, game->col_5, 
                            piece, winner, h)) {
    return true;
  } else if (single_row_win(game->col_3, game->col_4, game->col_5, game->col_6, 
                            piece, winner, h)) {
    return true;
  } else {
    return false;
  }
}

// single_dia_win(col1, col2, col3, col4, piece, winner, h) returns true if
//   the 4 characters in the position of the diagonal straight line in col1, 
//   col2, col3, and col4, with length h, are all equal to piece, and false
//   otherwise, function modifies winner to be piece if function returns true.
static bool single_dia_win(const char col1[], const char col2[], 
                           const char col3[], const char col4[], char piece, 
                           char *winner, const int h) {
  assert(col1);
  assert(col2);
  assert(col3);
  assert(col4);
  assert(winner);

  for (int i = 0; i <= h - win; ++i) {
    // define and initialize a boolean to record the game result
    bool w = 1;

    w = w && (col1[i + 0] == piece);
    w = w && (col2[i + 1] == piece);
    w = w && (col3[i + 2] == piece);
    w = w && (col4[i + 3] == piece);

    if (w == 1) {
      *winner = piece;
      return true;
    }
  }

  return false;
}

// dia1_win(game, piece, winner, h) return true if there are at least 4 pieces
//   in a diagonal straight line from left bottom corner to the right top corner
//   of the game board with height h, and false otherwise, function modifies
//   the winner to be piece if function returns true.
// effects: might modify winner
// requires: piece is one of 'X' or 'O'
static bool dia1_win(const struct game_board *game, char piece, char *winner,
                     const int h) {
  assert(game);
  assert(winner);
  assert(piece == 'X' || piece == 'O');

  if (single_dia_win(game->col_0, game->col_1, game->col_2, game->col_3,
                     piece, winner, h)) {
    return true;
  } else if (single_dia_win(game->col_1, game->col_2, game->col_3, game->col_4,
                            piece, winner, h)) {
    return true;
  } else if (single_dia_win(game->col_2, game->col_3, game->col_4, game->col_5,
                            piece, winner, h)) {
    return true;
  } else if (single_dia_win(game->col_3, game->col_4, game->col_5, game->col_6,
                            piece, winner, h)) {
    return true;
  } else {
    return false;
  }
}

// dia2_win(game, piece, winner, h) return true if there are at least 4 pieces
//   in a diagonal straight line from left top corner to the right bottom corner
//   of the game board with height h, and false otherwise, function modifies
//   the winner to be piece if function returns true.
// effects: might modify winner
// requires: piece is one of 'X' or 'O'
static bool dia2_win(const struct game_board *game, char piece, char *winner,
                     const int h) {
  assert(game);
  assert(winner);
  assert(piece == 'X' || piece == 'O');

  if (single_dia_win(game->col_3, game->col_2, game->col_1, game->col_0,
                     piece, winner, h)) {
    return true;
  } else if (single_dia_win(game->col_4, game->col_3, game->col_2, game->col_1,
                            piece, winner, h)) {
    return true;
  } else if (single_dia_win(game->col_5, game->col_4, game->col_3, game->col_2,
                            piece, winner, h)) {
    return true;
  } else if (single_dia_win(game->col_6, game->col_5, game->col_4, game->col_3,
                            piece, winner, h)) {
    return true;
  } else {
    return false;
  }
}
// === CORE FUNCTIONS =========================================================
// see connect.h for documentation
bool is_full(const struct game_board *game, const int col, const int h) {
  assert(game);
  assert(col >= 0);
  assert(col <= 6);
  assert(h > 0);

  if (col == 0) {
    return is_full_col(game->col_0, h);
  } else if (col == 1) {
    return is_full_col(game->col_1, h);
  } else if (col == 2) {
    return is_full_col(game->col_2, h);
  } else if (col == 3) {
    return is_full_col(game->col_3, h);
  } else if (col == 4) {
    return is_full_col(game->col_4, h);
  } else if (col == 5) {
    return is_full_col(game->col_5, h);
  } else {
    return is_full_col(game->col_6, h);
  }
}

// see connect.h for documentation
bool is_all_full(const struct game_board *game, const int h, const int w) {
  assert(game);
  assert(h > 0);
  assert(w > 0);
  
  // define and initialize a boolean to record the result
  bool b = 1;
  
  for (int i = 0; i < w; ++i) {
    b = b && is_full(game, i, h);
  }
  
  return b;
}

// see connect.h for documentation
void game_update(struct game_board *game, const int col, const char piece,
                 const int h) {
  assert(game);
  assert(col >= 0);
  assert(col <= 6);
  assert(piece == 'X' || piece == 'O');

  if (col == 0) {
    update_col(game->col_0, piece, h);
    return;
  } else if (col == 1) {
    update_col(game->col_1, piece, h);
    return;
  } else if (col == 2) {
    update_col(game->col_2, piece, h);
    return;
  } else if (col == 3) {
    update_col(game->col_3, piece, h);
    return;
  } else if (col == 4) {
    update_col(game->col_4, piece, h);
    return;
  } else if (col == 5) {
    update_col(game->col_5, piece, h);
    return;
  } else {
    update_col(game->col_6, piece, h);
    return;
  }
}

// see connect.h for documentation
void game_print(const struct game_board *game, const int h) {
  assert(game);
  assert(h > 0);

  for (int i = h - 1; i >= 0; --i) {
    printf("|"); // prints "|" at each beginning of the row

    // prints the piece for i position in each column
    piece_print(game->col_0, i);
    piece_print(game->col_1, i);
    piece_print(game->col_2, i);
    piece_print(game->col_3, i);
    piece_print(game->col_4, i);
    piece_print(game->col_5, i);
    piece_print(game->col_6, i);

    printf("\n");
  }

  // prints the bottom row of numbers
  printf(" 0 1 2 3 4 5 6\n");
}

// see connect.h for documentation
bool game_winner(const struct game_board *game, char *winner, const int h) {
  assert(game);
  assert(winner);
  assert(h > 0);
  
  // check each piece one by one to see whether there is a winner
  if (col_win(game, 'X', winner, h) || row_win(game, 'X', winner, h) || 
      dia1_win(game, 'X', winner, h) || dia2_win(game, 'X', winner, h)) {
    return true;
  } else if (col_win(game, 'O', winner, h) || row_win(game, 'O', winner, h) || 
             dia1_win(game, 'O', winner, h) || dia2_win(game, 'O', winner, h)) {
    return true;
  } else {
    return false;
  }
}
