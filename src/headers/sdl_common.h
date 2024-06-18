#define SDL_COMMON_H

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);
SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer);
