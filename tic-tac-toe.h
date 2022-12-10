#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#define IN_PROGRESS 2
#define PLAYER_WIN 1
#define COMPUTER_WIN 0
#define DRAW -1

void reset_board();
bool randomize_first_turn();
void print_board();
void get_player_move();
void get_computer_move();
int check_game_result();
int check_board_full();

#endif // TIC_TAC_TOE_H
