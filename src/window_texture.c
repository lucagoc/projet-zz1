#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "headers/sdl_common.h"

SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Surface *my_image = NULL;   // Variable de passage
    SDL_Texture *my_texture = NULL; // La texture

    my_image = IMG_Load(file_image_name); // Chargement de l'image dans la surface
                                          // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL,
                                          // uniquement possible si l'image est au format bmp */
    if (my_image == NULL)
        end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire
    if (my_texture == NULL)
        end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}


int window_texture()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;

    /*********************************************************************************************************************/
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
           screen.w, screen.h);

    window = SDL_CreateWindow("Deuxième dessin",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screen.w,
                              screen.h,
                              SDL_WINDOW_OPENGL);

    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    SDL_bool program_on = SDL_TRUE;
    SDL_Event event;

    /* Load des textures */
    SDL_Texture *textures[4];
    textures[0] = load_texture_from_image("assets/background.png", window, renderer);
    textures[1] = load_texture_from_image("assets/background2.png", window, renderer);

    /* Load des sprites des étoiles */
    SDL_Texture *stars[4];
    stars[0] = load_texture_from_image("assets/stars/image0000.png", window, renderer);
    stars[1] = load_texture_from_image("assets/stars/image0001.png", window, renderer);
    stars[2] = load_texture_from_image("assets/stars/image0002.png", window, renderer);

    int frame = 0;
    bool jour = false;
    while (program_on)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;

            case SDL_KEYDOWN: // En cas d'appui d'une touche du clavier
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE: // Si c'est la barre d'espace
                    if (jour)
                    {
                        jour = false;
                    }
                    else
                    {
                        jour = true;
                    }
                    break;
                default:
                    break;
                }
                break;

            default: // L'évènement défilé ne nous intéresse pas
                break;
            }
        }

        if (!jour)
        {
           
            SDL_Rect window = {0, 0, screen.w, screen.h};
            SDL_RenderCopy(renderer, textures[1], NULL, &window);
            for (int i = 0; i < 13; i++)
            {
                SDL_Rect star = {100 + i * 200, 100, 100, 100};
                SDL_RenderCopy(renderer, stars[((frame/50) + i) % 3], NULL, &star);
            }
            for (int i = 0; i < 13; i++)
            {
                SDL_Rect star = {150 + i * 200, 300, 100, 100};
                SDL_RenderCopy(renderer, stars[((frame/50) + i) % 3], NULL, &star);
            }
        }
        else
        {
            SDL_Rect window = {0, 0, screen.w, screen.h};
            SDL_RenderCopy(renderer, textures[0], NULL, &window);

            
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10);

        frame++;
    }

    /* Destructions des textures */
    SDL_DestroyTexture(textures[0]);
    SDL_DestroyTexture(textures[1]);
    SDL_DestroyTexture(stars[0]);
    SDL_DestroyTexture(stars[1]);
    SDL_DestroyTexture(stars[2]);

    IMG_Quit(); // Si on charge une librairie SDL, il faut penser à la décharger

    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}