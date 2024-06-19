#define STRUCT_H

#include <SDL2/SDL.h>
#include <stdbool.h>

struct ui_s
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *textures[10];
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int BOARD_SIZE;
};
typedef struct ui_s ui_t;

struct pos_s
{
    int x;
    int y;
};
typedef struct pos_s pos_t;

struct board_s
{
    int board_case[6][6];
    int board_piece[6][6];
    pos_t *bird; // Position de l'oiseau
};
typedef struct board_s board_t;

struct game_s
{
    SDL_Event event;
    int playing_player;
    int round;
    bool inPause;
    bool program_on;
};
typedef struct game_s game_t;

// Liste de positions
struct list_s
{
    pos_t pos;
    struct list_s *next;
};
typedef struct list_s list_t;