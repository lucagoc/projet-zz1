#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define M_PI 3.14159265358979323846

/*********************************************************************************************************************/
/*                              Programme d'exemple de création de rendu + dessin                                    */
/*********************************************************************************************************************/
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

void resetbackground(SDL_Renderer *renderer)
{

    SDL_Rect rectangle;

    rectangle.x = 0;    // x haut gauche du rectangle
    rectangle.y = 0;    // y haut gauche du rectangle
    rectangle.w = 1920; // sa largeur (w = width)
    rectangle.h = 1080; // sa hauteur (h = height)

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rectangle);

    rectangle.x = 0;    // x haut gauche du rectangle
    rectangle.y = 0;    // y haut gauche du rectangle
    rectangle.w = 1920; // sa largeur (w = width)
    rectangle.h = 100; // sa hauteur (h = height)
    SDL_SetRenderDrawColor(renderer, 0, 100, 100, 100);
    SDL_RenderFillRect(renderer, &rectangle);

    for (int largeur=0;largeur <1200; largeur+=300 ){

        for (int hauteur=-175; hauteur<225; hauteur+=200){

                int largrand= largeur + rand()%100;
                int hautrand= hauteur + rand()%50;
                rectangle.x = largrand;    // x haut gauche du rectangle
                rectangle.y = hautrand;    // y haut gauche du rectangle
                rectangle.w = largrand +5; // sa largeur (w = width)
                rectangle.h = hautrand +5; // sa hauteur (h = height)
                
                SDL_SetRenderDrawColor(renderer, 0, 100, 100, 100);
                SDL_RenderFillRect(renderer, &rectangle);




        }
        
                int largrand2= largeur + rand()%100;

                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

                SDL_RenderDrawLine(renderer,                             
                                    largrand2+5,100,                                          // x,y du point de la première extrémité
                                    largrand2+15, 165);                                // x,y seconde extrémité

                SDL_RenderDrawLine(renderer,                             
                                    largrand2+15,165,                                          // x,y du point de la première extrémité
                                    largrand2-5, 190);                                // x,y seconde extrémité

                SDL_RenderDrawLine(renderer,                             
                                    largrand2-5,190,                                          // x,y du point de la première extrémité
                                    largrand2+5, 210);                                // x,y seconde extrémité
    }


}

void affichecercle(SDL_Renderer *renderer, float angle, int k, int j, int x, int y)
{
    SDL_SetRenderDrawColor(renderer,
                           (cos(angle * 2) + 1) * 255 / 2, // quantité de Rouge
                           (cos(angle * 5) + 1) * 255 / 2, //          de vert
                           (cos(angle) + 1) * 255 / 2,     //          de bleu
                           255);                           // opacité = opaque
    SDL_RenderDrawPoint(renderer,
                        x + (175 + k + j) * cos(angle), // coordonnée en x     200 + (100 + k + j) * cos(angle)
                        y + (25 + k + j) * sin(angle)); //            en y     200 + (150 + k + j) * sin(angle)
}

void draw(SDL_Renderer *renderer, int k, int x, int y)
{

    resetbackground(renderer);

    for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 2000)
    {
        for (int j = 0; j < 5; j++)
        {

            affichecercle(renderer, angle, k, j, x, y);

            if (k > 20)
            {
                affichecercle(renderer, angle, k - 20, j, x, y);
            }

            if (k > 35)
            {
                affichecercle(renderer, angle, k - 35, j, x, y);
            }
        }
    }
}

void drawgoutte(SDL_Renderer *renderer, int xg, int yg)
{
    resetbackground(renderer);

    SDL_SetRenderDrawColor(renderer, 0 , 0, 255, 255);

    for (float anglegoutte = 0; anglegoutte < 2 * M_PI; anglegoutte += M_PI / 100)
    {
        for (int epaisseur = 0; epaisseur < 8 ; epaisseur++)
        {
    
            SDL_RenderDrawPoint(renderer,
                                xg + (2 + epaisseur) * cos(anglegoutte), // coordonnée en x     200 + (100 + k + j) * cos(angle)
                                yg + (4 + epaisseur) * sin(anglegoutte)); //            en y     200 + (150 + k + j) * sin(angle)
        }

    }
    SDL_RenderPresent(renderer); // affichage

}

int main()
{
    srand(time(0));
    int lancement = 0;

    int mouseY;
    int mouseX;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;

    /*********************************************************************************************************************/
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);

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
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /*********************************************************************************************************************/
    /*                                     On dessine dans le renderer                                                   */
    /*********************************************************************************************************************/
    /*             Cette partie pourrait avantageusement être remplacée par la boucle évènementielle                     */

    SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;                // c'est le type IMPORTANT !!

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
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                    exit(EXIT_SUCCESS);
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                    if (SDL_BUTTON(SDL_BUTTON_LEFT) || SDL_BUTTON(SDL_BUTTON_RIGHT))
                    { // Si c'est un click gauche


                        for (int anim = 0; anim<5; anim++ ){
                            
                            SDL_GetMouseState(&mouseX, &mouseY);

                            drawgoutte(renderer, mouseX, mouseY + anim*30);

                            SDL_Delay(100); // Pause exprimée en ms

                        }
                        
                        lancement = 1;
                    }
                break;

            case SDL_MOUSEMOTION: // Click souris                    


                SDL_GetMouseState(&mouseX, &mouseY);

                drawgoutte(renderer, mouseX, mouseY);
                break;
            default: // L'évènement défilé ne nous intéresse pas
                break;
            }

            if (lancement)
            {
                for (int k = 0; k < 50; k+=5)
                {
                    draw(renderer, k, mouseX, mouseY +150); // appel de la fonction qui crée l'image

                    SDL_RenderPresent(renderer); // affichage
                
                    SDL_Delay(100); // Pause exprimée en ms

                }

                lancement = 0;

            }

            
        }
    }

    SDL_Delay(2000); // Pause exprimée en ms

    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}