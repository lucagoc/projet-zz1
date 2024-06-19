#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

#include "headers/struct.h"
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

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

#define BOARD_SIZE 6

const int PLAYER_1 = 1;
const int PLAYER_2 = 2;

/**
 * @brief Fonction pour récupérer les événements
 *
 * @param game Structure de l'état du jeu
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

void init_game(game_t *game)
{
    game->playing_player = PLAYER_1;
    game->inPause = false;
    game->program_on = true;
}

/**
 * @brief Fonction principale du jeu
 *
 * @param argc Nombre d'arguments
 * @param argv Arguments
 * @return int Code de retour
 */
int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    board_t *board = malloc(sizeof(board_t));
    ui_t *ui = malloc(sizeof(ui_t));
    ui->SCREEN_WIDTH = SCREEN_WIDTH;
    ui->SCREEN_HEIGHT = SCREEN_HEIGHT;
    init_sdl(ui);

    /* Initialisation du jeu */
    game_t *game = malloc(sizeof(game_t));
    init_game(game);

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
        draw(ui->renderer, ui->textures, SCREEN_WIDTH, SCREEN_HEIGHT, board_case, board_piece, game->inPause);
        SDL_RenderPresent(ui->renderer);
        SDL_Delay(15); // ~ 60 FPS
    }
    
    free(game);
    free(board);
    unload_textures(ui->textures);
    end_sdl(0, "Le programme s'est terminé correctement", ui->window, ui->renderer);
    free(ui);

    return 0;
}

