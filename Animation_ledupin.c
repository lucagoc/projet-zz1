#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL_image.h>
#define M_PI 3.14159265358979323846

void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer)
{ // renderer à fermer

    char msg_formated[255];
    int l;

    if (!ok)
    { // Affichage de ce qui ne va pas
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
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

void resetbackground(    SDL_Texture *mare, SDL_Renderer *renderer, SDL_Window *window)
{


    if (mare == NULL){
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    }
    
    // affichage et gestion de l'animation

    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer
    
    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre

    destination = window_dimensions; // On fixe les dimensions de l'affichage à  celles de la fenêtre

    SDL_QueryTexture(mare, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image

    SDL_RenderCopy(renderer, mare,
                   &source,
                   &destination); // Création de l'élément à afficher
}

void affichercanard(SDL_Texture *canard, SDL_Renderer *renderer, SDL_Window *window, int x, int y)
{    

    SDL_Rect 
         source = {0},                      // Rectangle définissant la zone de la texture à récupérer
         window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
         destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
       window, &window_dimensions.w,
       &window_dimensions.h);               // Récupération des dimensions de la fenêtre
       SDL_QueryTexture(canard, NULL, NULL,
            &source.w, &source.h);  // Récupération des dimensions de l'image

       float zoom = 1.5;                        // Facteur de zoom à appliquer    
       destination.w = source.w * zoom;         // La destination est un zoom de la source
       destination.h = source.h * zoom;         // La destination est un zoom de la source
       destination.x = x;       
       destination.y = y;

       SDL_RenderCopy(renderer, canard,     // Préparation de l'affichage  
              &source,
              &destination);            
}

int main()
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_DisplayMode screen;
    SDL_Texture *mare;
    SDL_Texture *canard;
    SDL_Texture *canarddte;


    /*********************************************************************************************************************/
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        end_sdl(0, "ERROR SDL INIT", window, renderer);
    }

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
           screen.w, screen.h);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
                              screen.h * 0.66,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
    }

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */
    
    mare = IMG_LoadTexture(renderer, "./mare.xcf");

    canard = IMG_LoadTexture(renderer, "./canard.xcf");
    canarddte = IMG_LoadTexture(renderer, "./canard2.xcf");























    int x=500;
    int y=100;
    for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 100)    {

        resetbackground(mare, renderer, window);
        if(angle<M_PI){
            affichercanard(canard, renderer, window, x+275*cos(angle), y+90*sin(angle));
            affichercanard(canarddte, renderer, window, x+275*cos(angle+M_PI), y+90*sin(angle+M_PI));

        } else {

            affichercanard(canarddte, renderer, window, x+250*cos(angle), y+75*sin(angle));
            affichercanard(canard, renderer, window, x+275*cos(angle+M_PI), y+90*sin(angle+M_PI));

        }

        SDL_Delay(20);             // Pause en ms
        SDL_RenderPresent(renderer); // Affichage
    }

    SDL_Delay(2000);             // Pause en ms

    IMG_Quit();

    return 0;
}
