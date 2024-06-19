#include <stdbool.h>


/**
 * @file rules.c
 * @brief Fonctions correspondant aux règles du jeu (algorithmique)
 * @version 1.0
 * @date 2023-06-19
 * @author Team 21
 */


/**
 * @brief Initialise le plateau avec les cases 1 2 3 (noir en bas, blanc en haut)
 *
 * @param board Fin normale : plateau initialisé ; anormale plateau mal initialisé
 */
void initialise_plateau(int board[6][6])
{

    board[0][0] = 1;
    board[0][1] = 2;
    board[0][2] = 2;
    board[0][3] = 3;
    board[0][4] = 1;
    board[0][5] = 2;
    board[1][0] = 3;
    board[1][1] = 1;
    board[1][2] = 3;
    board[1][3] = 1;
    board[1][4] = 3;
    board[1][5] = 2;
    board[2][0] = 2;
    board[2][1] = 3;
    board[2][2] = 1;
    board[2][3] = 2;
    board[2][4] = 1;
    board[2][5] = 3;
    board[3][0] = 2;
    board[3][1] = 1;
    board[3][2] = 3;
    board[3][3] = 2;
    board[3][4] = 3;
    board[3][5] = 1;
    board[4][0] = 1;
    board[4][1] = 3;
    board[4][2] = 1;
    board[4][3] = 3;
    board[4][4] = 1;
    board[4][5] = 2;
    board[5][0] = 3;
    board[5][1] = 2;
    board[5][2] = 2;
    board[5][3] = 1;
    board[5][4] = 3;
    board[5][5] = 2;
}



int ** occuped_cases_def(int player, int pieces_position[6][6]){
    int occuped_cases[8][8]={0};

    for (int j = 0; j < 8; j++)
    {
        for (int k = 0; k < 8; k++)
        {
            if (j == 0 || k == 0 || j == 7 || k == 7)
            {
                occuped_cases[j][k] = 1;
            }
            else
            {
                if (pieces_position[j-1][k-1] != 0)
                {

                    occuped_cases[j][k] = pieces_position[j-1][k-1];
                }
            }
        }
    }
    return occuped_cases;
}



/* Vérifie si le pion peut être placé sur cette case */

/**
 * @brief Regarde si le coup joué est possible (0 ou 1)
 *
 * @param occuped_cases int occuped_cases[8][8]=occuped_cases_def(pieces_position); tableau de 0 = inoccupé et 1 si case occupée
 * 
 * @param valid utile à la récursion, initialisé à 0
 * 
  * @param xinit position initiale de la pièce jouée
  * @param yinit position initiale de la pièce jouée
  * 
  * @param xprev utile à la récursion, initialisé à xinit
  * @param yprev utile à la récursion, initialisé à yinit
  * 
  * @param xdesti position du coup joué
  * @param ydesti position du coup joué
  * 
  * @param number_moves nombre de coups à jouer (1 2 3): pieces_position[OMx][OMy]==pieces_position[xinit][yinit] au départ


 */
bool is_valid_move(int valid, int number_moves, int occuped_cases[8][8], int xinit, int yinit,int xprev, int yprev, int xdesti, int ydesti)
{

    if (number_moves==0){
        //plus aucun mouvement à effectuer

            //teste si on est sur la bonne case (on ne peut y arriver que si elle est vide)

            return (xinit == xdesti && yinit == ydesti);  
    } else {
        //1 ou plusieurs mouvements restants

        if((xinit+1 != xprev && yinit != yprev) && occuped_cases[xinit+1][yinit]==0){

            valid= is_valid_move(0,number_moves-1,occuped_cases,xinit+1 ,yinit,xinit ,yinit , xdesti, ydesti );
                    
            //valid = 1 si on arrive sur la bonne case

        }        
        if(valid==0 && (xinit-1 != xprev && yinit != yprev) && occuped_cases[xinit-1][yinit]==0){
            valid=  is_valid_move(0,number_moves-1,occuped_cases,xinit-1 ,yinit,xinit ,yinit , xdesti, ydesti );
        
            //valid = 1 si on arrive sur la bonne case

        }
        if(valid==0 && (xinit != xprev && yinit+1 != yprev) && occuped_cases[xinit][yinit+1]==0){
            valid=  is_valid_move(0,number_moves-1,occuped_cases,xinit+1 ,yinit+1,xinit ,yinit , xdesti, ydesti );
            
            //valid = 1 si on arrive sur la bonne case

        }
        if(valid==0 && (xinit != xprev && yinit-1 != yprev) && occuped_cases[xinit][yinit-1]==0){
            valid=  is_valid_move(0,number_moves-1,occuped_cases,xinit+1 ,yinit-1,xinit ,yinit , xdesti, ydesti );
        
            //valid = 1 si on arrive sur la bonne case

        }
        return valid;
    }
}

bool can_play(int player, int valid, int number_moves, int occuped_cases[8][8], int xinit, int yinit,int xprev, int yprev, int xdesti, int ydesti)
{

    if (number_moves==0){
        //plus aucun mouvement à effectuer
            int possible_move=0;

            //teste si on est sur la bonne case (on ne peut y arriver que si elle est vide)
            if (player==0){

                if (occuped_cases[xinit][yinit]==0 || occuped_cases[xinit][yinit]==2 || occuped_cases[xinit][yinit]==4){
                    possible_move=1;
                }
            } else {
                if (occuped_cases[xinit][yinit]==0 || occuped_cases[xinit][yinit]==1 || occuped_cases[xinit][yinit]==3){
                    possible_move=1;
                }
            }
            return possible_move; 

    } else {
        //1 ou plusieurs mouvements restants

        if((xinit+1 != xprev && yinit != yprev) && occuped_cases[xinit+1][yinit]==0){

            valid= is_valid_move(0,number_moves-1,occuped_cases,xinit+1 ,yinit,xinit ,yinit , xdesti, ydesti );
                    
            //valid = 1 si on arrive sur la bonne case

        }        
        if(valid==0 && (xinit-1 != xprev && yinit != yprev) && occuped_cases[xinit-1][yinit]==0){
            valid=  is_valid_move(0,number_moves-1,occuped_cases,xinit-1 ,yinit,xinit ,yinit , xdesti, ydesti );
        
            //valid = 1 si on arrive sur la bonne case

        }
        if(valid==0 && (xinit != xprev && yinit+1 != yprev) && occuped_cases[xinit][yinit+1]==0){
            valid=  is_valid_move(0,number_moves-1,occuped_cases,xinit+1 ,yinit+1,xinit ,yinit , xdesti, ydesti );
            
            //valid = 1 si on arrive sur la bonne case

        }
        if(valid==0 && (xinit != xprev && yinit-1 != yprev) && occuped_cases[xinit][yinit-1]==0){
            valid=  is_valid_move(0,number_moves-1,occuped_cases,xinit+1 ,yinit-1,xinit ,yinit , xdesti, ydesti );
        
            //valid = 1 si on arrive sur la bonne case

        }
        return valid;
    }
}

/* Vérifie si le joueur peut encore jouer */


/**
 * @brief Joue le coup indiqué par le joueur si c'est possible
 *
 * @param player 0 si on est sur le joueur noir ou 1 si le joueur blanc
 * @param board contient le tableau initial avec les valeurs des cases
 * @param pieces_position tableau qui contient les pièces sur le plateau: 0 aucun 1 ronin noir 2 ronin blanc 3 daimyo noir 4 daimyo blanc 5 le piaf

 * @param OMx position de l'oiseau marseillais posé précédemment

 * @param OMy position de l'oiseau marseillais posé précédemment

 * @param pieces_position tableau qui contient les pièces sur le plateau: 0 aucun 1 ronin noir 2 ronin blanc 3 daimyo noir 4 daimyo blanc 5 le piaf
  * 
  * @param xinit position de la pièce jouée
  * @param yinit position de la pièce jouée
  *  
  * @param xdesti position du coup joué
  * @param ydesti position du coup joué
  * 
  *@param advantage 0 si le coup dépend de l'oiseau, 1 sinon (cas où le coup précédent est impossible)
  *
 */

int ** playing_move(int player,int advantage, int OMx, int OMy, int pieces_position[6][6],  int board[6][6],int xinit, int yinit, int xdesti, int ydesti){

    int ** occuped_cases=occuped_cases_def(player, pieces_position);
    if (advantage==0){
        if (can_play(player,board, OMx, OMy, pieces_position )){

        }
    } else {
        

    }

}


/**
 * @brief Respawne une pièce à l'endroit indiqué et renvoie 1 si c'est possible, renvoie 0 sinon
 *
 * @param player 0 si on est sur le joueur noir ou 1 si le joueur blanc

 * @param captured_white_piece nombre de pièces blanches capturées

 * @param captured_black_piece nombre de pièces noires capturées

 * @param pieces_position tableau qui contient les pièces sur le plateau: 0 aucun 1 ronin noir 2 ronin blanc 3 daimyo noir 4 daimyo blanc 5 le piaf
  * 
  * @param xres position de la pièce replacée
  * @param yres position de la pièce replacée
  * 
 */

bool respawn_piece(int player, int captured_white_piece, int captured_black_piece, int pieces_position[6][6], int xres, int yres){
    
    int respawn_possible=0;
    
    if (player==0){
        if (captured_black_piece>0 && pieces_position[xres][yres]==0){
            respawn_possible=1;
            pieces_position[xres][yres]=1;  //on place un ronin noir
        }
    } else {
        if (captured_white_piece>0 && pieces_position[xres][yres]==0){
            respawn_possible=1;
            pieces_position[xres][yres]=2;//on place un ronin blanc

        }
    }

    return respawn_possible;
}






/**
 * brief Regarde si le joueur peut jouer ou non (0 ou 1)
 *
 * param player 0 si on est sur le joueur noir ou 1 si le joueur blanc
 * param board contient le tableau initial avec les valeurs des cases

 * param OMx position de l'oiseau marseillais posé précédemment

 * param OMy position de l'oiseau marseillais posé précédemment

 * param pieces_position tableau qui contient les pièces sur le plateau: 0 aucun 1 ronin noir 2 ronin blanc 3 daimyo noir 4 daimyo blanc 5 le piaf

 */


/*bool can_play(int player, int board[6][6], int OMx, int OMy, int pieces_position[6][6])
{

    int possible_move = 1;
    int number_moves = board[OMx][OMy]; // 1 2 3 coups à jouer selon l'oiseau posé précédemment

    // pour gérer les bords du plateau: matrice 0 si case inoccupee et 1 si occupee

    int ** occuped_cases=occuped_cases_def(player, pieces_position);

    for (int x = 0; x < 6; x++)
    {
        for (int y = 0; y < 6; y++)
        {
            if (board[x][y] == number_moves)
            {
                // on teste une case avec le bon nombre de coups à jouer

                if (player == 0)
                {
                    if (pieces_position[x][y] == 1 || pieces_position[x][y] == 3)
                    {
                        // on teste une case avec une pièce noire qui doit jouer

                        // si on a une case occupée a gauche, une a droite, une en haut, une en bas
                        if (occuped_cases[x + 1][y] == 0)
                        {

                            if (number_moves > 1)
                            {

                                if (occuped_cases[x + 2][y] == 0)
                                {
                                    if (number_moves > 2)
                                    {

                                        if (occuped_cases[x + 3][y] == 0 || occuped_cases[x + 2][y + 1] == 0 || occuped_cases[x + 2][y - 1] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                if (x < 7 && occuped_cases[x + 1][y + 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x + 1][y + 2] == 0 || occuped_cases[x + 2][y + 1] == 0 || occuped_cases[x][y + 1] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                if (x < 7 && occuped_cases[x + 1][y - 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x + 1][y - 2] == 0 || occuped_cases[x + 2][y - 1] == 0 || occuped_cases[x][y - 1] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                x = 7;
                                y = 7;
                            }
                        }

                        if (x < 7 && occuped_cases[x][y + 1] == 0)
                        {

                            if (number_moves > 1)
                            {

                                if (occuped_cases[x][y + 2] == 0)
                                {
                                    if (number_moves > 2)
                                    {

                                        if (occuped_cases[x][y + 3] == 0 || occuped_cases[x + 1][y + 2] == 0 || occuped_cases[x - 1][y + 2] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                if (x < 7 && occuped_cases[x + 1][y + 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x + 2][y + 1] == 0 || occuped_cases[x + 1][y + 2] == 0 || occuped_cases[x + 1][y] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                if (x < 7 && occuped_cases[x - 1][y + 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x - 2][y + 1] == 0 || occuped_cases[x - 1][y + 2] == 0 || occuped_cases[x - 1][y] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                x = 7;
                                y = 7;
                            }
                        }
                        if (x < 7 && occuped_cases[x - 1][y] == 0)
                        {

                            if (number_moves > 1)
                            {

                                if (occuped_cases[x - 1][y + 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {

                                        if (occuped_cases[x - 2][y + 1] == 0 || occuped_cases[x][y + 1] == 0 || occuped_cases[x - 1][y + 2] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                else if (occuped_cases[x - 1][y - 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x - 2][y - 1] == 0 || occuped_cases[x][y - 1] == 0 || occuped_cases[x - 1][y - 2] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                else if (occuped_cases[x - 2][y] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x - 3][y] == 0 || occuped_cases[x - 2][y + 1] == 0 || occuped_cases[x - 2][y - 1] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                x = 7;
                                y = 7;
                            }
                        }
                        if (x < 7 && occuped_cases[x][y - 1] == 0)
                        {

                            if (number_moves > 1)
                            {

                                if (occuped_cases[x][y - 2] == 0)
                                {
                                    if (number_moves > 2)
                                    {

                                        if (occuped_cases[x + 1][y - 2] == 0 || occuped_cases[x - 1][y - 2] == 0 || occuped_cases[x][y - 3] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                else if (occuped_cases[x + 1][y - 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x + 2][y - 1] == 0 || occuped_cases[x + 1][y - 2] == 0 || occuped_cases[x + 1][y] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                else if (occuped_cases[x - 1][y - 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x - 1][y - 2] == 0 || occuped_cases[x - 2][y - 1] == 0 || occuped_cases[x - 1][y] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                x = 7;
                                y = 7;
                            }
                        }
                    }

                    // si on a plusieurs coups: on teste puis on recommence avec une case libre mais avec la case
                    // précédente occupée
                }
                else
                {
                    if (pieces_position[x][y] == 2 || pieces_position[x][y] == 4)
                    {
                        // on teste une case avec une pièce blanche qui doit jouer

                        // on teste une case avec une pièce noire qui doit jouer

                        // si on a une case occupée a gauche, une a droite, une en haut, une en bas
                        if (occuped_cases[x + 1][y] == 0)
                        {

                            if (number_moves > 1)
                            {

                                if (occuped_cases[x + 2][y] == 0)
                                {
                                    if (number_moves > 2)
                                    {

                                        if (occuped_cases[x + 3][y] == 0 || occuped_cases[x + 2][y + 1] == 0 || occuped_cases[x + 2][y - 1] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                if (x < 7 && occuped_cases[x + 1][y + 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x + 1][y + 2] == 0 || occuped_cases[x + 2][y + 1] == 0 || occuped_cases[x][y + 1] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                if (x < 7 && occuped_cases[x + 1][y - 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x + 1][y - 2] == 0 || occuped_cases[x + 2][y - 1] == 0 || occuped_cases[x][y - 1] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                x = 7;
                                y = 7;
                            }
                        }

                        if (x < 7 && occuped_cases[x][y + 1] == 0)
                        {

                            if (number_moves > 1)
                            {

                                if (occuped_cases[x][y + 2] == 0)
                                {
                                    if (number_moves > 2)
                                    {

                                        if (occuped_cases[x][y + 3] == 0 || occuped_cases[x + 1][y + 2] == 0 || occuped_cases[x - 1][y + 2] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                if (x < 7 && occuped_cases[x + 1][y + 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x + 2][y + 1] == 0 || occuped_cases[x + 1][y + 2] == 0 || occuped_cases[x + 1][y] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                if (x < 7 && occuped_cases[x - 1][y + 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x - 2][y + 1] == 0 || occuped_cases[x - 1][y + 2] == 0 || occuped_cases[x - 1][y] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                x = 7;
                                y = 7;
                            }
                        }
                        if (x < 7 && occuped_cases[x - 1][y] == 0)
                        {

                            if (number_moves > 1)
                            {

                                if (occuped_cases[x - 1][y + 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {

                                        if (occuped_cases[x - 2][y + 1] == 0 || occuped_cases[x][y + 1] == 0 || occuped_cases[x - 1][y + 2] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                else if (occuped_cases[x - 1][y - 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x - 2][y - 1] == 0 || occuped_cases[x][y - 1] == 0 || occuped_cases[x - 1][y - 2] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                else if (occuped_cases[x - 2][y] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x - 3][y] == 0 || occuped_cases[x - 2][y + 1] == 0 || occuped_cases[x - 2][y - 1] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                x = 7;
                                y = 7;
                            }
                        }
                        if (x < 7 && occuped_cases[x][y - 1] == 0)
                        {

                            if (number_moves > 1)
                            {

                                if (occuped_cases[x][y - 2] == 0)
                                {
                                    if (number_moves > 2)
                                    {

                                        if (occuped_cases[x + 1][y - 2] == 0 || occuped_cases[x - 1][y - 2] == 0 || occuped_cases[x][y - 3] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                else if (occuped_cases[x + 1][y - 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x + 2][y - 1] == 0 || occuped_cases[x + 1][y - 2] == 0 || occuped_cases[x + 1][y] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                                else if (occuped_cases[x - 1][y - 1] == 0)
                                {
                                    if (number_moves > 2)
                                    {
                                        if (occuped_cases[x - 1][y - 2] == 0 || occuped_cases[x - 2][y - 1] == 0 || occuped_cases[x - 1][y] == 0)
                                        {
                                            x = 7;
                                            y = 7;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                x = 7;
                                y = 7;
                            }
                        }
                    }
                }
            }
        }
    }

    return possible_move;
}
*/