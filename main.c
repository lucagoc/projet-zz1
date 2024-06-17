#include <SDL2/SDL.h>
#include <stdio.h>

/*****************************************/
/*  exemple de création de fenêtres en X */
/*****************************************/

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    // Nombre de fenêtre qui tournent
    int n = 6;
    SDL_Window **window_tab = malloc(n * sizeof(SDL_Window *));

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++)
    {
        /* Création de la fenêtre de gauche */
        window_tab[i] = SDL_CreateWindow(
            "COUCOU",    // codage en utf8, donc accents possibles
            0 + 100*i, 0 + 100*i,                  // coin haut gauche en haut gauche de l'écran
            300, 300,              // largeur = 400, hauteur = 300
            SDL_WINDOW_RESIZABLE); // redimensionnable

        if (window_tab[i] == NULL)
        {
            SDL_Log("Error : SDL window creation - %s\n",
                    SDL_GetError()); // échec de la création de la fenêtre
            SDL_Quit();              // On referme la SDL
            exit(EXIT_FAILURE);
        }
    }

    /* Normalement, on devrait ici remplir les fenêtres... */
    SDL_Delay(15000); // Pause exprimée  en ms

    /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
    SDL_DestroyWindow(window_1); // la fenêtre 1

    SDL_Quit(); // la SDL

    return 0;
}