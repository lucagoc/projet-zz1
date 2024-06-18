#include <SDL2/SDL.h>
#include <stdbool.h>

/* Rendu du fond */
void draw_background(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // R G B A
    SDL_RenderClear(renderer);
    return;
}

/* Rendu d'une case : 
    type = 1
    type = 2
    type = 3 */
void draw_case(int type, int x, int y){
    
    return;
}

/* Rendu d'un rhonin ou daimio : 
    rhonin player_1 -> 1
    rhonin player_2 -> 2
    daimio player_1 -> 3
    daimio player_2 -> 4 */
void draw_piece(int joueur, int x, int y){

    return;
}


/**
 * @brief Rendu du plateau
 * 
 * @param board_case Matrice des cases du plateau
 * @param board_piece Matrice des pièces du plateau
 * @param x Coordonnée x du centre du plateau
 * @param y Coordonnée y du centre du plateau
 */
void draw_board(SDL_Renderer *renderer, int x, int y, int board_case[6][6], int board_piece[6][6]){
    
    SDL_Rect board_rect = {x - 300, y - 300, 600, 600};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &board_rect);

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            draw_case(board_case[i][j], i, j);
            draw_piece(board_piece[i][j], i, j);
        }
    }
    
    return;
}

/* Rendu du menu */
void draw_menu(){

    return;
}


/* Rendu globale */
void draw(SDL_Renderer *renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int board_case[6][6], int board_piece[6][6], bool inPause){
    draw_background(renderer);
    draw_board(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, board_case, board_piece);
    
    int count = 0; // Placeholder
    
    for (int i = 0; i < count; i++)
    {
        /* code */
    }
    
    draw_menu();
    return;
}