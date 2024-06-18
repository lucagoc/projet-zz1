#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void end_sdl(int ok, const char* msg, SDL_Window* window, SDL_Renderer* renderer) {
    if (!ok) {
        SDL_Log("ERROR: %s > %s\n", msg, SDL_GetError());
    }

    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL) {
        SDL_DestroyWindow(window);
    }

    IMG_Quit();
    SDL_Quit();

    if (!ok) {
        exit(EXIT_FAILURE);
    }
}

SDL_Texture* load_texture(const char* file_path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(file_path);
    if (!surface) {
        SDL_Log("ERROR: Unable to load image %s: %s\n", file_path, IMG_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        SDL_Log("ERROR: Unable to create texture from %s: %s\n", file_path, SDL_GetError());
        return NULL;
    }
    return texture;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("ERROR: SDL_Init > %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        SDL_Log("ERROR: IMG_Init > %s\n", IMG_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("Character Running Animation",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("ERROR: SDL_CreateWindow > %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("ERROR: SDL_CreateRenderer > %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Texture* background_texture = load_texture("background.png", renderer);
    SDL_Texture* character_texture1 = load_texture("perso1.png", renderer);
    SDL_Texture* character_texture2 = load_texture("perso2.png", renderer);

    if (!background_texture || !character_texture1 || !character_texture2) {
        end_sdl(0, "Failed to load textures", window, renderer);
    }

    int char_width, char_height;
    SDL_QueryTexture(character_texture1, NULL, NULL, &char_width, &char_height);

    SDL_Rect bg_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    //Ajoutement de la hauteur du personnage
    int offset_y = 90; // Changer offset_y change le hauteur du personnage
    SDL_Rect char_rect = {0, WINDOW_HEIGHT - char_height - offset_y, char_width, char_height};

    bool running = true;
    bool use_texture1 = true;
    int speed = 5;
    int frame_delay = 100;  // Permettre de délai le temps de transition des images
    int elapsed_time = 0;

    Uint32 last_time = SDL_GetTicks();

    while (running && char_rect.x < WINDOW_WIDTH - char_rect.w) {
        Uint32 current_time = SDL_GetTicks();
        elapsed_time += current_time - last_time;
        last_time = current_time;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Effacer le rendu
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture, NULL, &bg_rect);

        // Rendu du personnage
        SDL_Texture* current_texture = use_texture1 ? character_texture1 : character_texture2;
        SDL_RenderCopy(renderer, current_texture, NULL, &char_rect);

        // Présente
        SDL_RenderPresent(renderer);

        // Mouvement du personnage
        char_rect.x += speed;

        // Changer de texture du personnage
        if (elapsed_time >= frame_delay) {
            use_texture1 = !use_texture1;
            elapsed_time = 0;
        }

        SDL_Delay(16);
    }

    // Nettoyage
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(character_texture1);
    SDL_DestroyTexture(character_texture2);

    end_sdl(1, "Ending program", window, renderer);

    return EXIT_SUCCESS;
}
