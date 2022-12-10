# Tic-Tac-Toe

A simple implementation of the game Tic-Tac-Toe, written in C.

## Usage

To build the game, run the following command:

```
make
```

This will create an executable file called `tic-tac-toe`. To run the game, use the following command:

```
./tic-tac-toe
```

To clean up the directory and remove the executable, run the following command:

```
make clean
```

## How to Play

At the start of each game, the first player is randomly chosen (either the player or the computer). The players then take turns making moves, starting with the first player.

To make a move, the player specifies the coordinates of the square they want to occupy. The coordinates are entered as two integers, representing the row and column of the square, respectively. The top left square is (1, 1), and the bottom right square is (3, 3).

If a player occupies three squares in a row, column, or diagonal, they win the game. If all squares are occupied and no player has three in a row, the game ends in a draw.

The game board is represented by a 3x3 grid of characters, where each square is either occupied by a player's piece ('X' or 'O'), or is empty (' '). The game has a simple text-based user interface, where the game board is printed to the console after each move.

### Example

Suppose the player is X and the computer is O. The game starts with the following board:
```
   |   |   
---|---|---
   |   |   
---|---|---
   |   |   
```
The player's turn starts with the following prompt:
```
Enter coordinates (row column):
```
The player enters the coordinates of the square they want to occupy, for example:
```
Enter coordinates (row column): 2 3
```
This results in the following updated board:
```
   |   |   
---|---|---
   |   | X
---|---|---
   |   |   
```
The computer then makes a move, resulting in the following board:
```
   |   | O
---|---|---
   |   | X
---|---|---
   |   |   
```
The player and computer continue taking turns until the game ends.

## Credits

This game was developed by [MikeDX](http://github.com/MikeDX) and [Assistant](https://openai.com/blog/openai-api/).

## License

This code is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
