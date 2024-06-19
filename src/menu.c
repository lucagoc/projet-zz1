#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

// fonctions qui affiche le menu de sélection de la partie (joueur vs joueur, joueur vs IA, IA vs IA)
// Possibilité par la suite de rajouter un moyen d'enregistrer les scores, les parties, etc. (Si on a trop de temps).
// Ajouter la descriptions des positions comme échec peut être pas mal aussi (A8, B4 etc.).

bool is_mouse_over_button(SDL_Rect button, int mouse_x, int mouse_y) {                                                                          //Fonction permet de détecter si la souris est pas loin du bouton
    return mouse_x > button.x && mouse_x < (button.x + button.w) && mouse_y > button.y && mouse_y < (button.y + button.h);
}

bool load_resources(SDL_Renderer* renderer, SDL_Texture** background_texture, SDL_Texture** continue_text, SDL_Texture** quit_text) {           //
    *background_texture = load_texture("image_menu/menu_pause.png", renderer); 
    if (!*background_texture) {
        return false;
    }

    const char* font_path = "image_menu/metal_lord.ttf"; 
    SDL_Color text_color = {204, 136, 80, 255}; // Couleur blanche

    *continue_text = render_text("Continue", font_path, text_color, 24, renderer);
    if (!*continue_text) {
        SDL_DestroyTexture(*background_texture);
        return false;
    }

    *quit_text = render_text("Quit", font_path, text_color, 24, renderer);
    if (!*quit_text) {
        SDL_DestroyTexture(*background_texture);
        SDL_DestroyTexture(*continue_text);
        return false;
    }

    return true;
}

void draw_menu(SDL_Renderer* renderer, SDL_Texture* background_texture, SDL_Texture* continue_text, SDL_Texture* quit_text) {               //Fonction dessine le menu de pause
    int text_width, text_height;

    // La taille et le position du bouton "continue" et "quit"

    SDL_QueryTexture(continue_text, NULL, NULL, &text_width, &text_height);
    SDL_Rect continue_text_rect = {WINDOW_WIDTH / 2 - text_width / 2 - 5, 200, text_width, text_height};
    SDL_Rect continue_button_rect = {WINDOW_WIDTH / 2 - 100 - 5, continue_text_rect.y - 10, 200, text_height + 20};

    SDL_QueryTexture(quit_text, NULL, NULL, &text_width, &text_height);
    SDL_Rect quit_text_rect = {WINDOW_WIDTH / 2 - text_width / 2, WINDOW_HEIGHT - 200, text_width, text_height};
    SDL_Rect quit_button_rect = {WINDOW_WIDTH / 2 - 100, quit_text_rect.y - 10, 200, text_height + 20};

    SDL_RenderClear(renderer);

    // Activer le mode de mélange pour la transparence
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // Dessiner un rectangle semi-transparent qui permet de créer de transparent lors du pause
    SDL_SetRenderDrawColor(renderer,134, 182, 240, 100); 
    SDL_Rect semi_transparent_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderFillRect(renderer, &semi_transparent_rect);

    // Dessiner le fond
    SDL_RenderCopy(renderer, background_texture, NULL, NULL);

    // Dessiner le bouton "Continue"
    SDL_SetRenderDrawColor(renderer, 41, 34, 115, 255); // Bouton bleu marine
    SDL_RenderFillRect(renderer, &continue_button_rect);
    SDL_RenderCopy(renderer, continue_text, NULL, &continue_text_rect);

    // Dessiner le bouton "Quit"
    SDL_SetRenderDrawColor(renderer, 47, 10, 64, 255); // Bouton violet foncé
    SDL_RenderFillRect(renderer, &quit_button_rect);
    SDL_RenderCopy(renderer, quit_text, NULL, &quit_text_rect);

    SDL_RenderPresent(renderer);
}

void handle_events(SDL_Event* event, bool* running, bool* show_menu, SDL_Rect continue_button_rect, SDL_Rect quit_button_rect) {        //Fonction qui permet de d'afficher le menu pause
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            *running = false;
        } else if (event->type == SDL_KEYDOWN) {
            if (event->key.keysym.sym == SDLK_ESCAPE) {
                *show_menu = !*show_menu;
            }
        } else if (event->type == SDL_MOUSEBUTTONDOWN) {
            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);

            if (is_mouse_over_button(continue_button_rect, mouse_x, mouse_y)) {
                SDL_Log("Continue button clicked!");
                *show_menu = false;
                // Ajoutez ici le code pour continuer le jeu

            } else if (is_mouse_over_button(quit_button_rect, mouse_x, mouse_y)) {
                SDL_Log("Quit button clicked!");
                *running = false;
            }
        }
    }
}