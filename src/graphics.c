#include <SDL2/SDL.h>

/* Rendu du fond */
void draw_background(){

    return;
}

/* Rendu du plateau */
void draw_plateau(){

    return;
}

/* Rendu d'un pion */
void draw_pion(int joueur){

    return;
}

/* Rendu du menu */
void draw_menu(){

    return;
}


/* Rendu globale */
void draw(SDL_Renderer *renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int board[6][6], int pause){
    draw_background();
    draw_plateau();
    
    int count = 0; // Placeholder
    
    for (int i = 0; i < count; i++)
    {
        /* code */
    }
    
    draw_menu();
    return;
}