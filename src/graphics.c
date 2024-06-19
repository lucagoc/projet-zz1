#include <SDL2/SDL.h>
#include <stdbool.h>
#include "headers/struct.h"

#define BOARD_SIZE 6

/* Rendu du fond */
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

/* Rendu d'un rhonin ou daimio :
    rhonin player_1 -> 1
    rhonin player_2 -> 2
    daimio player_1 -> 3
    daimio player_2 -> 4 */
void draw_piece(ui_t *ui, int player, int x, int y)
{
    if (player != 0)
    {
        SDL_Rect piece_rect = {x, y, 95, 95};
        SDL_RenderCopy(ui->renderer, ui->textures[player], NULL, &piece_rect);
    }
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
    int x = ui->SCREEN_WIDTH / 2;
    int y = ui->SCREEN_HEIGHT / 2;
    SDL_Rect board_rect = {x - 300, y - 300, 600, 600};
    SDL_SetRenderDrawColor(ui->renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(ui->renderer, &board_rect);

    int x_case = x - 300;
    int y_case = y - 300;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            draw_case(ui, board->board_case[i][j], x_case + i * 99 + 5, y_case + j * 99 + 5);
            draw_piece(ui, board->board_piece[i][j], x_case + i * 99 + 5, y_case + j * 99 + 5);
        }
    }

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

/* Rendu globale */
void draw(ui_t *ui, board_t *board, game_t *game)
{
    draw_background(ui);
    draw_board(ui, board);
    draw_logo(ui);
}