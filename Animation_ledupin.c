#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

void resetbackground(SDL_Texture *mare, SDL_Renderer *renderer, SDL_Window *window)
{

    if (mare == NULL)
    {
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
    SDL_Rect rectangle;
    rectangle.x = 0;    // x haut gauche du rectangle
    rectangle.y = 0;    // y haut gauche du rectangle
    rectangle.w = 1920; // sa largeur (w = width)
    rectangle.h = 1080; // sa hauteur (h = height)

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rectangle);

    SDL_RenderCopy(renderer, mare,
                   &source,
                   &destination); // Création de l'élément à afficher
}

void affichercanard(SDL_Texture *canard, SDL_Renderer *renderer, SDL_Window *window, int x, int y)
{

    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(canard, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image

    float zoom = 1.5;                // Facteur de zoom à appliquer
    destination.w = source.w * zoom; // La destination est un zoom de la source
    destination.h = source.h * zoom; // La destination est un zoom de la source
    destination.x = x;
    destination.y = y;

    SDL_RenderCopy(renderer, canard, // Préparation de l'affichage
                   &source,
                   &destination);
}

void afficherherbes(SDL_Texture *herbe, SDL_Renderer *renderer, SDL_Window *window, int x, int y, float a, float b)
{

    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(herbe, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image

    destination.w = source.w * a; // La destination est un zoom de la source
    destination.h = source.h * b; // La destination est un zoom de la source
    destination.x = x;
    destination.y = y;

    SDL_RenderCopy(renderer, herbe, // Préparation de l'affichage
                   &source,
                   &destination);
}

void drawviseur(SDL_Renderer *renderer, int xv, int yv)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_RenderDrawLine(renderer,
                       xv - 15, yv, // x,y du point de la première extrémité
                       xv - 5, yv); // x,y seconde extrémité
    SDL_RenderDrawLine(renderer,
                       xv + 5, yv,   // x,y du point de la première extrémité
                       xv + 15, yv); // x,y seconde extrémité
    SDL_RenderDrawLine(renderer,
                       xv, yv - 15, // x,y du point de la première extrémité
                       xv, yv - 5); // x,y seconde extrémité
    SDL_RenderDrawLine(renderer,
                       xv, yv + 5,   // x,y du point de la première extrémité
                       xv, yv + 15); // x,y seconde extrémité

    //          SDL_RenderPresent(renderer); // affichage
}

void affiche(SDL_Renderer *renderer, SDL_Window *window)
{

    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);

    TTF_Font *font = NULL;                     // la variable 'police de caractère'
    font = TTF_OpenFont("./Pacifico.ttf", 65); // La police à charger, la taille désirée
    if (font == NULL)
        end_sdl(0, "Can't load font", window, renderer);

    TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD); // en italique, gras

    SDL_Color color = {255, 0, 0, 255};                         // la couleur du texte
    SDL_Surface *text_surface = NULL;                           // la surface  (uniquement transitoire)
    text_surface = TTF_RenderText_Blended(font, "pan!", color); // création du texte dans la surface
    if (text_surface == NULL)
        end_sdl(0, "Can't create text surface", window, renderer);

    SDL_Texture *text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL)
        end_sdl(0, "Can't create texture from surface", window, renderer);
    SDL_FreeSurface(text_surface); // la texture ne sert plus à rien

    SDL_Rect pos = {580, 250, 0, 0};                         // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);         // Ecriture du texte dans le renderer
    SDL_DestroyTexture(text_texture);                           // On n'a plus besoin de la texture avec le texte

    SDL_RenderPresent(renderer); // Affichage
    SDL_Delay(500);              // Pause en ms
}
int main()
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_DisplayMode screen;
    SDL_Texture *mare;
    SDL_Texture *canard;
    SDL_Texture *canarddte;
    SDL_Texture *herbe;

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
    herbe = IMG_LoadTexture(renderer, "./herbe.xcf");
    canard = IMG_LoadTexture(renderer, "./canard.xcf");
    canarddte = IMG_LoadTexture(renderer, "./canard2.xcf");

    int mouseX;
    int mouseY;
    float angle = 0;

    SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;                // c'est le type IMPORTANT !!

    while (program_on)
    { // Voilà la boucle des évènements



        if (SDL_PollEvent(&event))
        { // si la file d'évènements n'est pas vide : défiler l'élément en tête
            resetbackground(mare, renderer, window);
            if (angle < M_PI)
            {

                afficherherbes(herbe, renderer, window, angle * 15 - 200, -40, 1.2, 0.4);
                afficherherbes(herbe, renderer, window, angle * 40 - 200, 500, 1.2, 1);

                affichercanard(canarddte, renderer, window, 500 + 275 * cos(angle + M_PI), 100 + 90 * sin(angle + M_PI));
                affichercanard(canard, renderer, window, 500 + 275 * cos(angle), 100 + 90 * sin(angle));
            }
            else
            {

                afficherherbes(herbe, renderer, window, (angle - M_PI) * 15 - 200, -40, 1.2, 0.4);
                afficherherbes(herbe, renderer, window, (angle - M_PI) * 40 - 200, 500, 1.2, 1);

                affichercanard(canarddte, renderer, window, 500 + 250 * cos(angle), 100 + 75 * sin(angle));
                affichercanard(canard, renderer, window, 500 + 275 * cos(angle + M_PI), 100 + 90 * sin(angle + M_PI));
            }
            // de file dans 'event'
            switch (event.type)
            {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                exit(EXIT_SUCCESS);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                    exit(EXIT_SUCCESS);
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (SDL_BUTTON(SDL_BUTTON_LEFT) || SDL_BUTTON(SDL_BUTTON_RIGHT))
                { // Si c'est un click gauche

                    affiche(renderer, window);
                }
                break;

            case SDL_MOUSEMOTION: //  souris bouge

                SDL_GetMouseState(&mouseX, &mouseY);

                drawviseur(renderer, mouseX, mouseY);

                break;
            default: // L'évènement défilé ne nous intéresse pas
                break;
            }

            angle += M_PI / 100;
            if (angle >= 2 * M_PI)
            {
                angle = 0;
            }
            
            SDL_RenderPresent(renderer); // Affichage            SDL_Delay(80); // Pause en ms
            SDL_Delay(20); // Pause en ms
        }
    }
    SDL_Delay(2000); // Pause en ms

    IMG_Quit();

    return 0;
}
