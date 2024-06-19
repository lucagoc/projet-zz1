#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "headers/sdl_common.h"

#define SCREEN_WIDTH 620
#define SCREEN_HEIGHT 400

// fonctions qui affiche le menu de sélection de la partie (joueur vs joueur, joueur vs IA, IA vs IA)
// Possibilité par la suite de rajouter un moyen d'enregistrer les scores, les parties, etc. (Si on a trop de temps).
// Ajouter la descriptions des positions comme échec peut être pas mal aussi (A8, B4 etc.).


/**
 *@brief  Test de coordonnée du curseur
 *  
 *@param button L'emplacement du bouton
 *@param mouse_x Coordonnée en x du curseur 
 *@param mouse_y Coordonnée en y du curseur
 */
bool is_mouse_over_button(SDL_Rect button, int mouse_x, int mouse_y) {                                                                          
    return mouse_x > button.x && mouse_x < (button.x + button.w) && mouse_y > button.y && mouse_y < (button.y + button.h);
}

/**
 * @brief Charge les ressources avec des ressources préenregistrer
 * 
 * @param background_texture L'arrière plan
 * @param window fenêtre SDL
 * @param continue_text texte écrit "continue"
 * @param quit_text texte écrit "quit"
 */
bool load_resources(SDL_Renderer* renderer, SDL_Texture** background_texture, SDL_Window *window ,SDL_Texture** continue_text, SDL_Texture** quit_text) {           
    *background_texture = load_texture_from_image("image_menu/menu_pause.png", window , renderer); 
    if (!*background_texture) {
        return false;
    }

    const char* font_path = "image_menu/metal_lord.ttf"; 
    SDL_Color text_color = {204, 136, 80, 255}; 

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

/**
 * @brief Boucle évènement pour la boucle pause
 * 
 * @param event Evènement SDL2
 * @param running Booléen qui détermine l'état de la boucle (True : le jeu est encore, False sinon)
 * @param show_menu Booléen affiche menu
 * @param continue_button_rect Bouton "continue"
 * @param quit_button_rect Bouton "quit"
 */
void handle_events(SDL_Event* event, bool* running, bool* show_menu, SDL_Rect continue_button_rect, SDL_Rect quit_button_rect) {        
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


/*rendu du menu pause*/
void draw_menu_pause(SDL_Renderer* renderer, SDL_Texture* background_texture, SDL_Texture* continue_text, SDL_Texture* quit_text) {               //Fonction dessine le menu de pause
    int text_width, text_height;

    // La taille et le position du bouton "continue" et "quit"

    SDL_QueryTexture(continue_text, NULL, NULL, &text_width, &text_height);
    SDL_Rect continue_text_rect = {SCREEN_WIDTH / 2 - text_width / 2 - 5, 200, text_width, text_height};
    SDL_Rect continue_button_rect = {SCREEN_WIDTH / 2 - 100 - 5, continue_text_rect.y - 10, 200, text_height + 20};

    SDL_QueryTexture(quit_text, NULL, NULL, &text_width, &text_height);
    SDL_Rect quit_text_rect = {SCREEN_WIDTH / 2 - text_width / 2, SCREEN_HEIGHT - 200, text_width, text_height};
    SDL_Rect quit_button_rect = {SCREEN_WIDTH / 2 - 100, quit_text_rect.y - 10, 200, text_height + 20};

    SDL_RenderClear(renderer);

    // Activer le mode de mélange pour la transparence
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // Dessiner un rectangle semi-transparent qui permet de créer de transparent lors du pause
    SDL_SetRenderDrawColor(renderer,134, 182, 240, 100); 
    SDL_Rect semi_transparent_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
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