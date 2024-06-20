#define MENU_H

void handle_events(SDL_Event* event, bool* running, bool* show_menu, SDL_Rect continue_button_rect, SDL_Rect quit_button_rect);
bool load_resources(SDL_Renderer* renderer, SDL_Texture** background_texture, SDL_Window *window ,SDL_Texture** continue_text, SDL_Texture** quit_text);