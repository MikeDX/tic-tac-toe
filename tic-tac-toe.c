#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "tic-tac-toe.h"

// global variables
char player_piece;
char opponent_piece;
char game_board[3][3];

int main() {
    bool player_turn;
    int game_result;
    char replay;

    srand(time(NULL)); // for randomizing first turn

    // game loop
    do {
        reset_board();
        player_turn = randomize_first_turn();

        // turn loop
        do {
            print_board();

            if (player_turn) {
                player_turn = false;
                get_player_move();
            } else {
                player_turn = true;
                get_computer_move();
            }

            game_result = check_game_result();

        } while (game_result == IN_PROGRESS);

        print_board();

        if (game_result == PLAYER_WIN) {
            printf("You win!\n");
        } else if (game_result == COMPUTER_WIN) {
            printf("Computer wins!\n");
        } else {
            printf("It's a draw!\n");
        }

        printf("Play again (Y/N)? ");
        scanf(" %c", &replay);

    } while (replay == 'Y' || replay == 'y');

    return 0;
}

void reset_board() {
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            game_board[i][j] = ' ';
        }
    }
}

bool randomize_first_turn() {
    int random_number;

    random_number = rand() % 2;

    if (random_number == 0) {
        player_piece = 'X';
        opponent_piece = 'O';

        printf("You are X. Computer is O.\n");

        return true;
    } else {
        player_piece = 'O';
        opponent_piece = 'X';

        printf("Computer is X. You are O.\n");

        return false;
    }
}

void print_board() {
    int i;

    printf("\n");

    for (i = 0; i < 3; i++) {
        printf(" %c | %c | %c\n", game_board[i][0], game_board[i][1], game_board[i][2]);

        if (i != 2) {
            printf("---|---|---\n");
        }
    }

    printf("\n");
}

void get_player_move() {
    int x, y;

    printf("Enter coordinates (row column): ");
    scanf("%d%d", &x, &y);

    x--;
    y--;

    if (game_board[x][y] != ' ') {
        printf("\nSquare is already occupied.\n");
        get_player_move();
    } else {
        game_board[x][y] = player_piece;
    }
}

int check_game_result() {
    int i, j;

    // check for player win
    for (i = 0; i < 3; i++) {
        if (game_board[i][0] == player_piece && game_board[i][1] == player_piece && game_board[i][2] == player_piece) {
            return PLAYER_WIN;
        }
    }

    for (i = 0; i < 3; i++) {
        if (game_board[0][i] == player_piece && game_board[1][i] == player_piece && game_board[2][i] == player_piece) {
            return PLAYER_WIN;
        }
    }

    if (game_board[0][0] == player_piece && game_board[1][1] == player_piece && game_board[2][2] == player_piece) {
        return PLAYER_WIN;
    }

    if (game_board[0][2] == player_piece && game_board[1][1] == player_piece && game_board[2][0] == player_piece) {
        return PLAYER_WIN;
    }

    // check for computer win
    for (i = 0; i < 3; i++) {
        if (game_board[i][0] == opponent_piece && game_board[i][1] == opponent_piece && game_board[i][2] == opponent_piece) {
            return COMPUTER_WIN;
        }
    }

    for (i = 0; i < 3; i++) {
        if (game_board[0][i] == opponent_piece && game_board[1][i] == opponent_piece && game_board[2][i] == opponent_piece) {
            return COMPUTER_WIN;
        }
    }

    if (game_board[0][0] == opponent_piece && game_board[1][1] == opponent_piece && game_board[2][2] == opponent_piece) {
        return COMPUTER_WIN;
    }

    if (game_board[0][2] == opponent_piece && game_board[1][1] == opponent_piece && game_board[2][0] == opponent_piece) {
        return COMPUTER_WIN;
    }

    // check for draw
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (game_board[i][j] == ' ') {
                return IN_PROGRESS;
            }
        }
    }

    return DRAW;
}

void get_computer_move() {
    int x, y;
    bool found_move = false;

    // try to find a winning move for the computer
    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            if (game_board[x][y] == ' ') {
                game_board[x][y] = opponent_piece;

                if (check_game_result() == COMPUTER_WIN) {
                    found_move = true;
                    break;
                }

                game_board[x][y] = ' ';
            }
        }

        if (found_move) {
            break;
        }
    }

    // if there is no winning move, try to block the player's winning move
    if (!found_move) {
        for (x = 0; x < 3; x++) {
            for (y = 0; y < 3; y++) {
                if (game_board[x][y] == ' ') {
                    game_board[x][y] = player_piece;

                    if (check_game_result() == PLAYER_WIN) {
                        game_board[x][y] = opponent_piece;
                        found_move = true;
                        break;
                    }

                    game_board[x][y] = ' ';
                }
            }

            if (found_move) {
                break;
            }
        }
    }

    // if there is no winning or blocking move, choose a random empty square
    if (!found_move) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (game_board[x][y] != ' ');

        game_board[x][y] = opponent_piece;
    }
}
