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

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    // window_go_round();
    window_render();

    SDL_Quit(); // la SDL

    return 0;
}