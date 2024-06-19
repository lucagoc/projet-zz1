#define SDL_COMMON_H

#include "headers/struct.h"

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);
void init_sdl(ui_t *ui);
SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer);
void load_textures(SDL_Texture *textures[10], SDL_Renderer *renderer, SDL_Window *window);
void unload_textures(SDL_Texture *textures[10]);
SDL_Texture* render_text(const char* message, const char* font_file, SDL_Color color, int font_size, SDL_Renderer* renderer);
void get_input(ui_t *ui, game_t *game);
