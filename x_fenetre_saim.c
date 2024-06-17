#include <SDL2/SDL.h>

#include <stdio.h>

#define WINDOW_WIDTH 100

#define WINDOW_HEIGHT 100

#define NUM_WINDOWS 5

#define SCREEN_WIDTH 640

#define SCREEN_HEIGHT 480

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {

        printf("SDL_Init Error: %s\n", SDL_GetError());

        return 1;

    }
     SDL_Window *windows[NUM_WINDOWS];

     SDL_Renderer *renderers[NUM_WINDOWS];

     int window_positions[NUM_WINDOWS][2] = {

          {SCREEN_WIDTH / 2 - WINDOW_WIDTH / 2, SCREEN_HEIGHT / 2 - WINDOW_HEIGHT / 2}, // Centre

          {SCREEN_WIDTH / 2 - WINDOW_WIDTH / 2, SCREEN_HEIGHT / 2 - WINDOW_HEIGHT / 2 - WINDOW_HEIGHT}, // Haut

          {SCREEN_WIDTH / 2 - WINDOW_WIDTH / 2, SCREEN_HEIGHT / 2 - WINDOW_HEIGHT / 2 + WINDOW_HEIGHT}, // Bas

          {SCREEN_WIDTH / 2 - WINDOW_WIDTH / 2 - WINDOW_WIDTH, SCREEN_HEIGHT / 2 - WINDOW_HEIGHT / 2}, // Gauche

          {SCREEN_WIDTH / 2 - WINDOW_WIDTH / 2 + WINDOW_WIDTH, SCREEN_HEIGHT / 2 - WINDOW_HEIGHT / 2} // Droite

     };

    // Créer les fenêtres et les rendus

    for (int i = 0; i < NUM_WINDOWS; i++) {

        windows[i] = SDL_CreateWindow("SDL2 Window",

                                      window_positions[i][0], window_positions[i][1],

                                      WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

        if (windows[i] == NULL) {

            printf("SDL_CreateWindow Error: %s\n", SDL_GetError());

            SDL_Quit();

            return 1;

        }

        renderers[i] = SDL_CreateRenderer(windows[i], -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (renderers[i] == NULL) {

            printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());

            SDL_Quit();

            return 1;

        }

    }

    SDL_Event e;

    int quit = 0;

    int color_change = 0;

    while (!quit) {

        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_QUIT) {

               quit = 1;

            }
        }

        // Animer les couleurs des fenêtres

        color_change = (color_change + 1) % 255;

        for (int i = 0; i < NUM_WINDOWS; i++) {

          SDL_SetRenderDrawColor(renderers[i], (color_change + i * 50) % 255, (color_change + i * 80) % 255, (color_change + i * 100) % 255, 255);

          SDL_RenderClear(renderers[i]);

          SDL_RenderPresent(renderers[i]);

        }

        SDL_Delay(50); // Attendre 50 ms pour ralentir l'animation

    }
    // Nettoyer les ressources
    for (int i = 0; i < NUM_WINDOWS; i++) {

        SDL_DestroyRenderer(renderers[i]);

        SDL_DestroyWindow(windows[i]);

    }

    SDL_Quit();

    return 0;

}