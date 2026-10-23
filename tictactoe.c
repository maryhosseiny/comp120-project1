#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants
const int SIZE = 9;
const char HUMAN = 'O';
const char COMPUTER = 'X';
const char EMPTY = ' ';

// Function Declaration (make changes to board)
void init_board(char board[]);
void take_turn(char board[], char player);
void play_game(void);
bool play_again(void);
void clear_input_line(void);

// Function Declaration (reads from board)
void display_board(const char board[]);
bool is_winner(const char board[], char player);
char other_player(char player);
int get_human_move(const char board[]);
int get_computer_move(const char board[]);

// Main
int main(void) {
  srand((unsigned int)time(NULL));

  printf("=====================================\n");
  printf("        TIC-TAC-TOE vs COMPUTER\n");
  printf("=====================================\n");
  printf("You are %c and you go first. The computer is %c.\n", HUMAN, COMPUTER);
  printf("On your turn, type the number of an empty square.\n");

  do {
    play_game();
  } while (play_again());

  printf("Thanks for playing. Goodbye!\n");
  return 0;
}

// Set all 9 squares to empty
void init_board(char board[]) {
  for (int i = 0; i < SIZE; i++)
    board[i] = EMPTY;
}

// Displays either X/O or the square number if square available
void display_board(const char board[]) {
  char c[9];

  for (int i = 0; i < SIZE; i++) {
    if (board[i] == EMPTY)
      c[i] = '0' + i;
    else
      c[i] = board[i];
  }

  printf("\n");
  printf(" %c | %c | %c\n", c[0], c[1], c[2]);
  printf("---+---+---\n");
  printf(" %c | %c | %c\n", c[3], c[4], c[5]);
  printf("---+---+---\n");
  printf(" %c | %c | %c\n", c[6], c[7], c[8]);
  printf("\n");
}

// Return true if player gets three in a row, column, or cross
bool is_winner(const char board[], char player) {
  const int lines[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
                           {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

  for (int i = 0; i < 8; i++) {
    if (board[lines[i][0]] == player && board[lines[i][1]] == player &&
        board[lines[i][2]] == player) {
      return true;
    }
  }
  return false;
}

// throws away whatever is left on input line
void clear_input_line(void) {
  int ch = getchar();
  while (ch != '\n' && ch != EOF) {
    ch = getchar();
  }
}

// Responsible for switching turns between players
char other_player(char player) {
  if (player == HUMAN)
    return COMPUTER;
  else
    return HUMAN;
}

// asks until user inputs valid empty square(0-8)
int get_human_move(const char board[]) {
  int square;
  int result;
  bool valid = false;

  while (!valid) {
    printf("Your turn (%c). Enter a square number (0-8): ", HUMAN);
    result = scanf("%d", &square);

    if (result == EOF) {
      printf("\nInput ended. Goodbye!\n");
      exit(0);
    }
    clear_input_line();

    if (result != 1) {
      printf("  That is not a number. Enter a digit from 0 to 8.\n");
    } else if (square < 0 || square > 8) {
      printf("  %d is out of range. Enter a digit from 0 to 8.\n", square);
    } else if (board[square] != EMPTY) {
      printf("  That square is already taken. Choose an empty one.\n");
    } else {
      valid = true;
    }
  }
  return square;
}

// picks a random empty square for computer
int get_computer_move(const char board[]) {
  int square;

  do {
    square = rand() % SIZE;
  } while (board[square] != EMPTY);

  return square;
}

// updates the board with the move by play
void take_turn(char board[], char player) {
  int square;

  if (player == HUMAN) {
    square = get_human_move(board);
  } else {
    printf("Computer (%c) is thinking...\n", COMPUTER);
    square = get_computer_move(board);
    printf("Computer (%c) chose square %d.\n", COMPUTER, square);
  }
  board[square] = player;
}

// Playing one game
void play_game(void) {
  char board[9];
  char player = HUMAN;
  bool game_over = false;

  init_board(board);
  display_board(board);

  for (int turn = 0; turn < SIZE && !game_over; turn++) {
    take_turn(board, player);
    display_board(board);

    if (is_winner(board, player)) {
      if (player == HUMAN) {
        printf("*** You (%c) win! Congratulations! ***\n", HUMAN);
      } else {
        printf("*** Computer (%c) wins! Better luck next time. ***\n",
               COMPUTER);
      }
      game_over = true;

    } else {
      player = other_player(player);
      if (player == HUMAN && turn < SIZE - 1)
        printf("Your move next!\n");
    }
  }

  if (!game_over) {
    printf("*** It's a draw! ***\n");
  }
}

// asks whether player wants to play another game (y/q)
bool play_again(void) {
  char answer;
  bool valid = false;
  bool again = false;

  while (!valid) {
    printf("\nPlay again (y) or quit (q)?");

    if (scanf(" %c", &answer) == EOF)
      return false;
    clear_input_line();

    if (answer == 'Y' || answer == 'y' || answer == 'q' || answer == 'Q') {
      valid = true;
      again = (answer == 'y' || answer == 'Y');
    } else {
      printf("Please enter y or q.\n");
    }
  }

  if (again)
    printf("\n");
  return again;
}
