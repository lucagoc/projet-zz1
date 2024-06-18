#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "headers/graphics.h"
#include "headers/rules.h"
#include "headers/opponent.h"

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

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);


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

    /* Initialisation du jeu */
    SDL_bool program_on = SDL_TRUE;
    SDL_Event event;

    int board_piece[6][6] = {0}; // Matrices des rhonins et daimios (= 1, 2, 3, 4)
    int board_case[6][6]; // Matrice des cases du plateau (= 1, 2 ou 3)
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
        draw(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, board_case, board_piece, inPause);
        SDL_RenderPresent(renderer);
        SDL_Delay(15); // ~ 60 FPS
    }

    
    end_sdl(0, "Le programme s'est terminé correctement", window, renderer);

    return 0;
}





void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer)
{
    char msg_formated[255];
    int l;

    if (!ok)
    {
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL)
    {                                  // Destruction si nécessaire du renderer
        SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
        renderer = NULL;
    }
    if (window != NULL)
    {                              // Destruction si nécessaire de la fenêtre
        SDL_DestroyWindow(window); // Attention : on suppose que les NULL sont maintenus !!
        window = NULL;
    }

    SDL_Quit();

    if (!ok)
    {
        exit(EXIT_FAILURE);
    }
}