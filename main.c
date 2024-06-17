#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

/********************************************/
/*  exemple de création de fenêtres en roue */
/********************************************/

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    const int n = 12; // Nombre de fenêtre qui tournent
    SDL_Window **window_tab = malloc(n * sizeof(SDL_Window *));

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    int center_x = DM.w/2;
    int center_y = DM.h/2;

    int window_size = 200;

    for (int i = 0; i < n; i++)
    {
        /* Création de la fenêtre */
        window_tab[i] = SDL_CreateWindow(
            "COUCOU",                 // codage en utf8, donc accents possibles
            0, 0,                     // coin haut gauche en haut gauche de l'écran
            window_size, window_size, // largeur = 400, hauteur = 300
            SDL_WINDOW_RESIZABLE);    // redimensionnable

        if (window_tab[i] == NULL)
        {
            SDL_Log("Error : SDL window creation - %s\n",
                    SDL_GetError()); // échec de la création de la fenêtre
            SDL_Quit();              // On referme la SDL
            exit(EXIT_FAILURE);
        }
    }

    float const max_radius = 300.0;
    for (int j = 0; j < 200; j++)
    {
        float rad = (2 * 3.14 / n);
        for (int i = 0; i < n; i++)
        {
            window_size = (1.0 - fabs(sin(10 * rad + j * 0.1)))*300;
            int x = max_radius*(1.0 - fabs(sin(10 * rad + j * 0.1))) * sin(i * rad + j * 0.1) + center_x - window_size/2;
            int y = max_radius*(1.0 - fabs(sin(10 * rad + j * 0.1))) * cos(i * rad + j * 0.1) + center_y - window_size/2;
            SDL_SetWindowPosition(window_tab[i], x, y);
            SDL_SetWindowSize(window_tab[i], window_size, window_size);
            SDL_Delay(3); // Pause exprimée  en ms
        }
    }

    /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
    for (int i = 0; i < n; i++)
    {
        SDL_DestroyWindow(window_tab[i]); // la fenêtre i
    }

    free(window_tab);

    SDL_Quit(); // la SDL

    return 0;
}