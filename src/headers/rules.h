#define RULES_H
#define GRID_SIZE 6

void initialise_plateau(int board[6][6]);
void initialise_pieces(int pieces_position[6][6], int king_black_position, int king_white_position);

bool can_play(int player, int board[6][6], int OMx, int OMy, int pieces_position[6][6]);
bool is_valid_move(int valid, int number_moves, int pieces_position[GRID_SIZE][GRID_SIZE], int xinit, int yinit, int xprev, int yprev, int xdesti, int ydesti);
bool possible_piece(int player, int board[GRID_SIZE][GRID_SIZE], int xprev, int yprev, int position_piece[GRID_SIZE][GRID_SIZE]);
bool valid_bird_placement(int xinit, int yinit, int birdX, int birdY, int pieces_position[GRID_SIZE][GRID_SIZE], int board[GRID_SIZE][GRID_SIZE]);

int number_moves_to_play(int board[6][6], int xinit, int yinit);

bool playing_move(int player, int *victory, int *captured_black_piece, int *captured_white_piece, int pieces_position[GRID_SIZE][GRID_SIZE], int board[6][6], int xinit, int yinit, int xdesti, int ydesti);
bool respawn_piece(int player, int captured_white_piece, int captured_black_piece, int pieces_position[GRID_SIZE][GRID_SIZE], int xres, int yres);
