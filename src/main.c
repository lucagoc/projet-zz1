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

const int SCREEN_WIDTH = 1280;  
const int SCREEN_HEIGHT = 720;

const int PLAYER_1 = 1;
const int PLAYER_2 = 2;

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

    /* Initialisation SDL */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Création de la fenêtre et du renderer */
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
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
    SDL_bool program_on = SDL_TRUE;
    SDL_Event event;

    int board_piece[6][6] = {0}; // Matrices des rhonins et daimios (= 1, 2, 3, 4)
    int board_case[6][6]; // Matrice des cases du plateau (= 1, 2 ou 3)

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            board_case[i][j] = 1;
            board_piece[i][j] = 1;
        }
    }
    
    bool inPause = false;

    /* Boucle principal */
    while (program_on)
    {
        /* Gestion des événements */
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                program_on = SDL_FALSE;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int x = event.button.x;
                    int y = event.button.y;
                    printf("Clic en (%d, %d)\n", x, y);
                }
                break;
            }
        }

        /* Mise à jour de l'affichage */
        draw(renderer, textures, SCREEN_WIDTH, SCREEN_HEIGHT, board_case, board_piece, inPause);
        SDL_RenderPresent(renderer);
        SDL_Delay(15); // ~ 60 FPS
    }

    unload_textures(textures);
    end_sdl(0, "Le programme s'est terminé correctement", window, renderer);

    return 0;
}
