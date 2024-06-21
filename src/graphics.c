#include <SDL2/SDL.h>
#include <stdbool.h>
#include "headers/struct.h"

#define BOARD_SIZE 6
#define GRID_SIZE 6

/**
 * @brief Dessine le fond de l'écran
 *
 * @param ui Interface utilisateur
 */
void draw_background(ui_t *ui)
{
    SDL_SetRenderDrawColor(ui->renderer, 208, 240, 245, 255); // R G B A
    SDL_RenderClear(ui->renderer);
    return;
}

/**
 * @brief Affiche une case
 *
 * @param ui Interface utilisateur
 * @param type Type de la case
 * @param x Coordonnée x de la case
 * @param y Coordonnée y de la case
 */
void draw_case(ui_t *ui, int type, int x, int y)
{
    SDL_Rect case_rect = {x, y, 95, 95};
    SDL_RenderCopy(ui->renderer, ui->textures[type + 4], NULL, &case_rect);
}

/**
 * @brief Affiche une pièce
 *
 * @param ui Interface utilisateur
 * @param player Joueur
 * @param x Coordonnée x de la pièce
 * @param y Coordonnée y de la pièce
 */
void draw_piece(ui_t *ui, int player, int x, int y)
{
    if (player != 0)
    {
        SDL_Rect piece_rect = {x, y, 95, 95};
        SDL_RenderCopy(ui->renderer, ui->textures[player], NULL, &piece_rect);
    }
}

/**
 * @brief Affiche la case sélectionnée
 *
 * @param ui Interface utilisateur
 * @param input Entrée utilisateur
 */
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

/*
 * @brief Affiche le message de victoire
 *
 * @param ui Interface utilisateur
 * @param game Etat du jeu
 * @param y Coordonnée y du message
 */
void draw_victory(ui_t *ui)
{
    SDL_Rect win_rect = {950, 100, 300, 60};
    SDL_RenderCopy(ui->renderer, ui->textures_pause[3], NULL, &win_rect);
}

/**
 * @brief Affiche un rectangle rouge autour de la case prédite
 *
 * @param ui Interface utilisateur
 * @param board Plateau de jeu
 * @param x Coordonnée x de la prédiction
 * @param y Coordonnée y de la prédiction
 */
void draw_possible_move(ui_t *ui, int x, int y, int phase)
{
    SDL_Rect prediction_rect = {ui->screen_w / 2 - 300 + x * 99 + 5, ui->screen_h / 2 - 300 + y * 99 + 5, 95, 95};
    if (phase == 0)
    {
        SDL_SetRenderDrawColor(ui->renderer, 255, 0, 0, 128);
    }
    else // Pour l'oiseau
    {
        SDL_SetRenderDrawColor(ui->renderer, 0, 0, 255, 128);
    }
    SDL_RenderFillRect(ui->renderer, &prediction_rect);
}

/**
 * @brief Affiche toutes les cases possibles
 *
 * @param ui Interface utilisateur
 * @param list_moves Liste des cases possibles
 * @param is_bird Indique si l'oiseau est en jeu
 */
void draw_all_possible_moves(ui_t *ui, list_t *list_moves, int phase)
{
    list_t *current = list_moves;
    while (current != NULL)
    {
        draw_possible_move(ui, current->value.x, current->value.y, phase);
        current = current->next;
    }

    return;
}

/**
 * @brief Affiche la dernière case jouée
 *
 * @param ui Interface utilisateur
 * @param game_state Etat du jeu
 */
void draw_last_case(ui_t *ui, game_state_t *game_state)
{
    if (game_state->last_case != 0)
    {
        SDL_Rect last_case_rect = {0, 500, 100, 100};
        SDL_RenderCopy(ui->renderer, ui->textures[game_state->last_case + 4], NULL, &last_case_rect);
    }
}

/**
 * @brief Affiche l'oiseau
 *
 * @param ui Interface utilisateur
 * @param board Plateau de jeu
 */
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

/**
 * @brief Affiche le joueur qui doit jouer
 *
 * @param ui Interface utilisateur
 * @param game_state Etat du jeu
 */
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

            if (board->pieces[i][j] == 1)
            {
                if (board->daimyo_1->x == i && board->daimyo_1->y == j)
                {
                    draw_piece(ui, 3, x_case + i * 99 + 5, y_case + j * 99 + 5);
                }
                else
                {
                    draw_piece(ui, 1, x_case + i * 99 + 5, y_case + j * 99 + 5);
                }
            }
            else if (board->pieces[i][j] == 2)
            {
                if (board->daimyo_2->x == i && board->daimyo_2->y == j)
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

/**
 * @brief Rendu du logo
 *
 * @param ui Interface utilisateur
 */
void draw_logo(ui_t *ui)
{
    SDL_Rect logo_rect = {10, 10, 250, 100};
    SDL_RenderCopy(ui->renderer, ui->textures[8], NULL, &logo_rect);
}

/**
 * @brief Rendu de l'indicateur de joueur
 *
 * @param ui Interface utilisateur
 * @param game_state Etat du jeu
 * @param input Entrée utilisateur
 */
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

    /************************ AFFICHAGE PIECES CAPTURES *************************/
    int captured_black = game_state->captured_pieces[1];
    int captured_white = game_state->captured_pieces[2];

    while (captured_black > 0)
    {
        draw_piece(ui, 1, 150, captured_black * 100 + 100);
        captured_black--;
    }

    while (captured_white > 0)
    {
        draw_piece(ui, 2, ui->screen_w - 150, captured_white * 100 + 100);
        captured_white--;
    }

    return;
}

/**
 * @brief Dessine le menu de pause
 *
 * @param ui Interface utilisateur
 */
void draw_menu_pause(ui_t *ui)
{
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

/**
 * @brief Rendu de l'interface utilisateur
 *
 * @param ui Interface utilisateur
 * @param game_state Etat du jeu
 * @param input Entrée utilisateur
 */
void draw(ui_t *ui, game_state_t *game_state, input_t *input)
{
    draw_background(ui);
    draw_logo(ui);
    if (ui->in_pause)
    {
        draw_menu_pause(ui);
        return;
    }
    draw_board(ui, game_state->board);
    draw_indicator(ui, game_state, input);
    if (game_state->winner != 0)
    {
        draw_victory(ui);
        return;
    }
}