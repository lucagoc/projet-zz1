#include <SDL2/SDL.h>

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <math.h>



#define WINDOW_WIDTH 100

#define WINDOW_HEIGHT 100

#define NUM_WINDOWS 8

#define SCREEN_WIDTH 640

#define SCREEN_HEIGHT 480

#define RADIUS 200



void create_window(int x, int y, int id) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {

        printf("SDL_Init Error: %s\n", SDL_GetError());

        exit(1);

    }
    char title[50];
    snprintf(title, sizeof(title), "SDL2 Window %d", id);

    SDL_Window *window = SDL_CreateWindow(title, x, y, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {

        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());

        SDL_Quit();

        exit(1);

    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {

        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());

        SDL_DestroyWindow(window);

        SDL_Quit();

        exit(1);

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



        color_change = (color_change + 1) % 255;

        SDL_SetRenderDrawColor(renderer, (color_change + id * 50) % 255, (color_change + id * 80) % 255, (color_change + id * 100) % 255, 255);

        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);



        SDL_Delay(30); // Attendre 50 ms pour ralentir l'animation

    }

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    exit(0);

}

int main(int argc, char *argv[]) {

    int center_x = SCREEN_WIDTH / 2;

    int center_y = SCREEN_HEIGHT / 2;



    for (int i = 0; i < NUM_WINDOWS; i++) {

        double angle = 2 * M_PI * i / NUM_WINDOWS;

        int x = center_x + RADIUS * cos(angle) - WINDOW_WIDTH / 2;

        int y = center_y + RADIUS * sin(angle) - WINDOW_HEIGHT / 2;

        pid_t pid = fork();

        if (pid == 0) {

            create_window(x, y, i);

        } else if (pid < 0) {

            printf("Fork failed\n");

            return 1;

        }

    }

    // Attendre que tous les processus enfants se terminent

    for (int i = 0; i < NUM_WINDOWS; i++) {

        continue;

    }

    return 0;

}