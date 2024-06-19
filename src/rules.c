#include <stdbool.h>

int **initialise_plateau(int board[6][6])
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

    return board;
}

/* Vérifie si le pion peut être placé sur cette case */
bool is_valid_move(int pieces_position[6][6], int x, int y)
{

    return (pieces_position[x][y] == 0);
}

/* Vérifie si le joueur peut encore jouer */

// board contient le tableau initial avec les valeurs des cases
// pieces contient les pièces sur le plateau: 0 aucun 1 ronin noir 2 ronin blanc 3 daimyo noir 4 daimyo blanc 5 le piaf
// player vaut 0 si on est sur le joueur noir ou 1 si le joueur blanc
//OMx et OMy correspond à la position de l'oiseau marseillais posé précédemment

bool can_play(int player, int board[6][6], int OMx, int OMy, int pieces_position[6][6])
{

    int possible_move = 1;
    int x = 0;
    int y = 0;
    int number_moves = board[OMx][OMy]; // 1 2 3 coups à jouer selon l'oiseau posé précédemment

    // pour gérer les bords du plateau: matrice 0 si case inoccupee et 1 si occupee
    int occuped_cases[8][8];

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
                if (pieces_position[j][k] != 0)
                {
                    occuped_cases[j][k] = 1;
                }
            }
        }
    }

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
