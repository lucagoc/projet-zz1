#include <stdbool.h>

int **initialise_plateau(int matrice[6][6])
{

    matrice[0][0] = 2;
    matrice[0][1] = 3;
    matrice[0][2] = 1;
    matrice[0][3] = 2;
    matrice[0][4] = 2;
    matrice[0][5] = 3;
    matrice[1][0] = 2;
    matrice[1][1] = 1;
    matrice[1][2] = 3;
    matrice[1][3] = 1;
    matrice[1][4] = 3;
    matrice[1][5] = 1;
    matrice[2][0] = 1;
    matrice[2][1] = 3;
    matrice[2][2] = 2;
    matrice[2][3] = 3;
    matrice[2][4] = 1;
    matrice[2][5] = 2;
    matrice[3][0] = 3;
    matrice[3][1] = 1;
    matrice[3][2] = 2;
    matrice[3][3] = 1;
    matrice[3][4] = 3;
    matrice[3][5] = 2;
    matrice[4][0] = 2;
    matrice[4][1] = 3;
    matrice[4][2] = 1;
    matrice[4][3] = 3;
    matrice[4][4] = 1;
    matrice[4][5] = 3;
    matrice[5][0] = 2;
    matrice[5][1] = 1;
    matrice[5][2] = 3;
    matrice[5][3] = 2;
    matrice[5][4] = 2;
    matrice[5][5] = 1;

    return matrice;
}

/* Vérifie si le pion peut être placé sur cette case */
bool is_valid_move(int tableau_pieces[6][6], int x, int y)
{

    return (tableau_pieces[x][y] == 0);
}

/* Vérifie si le joueur peut encore jouer */

//board contient le tableau initial avec les valeurs des cases
//pieces contient les pièces sur le plateau: 0 aucun 1 ronin noir 2 ronin blanc 3 daimyo noir 4 daimyo blanc 5 le piaf
//player vaut 0 si on est sur le joueur noir ou 1 si le joueur blanc

bool can_play(int player, int board[6][6], int OMx, int OMy, int pieces[6][6])
{
    
    int coup_possible = 1;
    int x=0;
    int y=0;
    int coups_à_jouer=board[OMx][OMy] = {0};  //1 2 3 selon l'oiseau posé précédemment
    
    //pour gérer les bords du plateau: matrice 0 si case inoccupee et 1 si occupee
    int cases_occupees[8][8]; 
    for (int j=0; j<8; j++){
        for (int k=0; k<8; k++){
            if(j==0 || k==0 || j==7 || k==7){
                cases_occupees[j][k]=1;
            } else{
                if (pieces[j][k] != 0){
                   cases_occupees[j][k]=1;

                }
            }
        }
    }   

    for (int x=0; x<6; x++) {
        for (int y=0; y<6; y++) {
            if (board[x][y]==coups_à_jouer){
                // on teste une case avec le bon nombre de coups à jouer

                if (player==0){
                    if (pieces[x][y]==1 || pieces[x][y]==3){
                        // on teste une case avec une pièce noire qui doit jouer
                        
                        //si on a une case occupée a gauche, une a droite, une en haut, une en bas
                        if (x)
                        //si on a plusieurs coups: on teste puis on recommence avec une case libre mais avec la case 
                        //précédente occupée
                    }
                } else {
                    if (pieces[x][y]==2 || pieces[x][y]==4){
                        // on teste une case avec une pièce blanche qui doit jouer
                        

                        
                    }
                }
            }
        }   
    }       
    
    return coup_possible;
}
