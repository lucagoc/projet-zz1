#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

#include "headers/graphics.h"
#include "headers/rules.h"
#include "headers/opponent.h"
#include "headers/sdl_common.h"

/**
 * @file main.c
 * @brief Programme principal du jeu Mana
 * @version 1.0
 * @date 2023-06-18
 * @author Team 21
 */

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

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

#define BOARD_SIZE 6

const int PLAYER_1 = 1;
const int PLAYER_2 = 2;

/**
 * @brief Fonction principale du jeu
 *
 * @param argc Nombre d'arguments
 * @param argv Arguments
 * @return int Code de retour
 */

void get_input(game_t *game)
{
    /* Gestion des événements */
    while (SDL_PollEvent(&game->event))
    {
        switch (game->event.type)
        {
        case SDL_QUIT:
            game->program_on = SDL_FALSE;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (game->event.button.button == SDL_BUTTON_LEFT)
            {
                int x = game->event.button.x;
                int y = game->event.button.y;
                printf("Clic en (%d, %d)\n", x, y);
            }
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    /* Initialisation de la SDL */
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    /* Initialisation SDL */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Création de la fenêtre et du renderer */
    window = SDL_CreateWindow("Mana (pre-alpha)",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);

    /* Loading de toutes les textures dans un tableau */
    SDL_Texture *textures[10];
    load_textures(textures, renderer, window);

    /* Initialisation du jeu */
    game_t *game = malloc(sizeof(game_t));
    game->program_on = true;
    game->inPause = false;
    game->playing_player = PLAYER_1;

    int board_piece[BOARD_SIZE][BOARD_SIZE]; // Matrices des rhonins et daimios (= 1, 2, 3, 4)
    int board_case[BOARD_SIZE][BOARD_SIZE];  // Matrice des cases du plateau (= 1, 2 ou 3)

    initialise_plateau(board_case);

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board_piece[i][j] = 0;
        }
    }

    /* Boucle principal */
    while (game->program_on)
    {
        get_input(game);
        draw(renderer, textures, SCREEN_WIDTH, SCREEN_HEIGHT, board_case, board_piece, game->inPause);
        SDL_RenderPresent(renderer);
        SDL_Delay(15); // ~ 60 FPS
    }

    free(game);
    unload_textures(textures);
    end_sdl(0, "Le programme s'est terminé correctement", window, renderer);

    return 0;
}

