#include <SDL2/SDL.h>

#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include "pave_serpent_saim.h"


#define WINDOW_WIDTH 800

#define WINDOW_HEIGHT 600

#define SNAKE_SIZE 20

#define INITIAL_LENGTH 5



void init_snake(Snake *snake) {

    snake->length = INITIAL_LENGTH;

    snake->body = (Point *)malloc(snake->length * sizeof(Point));

    for (int i = 0; i < snake->length; i++) {

        snake->body[i].x = WINDOW_WIDTH / 2 - i * SNAKE_SIZE;

        snake->body[i].y = WINDOW_HEIGHT / 2;

    }

    snake->dir_x = SNAKE_SIZE;

    snake->dir_y = 0;

}



void move_snake(Snake *snake) {

    for (int i = snake->length - 1; i > 0; i--) {

        snake->body[i] = snake->body[i - 1];

    }

    snake->body[0].x += snake->dir_x;

    snake->body[0].y += snake->dir_y;

}



void render_snake(SDL_Renderer *renderer, Snake *snake) {

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    for (int i = 0; i < snake->length; i++) {

        SDL_Rect rect = {snake->body[i].x, snake->body[i].y, SNAKE_SIZE, SNAKE_SIZE};

        SDL_RenderFillRect(renderer, &rect);

    }

}



int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {

        printf("SDL_Init Error: %s\n", SDL_GetError());

        return 1;

    }



    SDL_Window *window = SDL_CreateWindow("Snake",

                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,

                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {

        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());

        SDL_Quit();

        return 1;

    }



    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {

        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());

        SDL_DestroyWindow(window);

        SDL_Quit();

        return 1;

    }



    Snake snake;

    init_snake(&snake);



    SDL_Event e;

    int quit = 0;



    while (!quit) {

        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_QUIT) {

                quit = 1;

            } else if (e.type == SDL_KEYDOWN) {

                switch (e.key.keysym.sym) {
                    
                    case SDLK_UP:

                        if (snake.dir_y == 0) {

                            snake.dir_x = 0;

                            snake.dir_y = -SNAKE_SIZE;

                        }

                        break;

                    case SDLK_DOWN:

                        if (snake.dir_y == 0) {

                            snake.dir_x = 0;

                            snake.dir_y = SNAKE_SIZE;

                        }

                        break;

                    case SDLK_LEFT:

                        if (snake.dir_x == 0) {

                            snake.dir_x = -SNAKE_SIZE;

                            snake.dir_y = 0;

                        }

                        break;

                    case SDLK_RIGHT:

                        if (snake.dir_x == 0) {

                            snake.dir_x = SNAKE_SIZE;

                            snake.dir_y = 0;

                        }

                        break;

                }

            }

        }



        move_snake(&snake);



        SDL_SetRenderDrawColor(renderer, 0, 25, 38, 255);

        SDL_RenderClear(renderer);



        render_snake(renderer, &snake);



        SDL_RenderPresent(renderer);



        SDL_Delay(60); // Vitesse du serpent

    }



    free(snake.body);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
