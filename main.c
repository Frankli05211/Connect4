#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "connect.h"

// === GLOBAL READONLY =======================================================
const int height = 6; // record the height of the game board
const int width = 7; // record the width of the game board

// === GLOBAL VARIABLE =======================================================
char winner = 0; // record the "name" of the winner


// === HELPER FUNCTION =======================================================

// col_set_up(col, h) modifies column col of the game board with the length h,
//   to set put the col we let each element be 0.
// effects: modifies col
void col_set_up(char col[], const int h) {
  assert(col);

  for (int i = 0; i < h; ++i) {
    col[i] = 0;
  }
}

// === MAIN FUNCTION =========================================================

int main(void) {
  // character keeps track of the piece putted in
  char piece = 0;
  // integer keeps track of which column the piece go
  int col = 0;

  // set up the game board, initialize board to its start configuration
  struct game_board game;
  col_set_up(game.col_0, height);
  col_set_up(game.col_1, height);
  col_set_up(game.col_2, height);
  col_set_up(game.col_3, height);
  col_set_up(game.col_4, height);
  col_set_up(game.col_5, height);
  col_set_up(game.col_6, height);

  // prints the initialized game board at the beginning
  game_print(&game, height);
  printf("\n");
  
  // run the game loop
  while (1) {
    // wait for player input
    if (scanf(" %c", &piece) != 1) {      // record the player's code
      printf("ERROR: cannot read player code\n");
      exit(EXIT_SUCCESS);
    } else if (scanf("%d", &col) != 1) {  // record the player's slot number
      printf("ERROR: cannot read slot number\n");
      exit(EXIT_SUCCESS);
    }

    // check for player's input
    if (piece != 'X' && piece != 'O') {   // check the player's code
      printf("ERROR: invalid player code: %c\n", piece);
      exit(EXIT_SUCCESS);
    } else if (col < 0 || col > 6) {      // check the player's slot number
      printf("ERROR: invalid slot number: %d\n", col);
      exit(EXIT_SUCCESS);
    }

    // check whether the selected col is full, if it is already full we prints
    //   error message and exit the program, if it is not full we update the
    //   game board to put the piece into the game
    if (is_full(&game, col, height)) {
      printf("ERROR: invalid slot number: %d\n", col);
      exit(EXIT_SUCCESS);
    } else {
      game_update(&game, col, piece, height);
    }
    
    // prints updated game board
    game_print(&game, height);
    printf("\n");
    
    // assess game state
    if (game_winner(&game, &winner, height)) {
      printf("Victory! Player %c has won!\n", winner);
      exit(EXIT_SUCCESS);
    } else if (is_all_full(&game, height, width)) {
      printf("Draw! No player has won!\n");
      exit(EXIT_SUCCESS);
    } else {
      continue;
    }
  }
  
  return EXIT_SUCCESS;
}
