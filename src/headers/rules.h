#define RULES_H

void initialise_plateau(int board[6][6]);
bool can_play(int player, int board[6][6], int OMx, int OMy, int pieces_position[6][6]);
void initialise_pieces(int pieces_position[6][6], int king_black_position, int king_white_position);
list_t* predictions_calculations(game_t *game, board_t *board, pos_t piece_pos, int step, int player);