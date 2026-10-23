# comp120-project1

A C program that lets you play tic-tac-toe against the computer in the terminal.
You can play as many games as you like without restarting the program.

## How to compile and run

```
gcc tictactoe.c -o tic
./tic
```

## How to play

- You are **O** and you always go first. The computer is **X**.
- The board has 9 squares, numbered 0 to 8:

```
 0 | 1 | 2
---+---+---
 3 | 4 | 5
---+---+---
 6 | 7 | 8
```

- On your turn, you type the number of an empty square and press Enter.
- Squares that are still free show their number on the board. Taken squares show 0 or X.
- The computer picks a random empty square, so it is not a strong player.
- You win by getting three O's in a row (horizontally, vertically, or diagonally). If all 9 squares fill up and nobody has won, the game is a draw.
- After each game, enter `y` to play again or `q` to quit.

## Sample run

```
=====================================
        TIC-TAC-TOE vs COMPUTER
=====================================
You are O and you go first. The computer is X.
On your turn, type the number of an empty square:

 0 | 1 | 2
---+---+---
 3 | 4 | 5
---+---+---
 6 | 7 | 8

Your turn (O). Enter a square number (0-8): 4

 0 | 1 | 2
---+---+---
 3 | O | 5
---+---+---
 6 | 7 | 8

Computer (X) is thinking...
Computer (X) chose square 2. Your move next!

 0 | 1 | X
---+---+---
 3 | O | 5
---+---+---
 6 | 7 | 8

Your turn (O). Enter a square number (0-8): 4
  That square is already taken. Choose an empty one.
Your turn (O). Enter a square number (0-8): 
```


## Input Handling

If you enter something invalid, the program reports the error and asks again:

- A number outside 0 to 8 (for example `9`)
- A square that is already taken
- Something that is not a number (for example `abc`)
- Anything other than `y` or `q` at the play-again prompt

## How the program is organized

The program is split into small functions that each do one job:

| Function | Purpose |
|---|---|
| `init_board`|Sets all 9 squares to empty |
| `display_board`| Prints the board, showing the number of each empty square |
| `is_winner` | Returns `true` if a player has three in a row |
| `other_player` | Returns the opposite player/symbol |
| `get_human_move` | Asks until the user enters a valid empty square |
| `get_computer_move` | Picks a random empty square |
| `take_turn` | Lets the current player make one move |
| `play_game` | PLays one complete game |
| `play_again` | Asks whether to play another game |
| `clear_input_line` | Discards leftover character on the input line |

The board is stored in a 1-D `char` array of 9 elements, with `' '` for an empty square.
`rand()` is used for the computer's move, and `srand()` is called once at the start of the `main` so that games differ from run to run.
