#include <SDL2/SDL.h>
#include <stdbool.h>
#include "headers/struct.h"
#include <SDL2/SDL_ttf.h>                                            // Charger la bibliothèque

#define GRID_SIZE 6

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

void draw_selected_case(ui_t *ui, board_t *board, game_t *game)
{
    if (game->selected_case->x != -1 && game->selected_case->y != -1)
    {
        SDL_Rect selected_rect = {ui->SCREEN_WIDTH / 2 - 300 + game->selected_case->x * 99 + 5, ui->SCREEN_HEIGHT / 2 - 300 + game->selected_case->y * 99 + 5, 95, 95};
        SDL_SetRenderDrawColor(ui->renderer, 0, 255, 0, 255);
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
void draw_prediction(ui_t *ui, board_t *board, game_t *game, int x, int y)
{
    SDL_Rect prediction_rect = {ui->SCREEN_WIDTH / 2 - 300 + x * 99 + 5, ui->SCREEN_HEIGHT / 2 - 300 + y * 99 + 5, 95, 95};
    SDL_SetRenderDrawColor(ui->renderer, 255, 0, 0, 128);
    SDL_RenderFillRect(ui->renderer, &prediction_rect);
}

/**
 * @brief Affiche toutes les cases possibles depuis le pion sélectionné
 *
 */
void draw_all_predictions(ui_t *ui, board_t *board, game_t *game)
{
    fprintf(stderr, "draw_all_predictions\n");
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            fprintf(stderr, "predictions[%d][%d] = %d\n", i, j, game->predictions[i][j]);
            if (game->predictions[i][j] == 1)
            {
                draw_prediction(ui, board, game, i, j);
            }
        }
    }
}

void draw_bird_prediction(ui_t *ui, board_t *board, game_t *game, int x, int y)
{
    SDL_Rect prediction_rect = {ui->SCREEN_WIDTH / 2 - 300 + x * 99 + 5, ui->SCREEN_HEIGHT / 2 - 300 + y * 99 + 5, 95, 95};
    SDL_SetRenderDrawColor(ui->renderer, 0, 0, 255, 128);
    SDL_RenderFillRect(ui->renderer, &prediction_rect);
}

void draw_all_bird_predictions(ui_t *ui, board_t *board, game_t *game)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (game->predictions[i][j] == 1)
            {
                draw_bird_prediction(ui, board, game, i, j);
            }
        }
    }
}

void draw_bird(ui_t *ui, board_t *board)
{
    if (board->bird->x != -1 && board->bird->y != -1)
    {
        SDL_Rect bird_rect = {ui->SCREEN_WIDTH / 2 - 300 + board->bird->x * 99 + 5, ui->SCREEN_HEIGHT / 2 - 300 + board->bird->y * 99 + 5, 95, 95};
        SDL_RenderCopy(ui->renderer, ui->textures[9], NULL, &bird_rect);
    }
}

void draw_blocage(ui_t *ui,game_t * game,int x,int y){
    
    if (TTF_Init() < 0) end_sdl(0, "Couldn't initialize SDL TTF", ui->window, ui->renderer);

    TTF_Font* font = NULL;                                               // la variable 'police de caractère'
    font = TTF_OpenFont("./Pacifico.ttf", 25);                     // La police à charger, la taille désirée
    if (font == NULL) end_sdl(0, "Can't load font", ui->window, ui->renderer);

    TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);           // en italique, gras

    SDL_Color color = {20, 0, 40, 255};                                  // la couleur du texte
    SDL_Surface* text_surface = NULL;                                    // la surface  (uniquement transitoire)
    text_surface = TTF_RenderText_Blended(font, "    jouer           revivre", color); // création du texte dans la surface 
    if (text_surface == NULL) end_sdl(0, "Can't create text surface", ui->window, ui->renderer);

    SDL_Texture* text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(ui->renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", ui->window, ui->renderer);
    SDL_FreeSurface(text_surface);                                       // la texture ne sert plus à rien

    SDL_Rect pos = {x-100, 0, x+50, 75};                                         // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte 
    SDL_RenderCopy(ui->renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer   
    SDL_DestroyTexture(text_texture);  
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
void draw_board(ui_t *ui, board_t *board, game_t *game)
{
    int x = ui->SCREEN_WIDTH / 2;
    int y = ui->SCREEN_HEIGHT / 2;
    SDL_Rect board_rect = {x - 300, y - 300, 600, 600};
    SDL_SetRenderDrawColor(ui->renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(ui->renderer, &board_rect);

    int x_case = x - 300;
    int y_case = y - 300;

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            draw_case(ui, board->board_case[i][j], x_case + i * 99 + 5, y_case + j * 99 + 5);
            draw_piece(ui, board->board_piece[i][j], x_case + i * 99 + 5, y_case + j * 99 + 5);
        }
    }

    int captured_black = board->captured_black_pieces;
    int captured_white = board->captured_white_pieces;

    while (captured_black > 0)
    {
        draw_piece(ui, 1, 150 , captured_black*100+100);
        captured_black--;
    }

    while (captured_white > 0)
    {
        draw_piece(ui, 2, ui->SCREEN_WIDTH-150 , captured_white*100+100);
        captured_white--;

    }

    if (game->blocage==1 || game->blocage==2){
        draw_blocage(ui, game,x,y);
    }

    if (game->case_is_selected)
    {
        draw_selected_case(ui, board, game);
        draw_all_predictions(ui, board, game);
    }
    else if (game->bird_is_selected)
    {
        draw_all_bird_predictions(ui, board, game);
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

/* Rendu globale */
void draw(ui_t *ui, board_t *board, game_t *game)
{
    draw_background(ui);
    draw_board(ui, board, game);
    draw_logo(ui);
}