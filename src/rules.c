#include <stdbool.h>
#include <stdlib.h>

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
int **initialise_plateau()
{

    int **board = malloc(6 * sizeof(int *));
    for (int i = 0; i < 6; i++)
    {
        board[i] = malloc(6 * sizeof(int));
    }

    board[0][0] = 2;
    board[0][1] = 3;
    board[0][2] = 1;
    board[0][3] = 2;
    board[0][4] = 2;
    board[0][5] = 3;
    board[1][0] = 2;
    board[1][1] = 1;
    board[1][2] = 3;
    board[1][3] = 1;
    board[1][4] = 3;
    board[1][5] = 1;
    board[2][0] = 1;
    board[2][1] = 3;
    board[2][2] = 2;
    board[2][3] = 3;
    board[2][4] = 1;
    board[2][5] = 2;
    board[3][0] = 3;
    board[3][1] = 1;
    board[3][2] = 2;
    board[3][3] = 1;
    board[3][4] = 3;
    board[3][5] = 2;
    board[4][0] = 2;
    board[4][1] = 3;
    board[4][2] = 1;
    board[4][3] = 3;
    board[4][4] = 1;
    board[4][5] = 3;
    board[5][0] = 2;
    board[5][1] = 1;
    board[5][2] = 3;
    board[5][3] = 2;
    board[5][4] = 2;
    board[5][5] = 1;

    return board;
}

// kpos= 0, 1, 2 selon la position de gauche à droite du roi, avec le POV blanc en bas

int **initialise_pieces(int king_black_position, int king_white_position)
{

    int **pieces_position = malloc(6 * sizeof(int *));
    for (int i = 0; i < 6; i++)
    {
        pieces_position[i] = malloc(6 * sizeof(int));

        for (int j = 0; j < 6; j++)
        {
            pieces_position[i][j] = 0;
        }
    }

    // ronin noir 1 ronin blanc 2 daimyo noir 3 daimyo blanc 4

    // ajout du daimyo noir

    if (king_black_position == 0)
    {

        pieces_position[0][0] = 3;
        pieces_position[0][3] = 1;
        pieces_position[0][4] = 1;
    }
    else if (king_black_position == 1)
    {

        pieces_position[0][0] = 1;
        pieces_position[0][3] = 3;
        pieces_position[0][4] = 1;
    }
    else
    {

        pieces_position[0][0] = 1;
        pieces_position[0][3] = 1;
        pieces_position[0][4] = 3;
    }

    // ajout du daimyo blanc

    if (king_white_position == 0)
    {

        pieces_position[0][0] = 4;
        pieces_position[0][3] = 2;
        pieces_position[0][4] = 2;
    }
    else if (king_white_position == 1)
    {

        pieces_position[0][0] = 2;
        pieces_position[0][3] = 4;
        pieces_position[0][4] = 2;
    }
    else
    {

        pieces_position[0][0] = 2;
        pieces_position[0][3] = 2;
        pieces_position[0][4] = 4;
    }

    // ajout des ronins noirs

    pieces_position[0][1] = 1;
    pieces_position[0][2] = 1;
    pieces_position[0][5] = 1;

    // ajout du ronins blancs

    pieces_position[5][1] = 2;
    pieces_position[5][2] = 2;
    pieces_position[5][5] = 2;

    return pieces_position;
}

int **occuped_cases_def(int pieces_position[6][6])
{
    int **occuped_cases = malloc(8 * sizeof(int *));
    for (int i = 0; i < 8; i++)
    {
        occuped_cases[i] = malloc(8 * sizeof(int));
    }

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
                if (pieces_position[j - 1][k - 1] != 0)
                {

                    occuped_cases[j][k] = pieces_position[j - 1][k - 1];
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
bool is_valid_move(int valid, int number_moves, int **occuped_cases, int xinit, int yinit, int xprev, int yprev, int xdesti, int ydesti)
{

    if (number_moves == 0)
    {
        // plus aucun mouvement à effectuer

        // teste si on est sur la bonne case (on ne peut y arriver que si elle est vide)

        return (xinit == xdesti && yinit == ydesti);
    }
    else
    {
        // 1 ou plusieurs mouvements restants

        if ((xinit + 1 != xprev && yinit != yprev) && occuped_cases[xinit + 1][yinit] == 0)
        {

            valid = is_valid_move(0, number_moves - 1, occuped_cases, xinit + 1, yinit, xinit, yinit, xdesti, ydesti);

            // valid = 1 si on arrive sur la bonne case
        }
        if (valid == 0 && (xinit - 1 != xprev && yinit != yprev) && occuped_cases[xinit - 1][yinit] == 0)
        {
            valid = is_valid_move(0, number_moves - 1, occuped_cases, xinit - 1, yinit, xinit, yinit, xdesti, ydesti);

            // valid = 1 si on arrive sur la bonne case
        }
        if (valid == 0 && (xinit != xprev && yinit + 1 != yprev) && occuped_cases[xinit][yinit + 1] == 0)
        {
            valid = is_valid_move(0, number_moves - 1, occuped_cases, xinit + 1, yinit + 1, xinit, yinit, xdesti, ydesti);

            // valid = 1 si on arrive sur la bonne case
        }
        if (valid == 0 && (xinit != xprev && yinit - 1 != yprev) && occuped_cases[xinit][yinit - 1] == 0)
        {
            valid = is_valid_move(0, number_moves - 1, occuped_cases, xinit + 1, yinit - 1, xinit, yinit, xdesti, ydesti);

            // valid = 1 si on arrive sur la bonne case
        }
        return valid;
    }
}

/**
 * @brief Regarde si le joueur peut jouer (0 ou 1)
 *
 * @param occuped_cases int **occuped_cases=occuped_cases_def(pieces_position); tableau de 0 = inoccupé et 1 si case occupée
 *
 * @param player joueur: 0 = noir, 1 = blanc
 *
 * @param possible_move utile à la récursion, initialisé à 0
 *
 * @param number_moves nombre de coups à jouer (1 2 3): pieces_position[OMx][OMy]==pieces_position[xinit][yinit] au départ si non avantage
 * @param xinit position initiale de la pièce jouée
 * @param yinit position initiale de la pièce jouée
 *
 * @param xprev utile à la récursion, initialisé à xinit
 * @param yprev utile à la récursion, initialisé à yinit
 *
 */

bool can_play(int player, int possible_move, int number_moves, int **occuped_cases, int xinit, int yinit, int xprev, int yprev)
{

    if (number_moves == 0)
    {
        // plus aucun mouvement à effectuer
        return 0;
        // on ne doit pas arriver ici, normalement
    }
    else
    {
        // 1 ou plusieurs mouvements restants
        if (number_moves == 1)
        {
            if (player == 0)
            {

                // si on ne revient pas sur la case prec, si la case à droite est libre
                if ((xinit + 1 != xprev && yinit != yprev) && (occuped_cases[xinit + 1][yinit] == 0 || occuped_cases[xinit + 1][yinit] == 2 || occuped_cases[xinit + 1][yinit] == 4))
                {

                    possible_move = 1;

                    // valid = 1 si on arrive sur la bonne case
                }
                if (possible_move == 0 && (xinit - 1 != xprev && yinit != yprev) && (occuped_cases[xinit - 1][yinit] == 0 || occuped_cases[xinit - 1][yinit] == 2 || occuped_cases[xinit - 1][yinit] == 4))
                {
                    possible_move = 1;

                    // possible_move = 1 si on arrive sur la bonne case
                }
                if (possible_move == 0 && (xinit != xprev && yinit + 1 != yprev) && (occuped_cases[xinit][yinit + 1] == 0 || occuped_cases[xinit][yinit + 1] == 2 || occuped_cases[xinit][yinit + 1] == 4))
                {
                    possible_move = 1;

                    // valid = 1 si on arrive sur la bonne case
                }

                if (possible_move == 0 && (xinit != xprev && yinit - 1 != yprev) && (occuped_cases[xinit][yinit - 1] == 0 || occuped_cases[xinit][yinit - 1] == 2 || occuped_cases[xinit][yinit - 1] == 4))
                {
                    possible_move = 1;

                    // possible_move = 1 si on arrive sur la bonne case
                }
            }
            else
            {

                // si on ne revient pas sur la case prec, si la case à droite est libre
                if ((xinit + 1 != xprev && yinit != yprev) && (occuped_cases[xinit + 1][yinit] == 0 || occuped_cases[xinit + 1][yinit] == 1 || occuped_cases[xinit + 1][yinit] == 3))
                {

                    possible_move = 1;

                    // valid = 1 si on arrive sur la bonne case
                }
                if (possible_move == 0 && (xinit - 1 != xprev && yinit != yprev) && (occuped_cases[xinit - 1][yinit] == 0 || occuped_cases[xinit - 1][yinit] == 1 || occuped_cases[xinit - 1][yinit] == 3))
                {
                    possible_move = 1;

                    // possible_move = 1 si on arrive sur la bonne case
                }
                if (possible_move == 0 && (xinit != xprev && yinit + 1 != yprev) && (occuped_cases[xinit][yinit + 1] == 0 || occuped_cases[xinit][yinit + 1] == 1 || occuped_cases[xinit][yinit + 1] == 3))
                {
                    possible_move = 1;

                    // valid = 1 si on arrive sur la bonne case
                }

                if (possible_move == 0 && (xinit != xprev && yinit - 1 != yprev) && (occuped_cases[xinit][yinit - 1] == 0 || occuped_cases[xinit][yinit - 1] == 1 || occuped_cases[xinit][yinit - 1] == 3))
                {
                    possible_move = 1;

                    // possible_move = 1 si on arrive sur la bonne case
                }
            }
            return possible_move;
        }
        else
        {

            // si on ne revient pas sur la case prec, si la case à droite est libre
            if ((xinit + 1 != xprev && yinit != yprev) && occuped_cases[xinit + 1][yinit] == 0)
            {

                possible_move = can_play(player, 0, number_moves - 1, occuped_cases, xinit + 1, yinit, xinit, yinit);

                // valid = 1 si on arrive sur la bonne case
            }
            if (possible_move == 0 && (xinit - 1 != xprev && yinit != yprev) && occuped_cases[xinit - 1][yinit] == 0)
            {
                possible_move = can_play(player, 0, number_moves - 1, occuped_cases, xinit - 1, yinit, xinit, yinit);

                // possible_move = 1 si on arrive sur la bonne case
            }
            if (possible_move == 0 && (xinit != xprev && yinit + 1 != yprev) && occuped_cases[xinit][yinit + 1] == 0)
            {
                possible_move = can_play(player, 0, number_moves - 1, occuped_cases, xinit + 1, yinit + 1, xinit, yinit);

                // valid = 1 si on arrive sur la bonne case
            }

            if (possible_move == 0 && (xinit != xprev && yinit - 1 != yprev) && occuped_cases[xinit][yinit - 1] == 0)
            {
                possible_move = can_play(player, 0, number_moves - 1, occuped_cases, xinit + 1, yinit - 1, xinit, yinit);

                // possible_move = 1 si on arrive sur la bonne case
            }
        }
        return possible_move;
    }
}

/* Vérifie si le joueur peut encore jouer */

int number_moves_to_play(int board[6][6], int xinit, int yinit)
{
    return board[xinit][yinit];
}

/**
 * @brief Joue le coup indiqué par le joueur et retourne 1 si c'est possible, retourne 0 sinon
 *
 * @param player 0 si on est sur le joueur noir ou 1 si le joueur blanc
 * @param victory contient l'adresse vers une case contenant: 0 si pas de victoire, 1 si victoire noire, 2 si victoire blanche
 *
 * @param captured_black_piece contient l'adresse vers un compteur du nombre de ronin noirs capturés
 * @param captured_white_piece contient l'adresse vers un compteur du nombre de ronin blancs capturés
 *
 * @param pieces_position tableau qui contient les pièces sur le plateau: 0 aucun 1 ronin noir 2 ronin blanc 3 daimyo noir 4 daimyo blanc 5 le piaf
 * @param board contient les numéros des cases de la grille
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
bool playing_move(int player, int *victory, int *captured_black_piece, int *captured_white_piece, int pieces_position[6][6], int board[6][6], int xinit, int yinit, int xdesti, int ydesti)
{

    int **occuped_cases = occuped_cases_def(pieces_position);
    int valid_move_played = 0;
    if (is_valid_move(0, board[xinit][yinit], occuped_cases, xinit, yinit, xinit, yinit, xdesti, ydesti))
    {
        valid_move_played = 1;
        if (player == 0)
        {

            if (pieces_position[xdesti][ydesti] == 2)
            {
                *captured_white_piece+=1;
            }
            else if (pieces_position[xdesti][ydesti] == 4)
            {
                *victory = 1;
            }
        }
        else
        {
            if (pieces_position[xdesti][ydesti] == 1)
            {
                *captured_black_piece+=1;
            }
            else if (pieces_position[xdesti][ydesti] == 3)
            {
                *victory = 2;
            }
        }

        pieces_position[xdesti][ydesti] = pieces_position[xinit][yinit];
        pieces_position[xinit][yinit] = 0;
    }
    return valid_move_played;
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

bool respawn_piece(int player, int captured_white_piece, int captured_black_piece, int pieces_position[6][6], int xres, int yres)
{

    int respawn_possible = 0;

    if (player == 0)
    {
        if (captured_black_piece > 0 && pieces_position[xres][yres] == 0)
        {
            respawn_possible = 1;
            pieces_position[xres][yres] = 1; // on place un ronin noir
        }
    }
    else
    {
        if (captured_white_piece > 0 && pieces_position[xres][yres] == 0)
        {
            respawn_possible = 1;
            pieces_position[xres][yres] = 2; // on place un ronin blanc
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