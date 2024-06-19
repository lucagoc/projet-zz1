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

    int joueur=0;

    int captured_white=0;
    int captured_black=0;
    int vic=0;  // 0 si partie en cours, 1 si noir gagne, 2 si blanc gagne

    int * captured_white_piece =captured_white;
    int * captured_black_piece =captured_black;
    int * victory = vic;
    int choice=0; //0 si le joueur respawn, 1 s'il joue (dans le cas où il a le choix)

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


        
        if (possible_piece()==0){ //aucune pièce jouable
            
            //il choisit

            if (choice==0) { //respawn
                respawn_piece();
            } else { //coup libre
                playing_move();
                //placer pièce et gérer capture
            }
        } else if (can_play()==0) { //blocage

            //adversaire choisit

            if (choice==0) { //respawn
                respawn_piece();
            } else { //coup libre
                playing_move();
                //placer pièce et gérer capture

            }
        } else { //coup

            while (is_valid_move() ==0){
                //choix piece, position
            }

            playing_move();
            //placer la pièce, gérer une capture ici

            while(valid_bird_placement==0){

            //choix placement piaf
            }
            //placer le piaf ici

        }



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

