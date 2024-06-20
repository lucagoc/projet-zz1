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
//#include "headers/menu.h"

/**
 * @file main.c
 * @brief Programme principal du jeu Mana
 * @version 1.0
 * @date 2023-06-18
 * @author Team 21
 */

#define GRID_SIZE 6

const int PLAYER_1 = 1;
const int PLAYER_2 = 2;

void init_game_state(game_state_t *game_state)
{
    game_state->player = PLAYER_1;
    game_state->round = 0;
    game_state->last_case = 0;
    game_state->player_blocked = false;
    game_state->phase = 0;

    game_state->captured_pieces[0] = 0; // Inutilisé
    game_state->captured_pieces[1] = 0;
    game_state->captured_pieces[2] = 0;
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

    // Allocation et initialisation des structures
    ui_t *ui = malloc(sizeof(ui_t));
    init_ui(ui);
    game_state_t *game_state = malloc(sizeof(game_state_t));
    init_game_state(game_state);
    
    game_state->board = malloc(sizeof(board_t));
    if (game_state->board == NULL)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    
    game_state->board = init_board(game_state->board);

    input_t *input = malloc(sizeof(input_t));
    init_input(input);

    

    bool in_pause = false;
    
    // Boucle principale
    while (ui->program_on)
    {
        get_input(ui, input);
        if (!in_pause)
        {
            game_logic(game_state, input);
        }
        else
        {
            //menu_logic(ui, input); // menu.c
        }
        draw(ui, game_state, input);
        SDL_RenderPresent(ui->renderer);
        SDL_Delay(15); // ~ 60 FPS
    }

    free(game_state); // Attention à bien free imbriqué dedans !
    unload_textures(ui->textures);
    end_sdl(0, "Le programme s'est terminé correctement", ui->window, ui->renderer);
    free(ui);

    return 0;
}
