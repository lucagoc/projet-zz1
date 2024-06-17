#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/************************************/
/*  exemple de création de fenêtres */
/************************************/

int main()
{

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    SDL_Log("Error : SDL initialisation - %s\n",
            SDL_GetError()); // l'initialisation de la SDL a échoué
    exit(EXIT_FAILURE);
  }

  SDL_Window **tabfen = (SDL_Window **)malloc(30 * sizeof(SDL_Window *));

  for (int i = 0; i < 12; i++)
  {

    /* Création de la fenêtre de gauche */
    tabfen[i] = SDL_CreateWindow(
        "Fenêtre à gauche",    // codage en utf8, donc accents possibles
        i * 100 + 500, 500,    // coin haut gauche en haut gauche de l'écran
        150, 150,              // largeur = 400, hauteur = 300
        SDL_WINDOW_RESIZABLE); // redimensionnable

    if (tabfen[i] == NULL)
    {
      SDL_Log("Error : SDL window 1 creation - %s\n",
              SDL_GetError()); // échec de la création de la fenêtre
      SDL_Quit();              // On referme la SDL
      exit(EXIT_FAILURE);
    }

    SDL_Delay(25); // Pause exprimée  en ms
  }
  for (int i2 = 12; i2 < 24; i2++)
  {

    /* Création de la fenêtre de gauche */
    tabfen[i2] = SDL_CreateWindow(
        "Fenêtre à gauche",    // codage en utf8, donc accents possibles
        1000, (i2 - 12) * 150, // coin haut gauche en haut gauche de l'écran
        150, 150,              // largeur = 400, hauteur = 300
        SDL_WINDOW_RESIZABLE); // redimensionnable

    if (tabfen[i2] == NULL)
    {
      SDL_Log("Error : SDL window 1 creation - %s\n",
              SDL_GetError()); // échec de la création de la fenêtre
      SDL_Quit();              // On referme la SDL
      exit(EXIT_FAILURE);
    }
    SDL_Delay(25); // Pause exprimée  en ms
  }
  SDL_Delay(200); // Pause exprimée  en ms

  /* Normalement, on devrait ici remplir les fenêtres... */
  int k = 0;
  int n = 0;
  while (k < 400)
  {

    SDL_SetWindowPosition(tabfen[n], n * 100 + 500, 500 + round(300 * cos((n + (k / 12.)) / 6.)));
    SDL_SetWindowPosition(tabfen[n + 12], n * 100 + 500, (500 - round(300 * cos((n + (k / 12.)) / 6.))));

    n++;

    if (n == 12)
    {
      n = 0;
    }

    k++;
  }

  for (int i3 = 24; i3 < 31; i3++)
  {

    tabfen[i3] = SDL_CreateWindow(
        "Fenêtre à gauche",         // codage en utf8, donc accents possibles
        1050, 350 + 50 * (i3 - 24), // coin haut gauche en haut gauche de l'écran
        100, 150,                   // largeur = 400, hauteur = 300
        SDL_WINDOW_RESIZABLE);      // redimensionnable

    if (tabfen[i3] == NULL)
    {
      SDL_Log("Error : SDL window 1 creation - %s\n",
              SDL_GetError()); // échec de la création de la fenêtre
      SDL_Quit();              // On referme la SDL
      exit(EXIT_FAILURE);
    }
  }
  /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */

  SDL_Delay(1000); // Pause exprimée  en ms

  for (int j = 30; j >= 0; j--)
  {
    SDL_DestroyWindow(tabfen[j]); // la fenêtre 2
    SDL_Delay(100);               // Pause exprimée  en ms
  }

  SDL_Quit();
  free(tabfen);
  // la SDL

  return 0;
}