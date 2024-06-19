#define RULES_H

void initialise_plateau(int board[6][6]);
bool can_play(int player, int board[6][6], int OMx, int OMy, int pieces_position[6][6]);