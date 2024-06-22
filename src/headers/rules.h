#define RULES_H

void init_game_state(game_state_t *game_state);
board_t* init_board(board_t *board);
bool is_daimyo(pos_t position, board_t *board);
bool is_pos_valid(pos_t position);
bool is_pos_empty(pos_t position, board_t *board);
int is_pos_occupied(pos_t position, board_t *board);
bool is_move_valid_play(pos_t destination, board_t *board, input_t *input, int player);
bool is_move_valid(pos_t origin, pos_t destination, board_t *board, int player);
list_t* list_rhonin_possible_moves(pos_t position, board_t *board, int step, int player);
list_t *list_bird_possible_moves(game_state_t *game_state);
void move_piece(pos_t origin, pos_t destination, game_state_t *game_state);
int who_wins(board_t *board);
void game_logic(game_state_t *game_state, input_t *input);
void game_logic_2(game_state_t *game_state, input_t *input);