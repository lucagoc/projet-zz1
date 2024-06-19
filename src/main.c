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
const int BOARD_SIZE = 600;

#define GRID_SIZE 6

const int PLAYER_1 = 1;
const int PLAYER_2 = 2;


void init_game(game_t *game)
{
    game->playing_player = PLAYER_1;
    game->inPause = false;
    game->program_on = true;
    game->round = 0;
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
    ui->BOARD_SIZE = BOARD_SIZE;
    init_sdl(ui);

    /* Initialisation du jeu */
    game_t *game = malloc(sizeof(game_t));
    init_game(game);

    initialise_plateau(board->board_case);
    initialise_pieces(board->board_piece, 1, 1);

    /* Boucle principal */
    while (game->program_on)
    {
        get_input(ui, game);
        draw(ui, board);
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

