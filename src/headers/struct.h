#define STRUCT_H

#include <stdbool.h>

struct ui_s
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *textures[10];
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
};
typedef struct ui_s ui_t;

struct board_s
{
    int board_case[6][6];
    int board_piece[6][6];
};
typedef struct board_s board_t;

struct game_s
{
    SDL_Event event;
    int playing_player;
    bool inPause;
    bool program_on;
};
typedef struct game_s game_t;