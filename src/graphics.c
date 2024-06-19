#include <SDL2/SDL.h>
#include <stdbool.h>

/* Rendu du fond */
void draw_background(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // R G B A
    SDL_RenderClear(renderer);
    return;
}

/* Rendu d'une case :
    type = 1
    type = 2
    type = 3 */
// x et y sont les coordonnées du haut à gauche de la case
void draw_case(SDL_Renderer *renderer, SDL_Texture *textures[10], int type, int x, int y)
{
    SDL_Rect case_rect = {x, y, 95, 95};
    SDL_RenderCopy(renderer, textures[type + 4], NULL, &case_rect);
}

/* Rendu d'un rhonin ou daimio :
    rhonin player_1 -> 1
    rhonin player_2 -> 2
    daimio player_1 -> 3
    daimio player_2 -> 4 */
void draw_piece(SDL_Renderer *renderer, SDL_Texture *textures[10], int player, int x, int y)
{
    SDL_Rect piece_rect = {x, y, 95, 95};
    SDL_RenderCopy(renderer, textures[player], NULL, &piece_rect);
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
void draw_board(SDL_Renderer *renderer, SDL_Texture *textures[10], int x, int y, int board_case[6][6], int board_piece[6][6])
{

    SDL_Rect board_rect = {x - 300, y - 300, 600, 600};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &board_rect);

    int x_case = x - 300;
    int y_case = y - 300;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            draw_case(renderer, textures, board_case[i][j], x_case + i * 99 + 5, y_case + j * 99 + 5);
            draw_piece(renderer, textures, board_piece[i][j], x_case + i * 99 + 5, y_case + j * 99 + 5);
        }
    }

    return;
}

/* Rendu du menu */
void draw_menu()
{

    return;
}

void draw_logo(SDL_Renderer *renderer, SDL_Texture *textures[10])
{


    SDL_Rect Message_rect = {10, 0, 250, 100};
    SDL_RenderCopy(renderer, textures[8], NULL, &Message_rect);
}

/* Rendu globale */
void draw(SDL_Renderer *renderer, SDL_Texture *textures[10], int SCREEN_WIDTH, int SCREEN_HEIGHT, int board_case[6][6], int board_piece[6][6], bool inPause)
{
    draw_background(renderer);
    draw_board(renderer, textures, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, board_case, board_piece);

    int count = 0; // Placeholder

    for (int i = 0; i < count; i++)
    {
        /* code */
    }

    draw_logo(renderer, textures);
}