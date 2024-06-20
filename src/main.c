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
#include "headers/menu.h"

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
    game->selected_case = malloc(sizeof(pos_t));
    
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            game->predictions[i][j] = 0;
        }
        
    }
    
    if(game->selected_case == NULL){
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    game->selected_case->x = -1;
    game->selected_case->y = -1;
    
    game->case_is_selected = false;
    game->bird_is_selected = false;
    
    game->last_case_value = 0;
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
    board_t *board = malloc(sizeof(board_t));
    ui_t *ui = malloc(sizeof(ui_t));
    game_t *game = malloc(sizeof(game_t));
    
    ui->SCREEN_WIDTH = SCREEN_WIDTH;
    ui->SCREEN_HEIGHT = SCREEN_HEIGHT;
    ui->BOARD_SIZE = BOARD_SIZE;

    init_sdl(ui);
    init_game(game);
    initialise_plateau(board->board_case);
    board->bird = malloc(sizeof(pos_t));
    board->bird->x = -1; // position de l'oiseau en dehors du plateau
    board->bird->y = -1;
    initialise_pieces(board->board_piece, 1, 1);
    board->captured_black_pieces=0;
    board->captured_white_pieces=0;

    game->blocage=-1; //-1 si premier coup 0 si pas de blocage, 1 si joueur noir doit respawner, 2 si blanc doit respawner
    game->enable_respawn=0;
    /*
    // Charger les ressources pour le menu pause
    SDL_Texture *background_texture = NULL;
    SDL_Texture *continue_text = NULL;
    SDL_Texture *quit_text = NULL;

    if (!load_resources(ui->renderer, &background_texture, ui->window, &continue_text, &quit_text)) {
        // Gestion de l'échec du chargement des ressources
        SDL_Log("Échec du chargement des ressources");
        free(game);
        free(board);
        unload_textures(ui->textures);
        end_sdl(0, "Le programme s'est terminé correctement", ui->window, ui->renderer);
        free(ui);
        return -1;
    }

    // Définitions des rectangles des boutons pour le menu pause
    int text_width, text_height;

    SDL_QueryTexture(continue_text, NULL, NULL, &text_width, &text_height);
    SDL_Rect continue_button_rect = {ui->SCREEN_WIDTH / 2 - 100 - 5, 250, 200, text_height + 20};

    SDL_QueryTexture(quit_text, NULL, NULL, &text_width, &text_height);
    SDL_Rect quit_button_rect = {ui->SCREEN_WIDTH / 2 - 100, ui->SCREEN_HEIGHT - 200 - 10, 200, text_height + 20};
     */
    // Boucle principale
    while (game->program_on) {
        if (game->inPause) {
            // Afficher le menu pause
            /*draw_menu_pause(ui->renderer, background_texture, continue_text, quit_text);*/
        } else {
            // Afficher le plateau de jeu
            get_input(ui, game, board);
            draw(ui, board, game);
            SDL_RenderPresent(ui->renderer);
        }
        SDL_Delay(15); // ~ 60 FPS
    }

    // Libération des ressources et nettoyage
    /*
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(continue_text);
    SDL_DestroyTexture(quit_text);*/

    free(game);
    free(board);
    unload_textures(ui->textures);
    end_sdl(0, "Le programme s'est terminé correctement", ui->window, ui->renderer);
    free(ui);

    return 0;
}
