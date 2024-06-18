#include <SDL2/SDL.h>
#include <stdbool.h>

/* Rendu du fond */
void draw_background(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // R G B A
    SDL_RenderClear(renderer);
    return;
}

/* Rendu du plateau */
void draw_board(int board_case[6][6], int board_piece[6][6]){

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
void draw_piece(int joueur){

    return;
}

/* Rendu du menu */
void draw_menu(){

    return;
}


/* Rendu globale */
void draw(SDL_Renderer *renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int board_case[6][6], int board_piece[6][6], bool inPause){
    draw_background(renderer);
    draw_board(board_case, board_piece);
    
    int count = 0; // Placeholder
    
    for (int i = 0; i < count; i++)
    {
        /* code */
    }
    
    draw_menu();
    return;
}