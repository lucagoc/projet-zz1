#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "headers/sdl_common.h"

/*********************************************************************************************************************/
/*                              Programme d'exemple de création de rendu + dessin                                    */
/*********************************************************************************************************************/


void draw_circle(SDL_Renderer *renderer, int radius, int thickness, int x, int y)
{
    int color_v = 0;
    for (int j = 0; j < thickness; j++)
    {
        for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 4000)
        {
            
            int alpha = 255 * j / thickness;
            SDL_SetRenderDrawColor(renderer,
                                   (cos(angle * 2 + color_v) + 1) * 255 / 2, // quantité de Rouge
                                   (cos(angle * 5 + color_v) + 1) * 255 / 2, //          de vert
                                   (cos(angle + color_v) + 1) * 255 / 2,     //          de bleu
                                   alpha);                         // opacité = opaque
            SDL_RenderDrawPoint(renderer,
                                x + (radius + j) * cos(angle),  // coordonnée en x
                                y + (radius + j) * sin(angle)); //            en y
                                color_v = (color_v + 1)%3;
        }
    }
}

void draw_snake(SDL_Renderer *renderer, int thickness, int number, int x, int y)
{
    if (number == 0)
    {
        return;
    }
    else
    {
        SDL_Rect rectangle;
        rectangle.x = x - number*thickness;        // x haut gauche du rectangle
        rectangle.y = y + 10*cos(x-number);        // y haut gauche du rectangle
        rectangle.w = thickness; // sa largeur (w = width)
        rectangle.h = thickness/2; // sa hauteur (h = height)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rectangle);
        rectangle.x = x - number*thickness;        // x haut gauche du rectangle
        rectangle.y = y + 10*cos(x-number);        // y haut gauche du rectangle
        rectangle.w = thickness-2; // sa largeur (w = width)
        rectangle.h = thickness/2-2; // sa hauteur (h = height)
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rectangle);
        draw_snake(renderer, thickness, number - 1, x, y);
    }
}

void draw(SDL_Renderer *renderer, SDL_DisplayMode screen, int frame)
{ // Je pense que vous allez faire moins laid :)
    SDL_Rect rectangle;

    // Background (Black)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // R G B A
    rectangle.x = 0;                                // x haut gauche du rectangle
    rectangle.y = 0;                                // y haut gauche du rectangle
    rectangle.w = screen.w;                         // sa largeur (w = width)
    rectangle.h = screen.h;                         // sa hauteur (h = height)
    SDL_RenderFillRect(renderer, &rectangle);

    draw_circle(renderer, 200 + 2*frame, 20, 200, 200);
    draw_snake(renderer, 20, 8, 200 + frame, 200);
    draw_snake(renderer, 20, 8, 400 + frame, 400);
    draw_snake(renderer, 20, 8, 600 + frame, 600);
    draw_snake(renderer, 20, 8, 100 + frame, 800);
    draw_snake(renderer, 20, 8, 900 + frame, 750);
    draw_snake(renderer, 20, 8, 250 + frame, 50);
}

int window_render()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;

    /*********************************************************************************************************************/
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
           screen.w, screen.h);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screen.w,
                              screen.h,
                              SDL_WINDOW_OPENGL);

    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /*********************************************************************************************************************/
    /*                                     On dessine dans le renderer                                                   */
    /*********************************************************************************************************************/

    SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;                // c'est le type IMPORTANT !!

    int frame = 0;
    while (program_on)
    { // Voilà la boucle des évènements

        if (SDL_PollEvent(&event))
        { // si la file d'évènements n'est pas vide : défiler l'élément en tête
          // de file dans 'event'
            switch (event.type)
            {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;

            default: // L'évènement défilé ne nous intéresse pas
                break;
            }
        }
        draw(renderer, screen, frame); // appel de la fonction qui crée l'image
        SDL_RenderPresent(renderer);   // affichage
        SDL_Delay(10);

        frame++;
    }

    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}