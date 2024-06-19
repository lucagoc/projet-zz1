#define SDL_COMMON_H

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);
void init_sdl(SDL_Renderer *renderer, SDL_Window *window, int SCREEN_WIDTH, int SCREEN_HEIGHT);
SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer);
void load_textures(SDL_Texture *textures[10], SDL_Renderer *renderer, SDL_Window *window);
void unload_textures(SDL_Texture *textures[10]);
