#include <SDL2/SDL.h>

#include <stdbool.h>


const int WINDOW_WIDTH = 800;

const int WINDOW_HEIGHT = 600;

const int FPS = 60;

const int FRAME_DELAY = 1200 / FPS;


typedef struct {

    int x, y;

    SDL_Texture* texture;

} Entity;


void initSDL(SDL_Window** window, SDL_Renderer** renderer) {

    SDL_Init(SDL_INIT_VIDEO);

    *window = SDL_CreateWindow("SDL2 Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

}


SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {

    SDL_Surface* surface = SDL_LoadBMP(path);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    return texture;

}


void handleEvents(bool* running) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {

            *running = false;

        }

    }

}


void update(Entity* character, Entity* path, int* frame, int* frameCount) {

    *frameCount += 1;

    if (*frameCount >= FPS / 10) { // Change frame tous les 0.1 s

        *frame = (*frame + 1) % 3;

        *frameCount = 0;

    }

    character->x += 2;

    if (character->x > WINDOW_WIDTH) {

        character->x = -64; 

    }


    path->x -= 2;

    if (path->x <= -WINDOW_WIDTH) {

        path->x = 0;

    }

}


void render(SDL_Renderer* renderer, Entity* background, Entity* path, Entity* character, SDL_Rect* srcRects) {

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, background->texture, NULL, NULL); // Background

    

    // Render path twice to create a scrolling effect

    SDL_Rect pathDest1 = { path->x, path->y, WINDOW_WIDTH, WINDOW_HEIGHT };

    SDL_Rect pathDest2 = { path->x + WINDOW_WIDTH, path->y, WINDOW_WIDTH, WINDOW_HEIGHT };

    SDL_RenderCopy(renderer, path->texture, NULL, &pathDest1);

    SDL_RenderCopy(renderer, path->texture, NULL, &pathDest2);

    

    // Render character

    SDL_Rect destRect = { character->x, character->y, 64, 64 };

    SDL_RenderCopy(renderer, character->texture, &srcRects[FPS], &destRect);

    

    SDL_RenderPresent(renderer);

}


int main(int argc, char* argv[]) {

    SDL_Window* window;

    SDL_Renderer* renderer;

    initSDL(&window, &renderer);


    Entity background = {0, 0, loadTexture("sampleA.png", renderer)};

    Entity path = {0, 0, loadTexture("tile_0004.png", renderer)};

    Entity character = {0, WINDOW_HEIGHT - 128, loadTexture("tile_0005.png", renderer)};


    SDL_Rect srcRects[3] = {

        {0, 0, 64, 64}, 

        {64, 0, 64, 64}, 

        {128, 0, 64, 64}

    };


    bool running = true;

    int frame = 0;

    int frameCount = 0;


    while (running) {

        Uint32 start_time = SDL_GetTicks();

        handleEvents(&running);

        update(&character, &path, &frame, &frameCount);

        render(renderer, &background, &path, &character, srcRects);

        Uint32 end_time = SDL_GetTicks();

        if (end_time - start_time < FRAME_DELAY) {

            SDL_Delay(FRAME_DELAY - (end_time - start_time));

        }

    }


    SDL_DestroyTexture(background.texture);

    SDL_DestroyTexture(path.texture);

    SDL_DestroyTexture(character.texture);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();


    return 0;

}

