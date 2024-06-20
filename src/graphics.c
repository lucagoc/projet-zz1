#include <SDL2/SDL.h>
#include <stdbool.h>
#include "headers/struct.h"

#define BOARD_SIZE 6
#define GRID_SIZE 6

void draw_background(ui_t *ui)
{
    SDL_SetRenderDrawColor(ui->renderer, 255, 255, 255, 255); // R G B A
    SDL_RenderClear(ui->renderer);
    return;
}

/* Rendu d'une case :
    type = 1
    type = 2
    type = 3 */
// x et y sont les coordonnées du haut à gauche de la case
void draw_case(ui_t *ui, int type, int x, int y)
{
    SDL_Rect case_rect = {x, y, 95, 95};
    SDL_RenderCopy(ui->renderer, ui->textures[type + 4], NULL, &case_rect);
}

void draw_piece(ui_t *ui, int player, int x, int y)
{
    if (player != 0)
    {
        SDL_Rect piece_rect = {x, y, 95, 95};
        SDL_RenderCopy(ui->renderer, ui->textures[player], NULL, &piece_rect);
    }
}

void draw_selected_case(ui_t *ui, input_t *input)
{
    if (input->selected_case_1->x != -1 && input->selected_case_1->y != -1)
    {
        SDL_Rect selected_rect = {ui->screen_w / 2 - 300 + input->selected_case_1->x * 99 + 5, ui->screen_h / 2 - 300 + input->selected_case_1->y * 99 + 5, 95, 95};
        SDL_SetRenderDrawColor(ui->renderer, 0, 255, 0, 128);
        SDL_RenderFillRect(ui->renderer, &selected_rect);
    }

    if (input->selected_case_2->x != -1 && input->selected_case_2->y != -1)
    {
        SDL_Rect selected_rect = {ui->screen_w / 2 - 300 + input->selected_case_2->x * 99 + 5, ui->screen_h / 2 - 300 + input->selected_case_2->y * 99 + 5, 95, 95};
        SDL_SetRenderDrawColor(ui->renderer, 0, 255, 0, 128);
        SDL_RenderFillRect(ui->renderer, &selected_rect);
    }
}

/**
 * @brief Affiche un rectangle rouge autour de la case prédite
 *
 * @param ui Interface utilisateur
 * @param board Plateau de jeu
 * @param x Coordonnée x de la prédiction
 * @param y Coordonnée y de la prédiction
 */
void draw_possible_move(ui_t *ui, int x, int y, bool is_bird)
{
    SDL_Rect prediction_rect = {ui->screen_w / 2 - 300 + x * 99 + 5, ui->screen_h / 2 - 300 + y * 99 + 5, 95, 95};
    if (is_bird)
    {
        SDL_SetRenderDrawColor(ui->renderer, 255, 0, 0, 128);
    }
    else
    {
        SDL_SetRenderDrawColor(ui->renderer, 255, 0, 0, 128);
    }
    SDL_RenderFillRect(ui->renderer, &prediction_rect);
}

/**
 * @brief Affiche toutes les cases possibles depuis le pion sélectionné
 *
 */
void draw_all_possible_moves(ui_t *ui, list_t *list_moves, bool is_bird)
{
    list_t *current = list_moves;
    while (current != NULL)
    {
        draw_possible_move(ui, current->value.x, current->value.y, is_bird);
        current = current->next;
    }

    return;
}

void draw_last_case(ui_t *ui, game_state_t *game_state)
{
    if (game_state->last_case != 0)
    {
        SDL_Rect last_case_rect = {0, 500, 100, 100};
        SDL_RenderCopy(ui->renderer, ui->textures[game_state->last_case + 4], NULL, &last_case_rect);
    }
}

void draw_bird(ui_t *ui, board_t *board)
{
    if (board->bird != NULL && board->bird->x != -1 && board->bird->y != -1)
    {
        SDL_Rect bird_rect = {ui->screen_w / 2 - 300 + board->bird->x * 99 + 5, ui->screen_h / 2 - 300 + board->bird->y * 99 + 5, 95, 95};
        SDL_Rect white_rect = {ui->screen_w / 2 - 300 + board->bird->x * 99 + 5, ui->screen_h / 2 - 300 + board->bird->y * 99 + 5, 95, 95};
        SDL_SetRenderDrawColor(ui->renderer, 0, 0, 0, 128);
        SDL_RenderFillRect(ui->renderer, &white_rect);
        SDL_RenderCopy(ui->renderer, ui->textures[9], NULL, &bird_rect);
    }
}

void draw_playing_player(ui_t *ui, game_state_t *game_state)
{
    SDL_Rect player_rect = {0, 400, 100, 100};
    if (game_state->player == 1) // Joueur noir
    {
        SDL_SetRenderDrawColor(ui->renderer, 0, 0, 0, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(ui->renderer, 255, 255, 255, 255);
    }
    SDL_RenderFillRect(ui->renderer, &player_rect);
}

/**
 * @brief Rendu du plateau
 *
 * @param renderer Renderer SDL
 * @param textures Tableau de textures
 * @param board_case Matrice des cases du plateau
 * @param board_piece Matrice des pièces du plateau
 * @param x Coordonnée x du centre du plateau
 * @param y Coordonnée y du centre du plateau
 */
void draw_board(ui_t *ui, board_t *board)
{
    int x = ui->screen_w / 2;
    int y = ui->screen_h / 2;
    SDL_Rect board_rect = {x - 300, y - 300, 600, 600};
    SDL_SetRenderDrawColor(ui->renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(ui->renderer, &board_rect);

    int x_case = x - 300;
    int y_case = y - 300;
    
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            draw_case(ui, board->cases[i][j], x_case + i * 99 + 5, y_case + j * 99 + 5);
            
            if(board->pieces[i][j] == 1){
                if(board->daimyo_1->x == i && board->daimyo_1->y == j)
                {
                    draw_piece(ui, 3, x_case + i * 99 + 5, y_case + j * 99 + 5);
                }
                else
                {
                    draw_piece(ui, 1, x_case + i * 99 + 5, y_case + j * 99 + 5);
                }
            }
            else if(board->pieces[i][j] == 2){
                if(board->daimyo_2->x == i && board->daimyo_2->y == j)
                {
                    draw_piece(ui, 4, x_case + i * 99 + 5, y_case + j * 99 + 5);
                }
                else
                {
                    draw_piece(ui, 2, x_case + i * 99 + 5, y_case + j * 99 + 5);
                }
            }
            
        }
    }

    draw_bird(ui, board);

    return;
}

/* Rendu du menu */
void draw_menu()
{

    return;
}

void draw_logo(ui_t *ui)
{
    SDL_Rect logo_rect = {10, 10, 250, 100};
    SDL_RenderCopy(ui->renderer, ui->textures[8], NULL, &logo_rect);
}

void draw_indicator(ui_t *ui, game_state_t *game_state, input_t *input)
{
    if (game_state->player_blocked) // Indicateur de blocage
    {
        SDL_Rect indicator_rect = {0, 200, 100, 100};
        SDL_SetRenderDrawColor(ui->renderer, 255, 0, 0, 128);
        SDL_RenderFillRect(ui->renderer, &indicator_rect);
    }

    if (game_state->player == 1) // Indicateur de joueur
    {
        SDL_Rect player_rect = {0, 300, 100, 100};
        SDL_SetRenderDrawColor(ui->renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(ui->renderer, &player_rect);
    }
    else
    {
        SDL_Rect player_rect = {0, 300, 100, 100};
        SDL_SetRenderDrawColor(ui->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(ui->renderer, &player_rect);
    }
    draw_last_case(ui, game_state);
    
    draw_selected_case(ui, input);
    if (input->possible_moves != NULL)
    {
        draw_all_possible_moves(ui, input->possible_moves, game_state->phase);
    }
    
    return;
}

/*rendu du menu pause*/
void draw_menu_pause(ui_t *ui) {
    int text_width, text_height;

    // La taille et la position du bouton "continue" et "quit"

    SDL_QueryTexture(ui->textures_pause[1], NULL, NULL, &text_width, &text_height);
    SDL_Rect continue_text_rect = {ui->screen_w / 2 - text_width / 2 - 5, 250, text_width, text_height}; // Déplacement vers le bas
    SDL_Rect continue_button_rect = {ui->screen_w / 2 - 100 - 5, continue_text_rect.y - 10, 200, text_height + 20};

    SDL_QueryTexture(ui->textures_pause[2], NULL, NULL, &text_width, &text_height);
    SDL_Rect quit_text_rect = {ui->screen_w / 2 - text_width / 2, ui->screen_h - 200, text_width, text_height};
    SDL_Rect quit_button_rect = {ui->screen_w / 2 - 100, quit_text_rect.y - 10, 200, text_height + 20};

    // Dessiner un rectangle semi-transparent pour l'effet de pause
    SDL_SetRenderDrawColor(ui->renderer, 134, 182, 240, 100); 
    SDL_Rect semi_transparent_rect = {0, 0, ui->screen_w, ui->screen_h};
    SDL_RenderFillRect(ui->renderer, &semi_transparent_rect);

    // Dessiner l'arrière-plan
    SDL_RenderCopy(ui->renderer, ui->textures_pause[0], NULL, NULL);

    // Dessiner le bouton "Continue"
    SDL_SetRenderDrawColor(ui->renderer, 41, 34, 115, 255); // Bouton bleu marine
    SDL_RenderFillRect(ui->renderer, &continue_button_rect);
    SDL_RenderCopy(ui->renderer, ui->textures_pause[1], NULL, &continue_text_rect);

    // Dessiner le bouton "Quit"
    SDL_SetRenderDrawColor(ui->renderer, 47, 10, 64, 255); // Bouton violet foncé
    SDL_RenderFillRect(ui->renderer, &quit_button_rect);
    SDL_RenderCopy(ui->renderer, ui->textures_pause[2], NULL, &quit_text_rect);

}

/* Rendu globale */
void draw(ui_t *ui, game_state_t *game_state, input_t *input)
{
    if(ui->in_pause)
    {
        draw_menu_pause(ui);
        return;
    }
    draw_background(ui);
    draw_board(ui, game_state->board);
    draw_indicator(ui, game_state, input);
    draw_logo(ui);
}