#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "tic-tac-toe.h"

// game state
struct GameState {
    char player_piece;
    char opponent_piece;
    char game_board[3][3];
};

// global variables
struct GameState state;

int main() {
    bool player_turn;
    int game_result;
    char replay;

    srand(time(NULL)); // for randomizing first turn

    // game loop
    do {
        reset_board(&state);
        player_turn = randomize_first_turn(&state);

        // turn loop
        do {
            print_board(&state);

            if (player_turn) {
                player_turn = false;
                get_player_move(&state);
            } else {
                player_turn = true;
                get_computer_move(&state);
            }

            game_result = check_game_result(&state);

        } while (game_result == IN_PROGRESS);

        print_board(&state);

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

void reset_board(struct GameState *state) {
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            state->game_board[i][j] = ' ';
        }
    }
}

bool randomize_first_turn(struct GameState *state) {
    int random_number;

    random_number = rand() % 2;

    if (random_number == 0) {
        state->player_piece = 'X';
        state->opponent_piece = 'O';

        printf("You are X. Computer is O.\n");

        return true;
    } else {
        state->player_piece = 'O';
        state->opponent_piece = 'X';

        printf("Computer is X. You are O.\n");

        return false;
    }
}

void print_board(struct GameState *state) {
    int i;

    printf("\n");

    for (i = 0; i < 3; i++) {
        printf(" %c | %c | %c\n", state->game_board[i][0], state->game_board[i][1], state->game_board[i][2]);

        if (i != 2) {
            printf("---|---|---\n");
        }
    }

    printf("\n");
}

void get_player_move(struct GameState *state) {
    int x, y;

    printf("Enter coordinates (row column): ");
    scanf("%d%d", &x, &y);

    x--;
    y--;

    if (x < 0 || x > 2 || y < 0 || y > 2 || state->game_board[x][y] != ' ') {
        printf("\nInvalid move.\n");
        get_player_move(state);
    } else {
        state->game_board[x][y] = state->player_piece;
    }
}

int check_game_result(struct GameState *state) {
    int i, j;

    // check for player win
    for (i = 0; i < 3; i++) {
        if (state->game_board[i][0] == state->player_piece && state->game_board[i][1] == state->player_piece && state->game_board[i][2] == state->player_piece) {
            return PLAYER_WIN;
        }
    }

    for (i = 0; i < 3; i++) {
        if (state->game_board[0][i] == state->player_piece && state->game_board[1][i] == state->player_piece && state->game_board[2][i] == state->player_piece) {
            return PLAYER_WIN;
        }
    }

    if (state->game_board[0][0] == state->player_piece && state->game_board[1][1] == state->player_piece && state->game_board[2][2] == state->player_piece) {
        return PLAYER_WIN;
    }

    if (state->game_board[0][2] == state->player_piece && state->game_board[1][1] == state->player_piece && state->game_board           [2][0] == state->player_piece) {
        return PLAYER_WIN;
    }

    // check for opponent win
    for (i = 0; i < 3; i++) {
        if (state->game_board[i][0] == state->opponent_piece && state->game_board[i][1] == state->opponent_piece && state->game_board[i][2] == state->opponent_piece) {
            return COMPUTER_WIN;
        }
    }

    for (i = 0; i < 3; i++) {
        if (state->game_board[0][i] == state->opponent_piece && state->game_board[1][i] == state->opponent_piece && state->game_board[2][i] == state->opponent_piece) {
            return COMPUTER_WIN;
        }
    }

    if (state->game_board[0][0] == state->opponent_piece && state->game_board[1][1] == state->opponent_piece && state->game_board[2][2] == state->opponent_piece) {
        return COMPUTER_WIN;
    }

    if (state->game_board[0][2] == state->opponent_piece && state->game_board[1][1] == state->opponent_piece && state->game_board[2][0] == state->opponent_piece) {
        return COMPUTER_WIN;
    }

    // check for draw
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (state->game_board[i][j] == ' ') {
                return IN_PROGRESS;
            }
        }
    }

    return DRAW;
}

void get_computer_move(struct GameState *state) {
    int i, j;
    bool move_made = false;

    // try to win
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (state->game_board[i][j] == ' ') {
                state->game_board[i][j] = state->opponent_piece;

                if (check_game_result(state) == COMPUTER_WIN) {
                    move_made = true;
                    break;
                }

                state->game_board[i][j] = ' ';
            }
        }

        if (move_made) {
            break;
        }
    }

    // block player win
    if (!move_made) {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (state->game_board[i][j] == ' ') {
                    state->game_board[i][j] = state->player_piece;

                    if (check_game_result(state) == PLAYER_WIN) {
                        state->game_board[i][j] = state->opponent_piece;;
                        move_made = true;
                        break;
                    }

                    state->game_board[i][j] = ' ';
                }
            }

            if (move_made) {
                break;
            }
        }
    }

    // pick random empty square
    if (!move_made) {
        do {
            i = rand() % 3;
            j = rand() % 3;
        } while (state->game_board[i][j] != ' ');

        state->game_board[i][j] = state->opponent_piece;
    }
}



