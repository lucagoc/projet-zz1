#include <stdbool.h>
#include <stdlib.h>
#include "headers/struct.h"

#define GRID_SIZE 6

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
void initialise_plateau(int board[GRID_SIZE][GRID_SIZE])
{
    board[0][0] = 2;
    board[1][0] = 3;
    board[2][0] = 1;
    board[3][0] = 2;
    board[4][0] = 2;
    board[5][0] = 3;
    board[0][1] = 2;
    board[1][1] = 1;
    board[2][1] = 3;
    board[3][1] = 1;
    board[4][1] = 3;
    board[5][1] = 1;
    board[0][2] = 1;
    board[1][2] = 3;
    board[2][2] = 2;
    board[3][2] = 3;
    board[4][2] = 1;
    board[5][2] = 2;
    board[0][3] = 3;
    board[1][3] = 1;
    board[2][3] = 2;
    board[3][3] = 1;
    board[4][3] = 3;
    board[5][3] = 2;
    board[0][4] = 2;
    board[1][4] = 3;
    board[2][4] = 1;
    board[3][4] = 3;
    board[4][4] = 1;
    board[5][4] = 3;
    board[0][5] = 2;
    board[1][5] = 1;
    board[2][5] = 3;
    board[3][5] = 2;
    board[4][5] = 2;
    board[5][5] = 1;
}

// kpos= 0, 1, 2 selon la position de gauche à droite du roi, avec le POV blanc en bas

void initialise_pieces(int pieces_position[GRID_SIZE][GRID_SIZE], int king_black_position, int king_white_position)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            pieces_position[i][j] = 0;
        }
    }

    // ronin noir 1 ronin blanc 2 daimyo noir 3 daimyo blanc 4

    // ajout du daimyo noir

    if (king_black_position == 0)
    {

        pieces_position[0][0] = 3;
        pieces_position[3][0] = 1;
        pieces_position[4][0] = 1;
    }
    else if (king_black_position == 1)
    {

        pieces_position[0][0] = 1;
        pieces_position[3][0] = 3;
        pieces_position[4][0] = 1;
    }
    else
    {

        pieces_position[0][0] = 1;
        pieces_position[3][0] = 1;
        pieces_position[4][0] = 3;
    }

    // ajout du daimyo blanc

    if (king_white_position == 0)
    {
        pieces_position[0][5] = 4;
        pieces_position[3][5] = 2;
        pieces_position[4][5] = 2;
    }
    else if (king_white_position == 1)
    {

        pieces_position[0][5] = 2;
        pieces_position[3][5] = 4;
        pieces_position[4][5] = 2;
    }
    else
    {

        pieces_position[0][5] = 2;
        pieces_position[3][5] = 2;
        pieces_position[4][5] = 4;
    }

    // ajout des ronins noirs

    pieces_position[1][0] = 1;
    pieces_position[2][0] = 1;
    pieces_position[5][0] = 1;

    // ajout du ronins blancs

    pieces_position[1][5] = 2;
    pieces_position[2][5] = 2;
    pieces_position[5][5] = 2;
}

/* Vérifie si le pion peut être placé sur cette case */

/**
 * @brief Regarde si le coup joué est possible (0 ou 1)
 *
 * @param position_piece valeurs pièces sur le plateau
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
bool is_valid_move(int valid, int number_moves, int pieces_position[GRID_SIZE][GRID_SIZE], int xinit, int yinit, int xprev, int yprev, int xdesti, int ydesti)
{
    if (xinit < 0 || yinit < 0 || xinit > 5 || yinit > 5)
    {
        return 0;
    }
    else
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

            if (xinit < 5 && (xinit + 1 != xprev && yinit != yprev) && pieces_position[xinit + 1][yinit] == 0)
            {

                valid = is_valid_move(0, number_moves - 1, pieces_position, xinit + 1, yinit, xinit, yinit, xdesti, ydesti);

                // valid = 1 si on arrive sur la bonne case
            }
            if (xinit > 0 && valid == 0 && (xinit - 1 != xprev && yinit != yprev) && pieces_position[xinit - 1][yinit] == 0)
            {
                valid = is_valid_move(0, number_moves - 1, pieces_position, xinit - 1, yinit, xinit, yinit, xdesti, ydesti);

                // valid = 1 si on arrive sur la bonne case
            }
            if (yinit < 5 && valid == 0 && (xinit != xprev && yinit + 1 != yprev) && pieces_position[xinit][yinit + 1] == 0)
            {
                valid = is_valid_move(0, number_moves - 1, pieces_position, xinit + 1, yinit + 1, xinit, yinit, xdesti, ydesti);

                // valid = 1 si on arrive sur la bonne case
            }
            if (xinit > 0 && valid == 0 && (xinit != xprev && yinit - 1 != yprev) && pieces_position[xinit][yinit - 1] == 0)
            {
                valid = is_valid_move(0, number_moves - 1, pieces_position, xinit + 1, yinit - 1, xinit, yinit, xdesti, ydesti);

                // valid = 1 si on arrive sur la bonne case
            }
            return valid;
        }
    }
}

/**
 * @brief Regarde si le joueur peut jouer (0 ou 1)
 *
 * @param position_piece valeurs des pièces sur le plateau
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

bool can_play(int player, int possible_move, int number_moves, int position_piece[GRID_SIZE][GRID_SIZE], int xinit, int yinit, int xprev, int yprev)
{

    if (xinit < 0 || yinit < 0 || xinit > 5 || yinit > 5)
    {
        return 0;
    }
    else
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
                    if (xinit < 5 && (xinit + 1 != xprev && yinit != yprev) && (position_piece[xinit + 1][yinit] == 0 || position_piece[xinit + 1][yinit] == 2 || position_piece[xinit + 1][yinit] == 4))
                    {

                        possible_move = 1;

                        // valid = 1 si on arrive sur la bonne case
                    }
                    if (xinit > 0 && possible_move == 0 && (xinit - 1 != xprev && yinit != yprev) && (position_piece[xinit - 1][yinit] == 0 || position_piece[xinit - 1][yinit] == 2 || position_piece[xinit - 1][yinit] == 4))
                    {
                        possible_move = 1;

                        // possible_move = 1 si on arrive sur la bonne case
                    }
                    if (yinit < 5 && possible_move == 0 && (xinit != xprev && yinit + 1 != yprev) && (position_piece[xinit][yinit + 1] == 0 || position_piece[xinit][yinit + 1] == 2 || position_piece[xinit][yinit + 1] == 4))
                    {
                        possible_move = 1;

                        // valid = 1 si on arrive sur la bonne case
                    }

                    if (yinit > 0 && possible_move == 0 && (xinit != xprev && yinit - 1 != yprev) && (position_piece[xinit][yinit - 1] == 0 || position_piece[xinit][yinit - 1] == 2 || position_piece[xinit][yinit - 1] == 4))
                    {
                        possible_move = 1;

                        // possible_move = 1 si on arrive sur la bonne case
                    }
                }
                else
                {

                    // si on ne revient pas sur la case prec, si la case à droite est libre
                    if (xinit < 5 && (xinit + 1 != xprev && yinit != yprev) && (position_piece[xinit + 1][yinit] == 0 || position_piece[xinit + 1][yinit] == 1 || position_piece[xinit + 1][yinit] == 3))
                    {

                        possible_move = 1;

                        // valid = 1 si on arrive sur la bonne case
                    }
                    if (xinit > 0 && possible_move == 0 && (xinit - 1 != xprev && yinit != yprev) && (position_piece[xinit - 1][yinit] == 0 || position_piece[xinit - 1][yinit] == 1 || position_piece[xinit - 1][yinit] == 3))
                    {
                        possible_move = 1;

                        // possible_move = 1 si on arrive sur la bonne case
                    }
                    if (yinit < 5 && possible_move == 0 && (xinit != xprev && yinit + 1 != yprev) && (position_piece[xinit][yinit + 1] == 0 || position_piece[xinit][yinit + 1] == 1 || position_piece[xinit][yinit + 1] == 3))
                    {
                        possible_move = 1;

                        // valid = 1 si on arrive sur la bonne case
                    }

                    if (yinit > 0 && possible_move == 0 && (xinit != xprev && yinit - 1 != yprev) && (position_piece[xinit][yinit - 1] == 0 || position_piece[xinit][yinit - 1] == 1 || position_piece[xinit][yinit - 1] == 3))
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
                if (xinit < 5 && (xinit + 1 != xprev && yinit != yprev) && position_piece[xinit + 1][yinit] == 0)
                {

                    possible_move = can_play(player, 0, number_moves - 1, position_piece, xinit + 1, yinit, xinit, yinit);

                    // valid = 1 si on arrive sur la bonne case
                }
                if (xinit > 0 && possible_move == 0 && (xinit - 1 != xprev && yinit != yprev) && position_piece[xinit - 1][yinit] == 0)
                {
                    possible_move = can_play(player, 0, number_moves - 1, position_piece, xinit - 1, yinit, xinit, yinit);

                    // possible_move = 1 si on arrive sur la bonne case
                }
                if (yinit < 5 && possible_move == 0 && (xinit != xprev && yinit + 1 != yprev) && position_piece[xinit][yinit + 1] == 0)
                {
                    possible_move = can_play(player, 0, number_moves - 1, position_piece, xinit + 1, yinit + 1, xinit, yinit);

                    // valid = 1 si on arrive sur la bonne case
                }

                if (yinit > 0 && possible_move == 0 && (xinit != xprev && yinit - 1 != yprev) && position_piece[xinit][yinit - 1] == 0)
                {
                    possible_move = can_play(player, 0, number_moves - 1, position_piece, xinit + 1, yinit - 1, xinit, yinit);

                    // possible_move = 1 si on arrive sur la bonne case
                }
            }
            return possible_move;
        }
    }
}

bool valid_bird_placement(int xinit, int yinit, int birdX, int birdY, int pieces_position[GRID_SIZE][GRID_SIZE], int board[GRID_SIZE][GRID_SIZE]){
    
    return ((pieces_position[birdX][birdY]==0 || pieces_position[birdX][birdY]==5) && (board[birdX][birdY]==board[xinit][yinit])){

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
bool playing_move(int player, int *victory, int *captured_black_piece, int *captured_white_piece, int pieces_position[GRID_SIZE][GRID_SIZE], int board[6][6], int xinit, int yinit, int xdesti, int ydesti)
{

    int valid_move_played = 0;
    if (is_valid_move(0, board[xinit][yinit], pieces_position, xinit, yinit, xinit, yinit, xdesti, ydesti))
    {
        valid_move_played = 1;
        if (player == 0)
        {

            if (pieces_position[xdesti][ydesti] == 2)
            {
                *captured_white_piece += 1;
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
                *captured_black_piece += 1;
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

bool respawn_piece(int player, int captured_white_piece, int captured_black_piece, int pieces_position[GRID_SIZE][GRID_SIZE], int xres, int yres)
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
  
bool is_movement_valid(game_t *game, board_t *board, pos_t destination)
{   
    int player = game->playing_player;
    int x = destination.x;
    int y = destination.y;
    if(x < 0 || y < 0 || x > 5 || y > 5)
    {
        return false;
    }
    else if(board->board_piece[x][y] == 0)
    {
        return true;
    }
    else
    {
        if(player == 2)
        {
            
            if(board->board_piece[x][y] == 1 || board->board_piece[x][y] == 3)
            {
                return true;
            }
        }
        else if(player == 1)
        {
            if(board->board_piece[x][y] == 2 || board->board_piece[x][y] == 4)
            {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Calcule les prédictions de déplacement possibles pour une pièce, step doit être égale à 0 pour que la case soit prise en compte
 * @param game Structure de l'état du jeu
 * @param board Structure du plateau
 * @param piece_pos Position de la pièce
 * @param step Nombre de déplacements possibles
 * @param player Joueur actuel
 *
 * @return Liste des déplacements possibles
 */
void predictions_calculations(game_t *game, board_t *board, pos_t piece_pos, int step)
{
    if (piece_pos.x < 0 || piece_pos.y < 0 || piece_pos.x > 5 || piece_pos.y > 5)
    {
        fprintf(stderr, "Position invalide : %d %d\n", piece_pos.x, piece_pos.y);
        return;
    }
    else if(step == 0 && is_movement_valid(game, board, piece_pos))
    {
        game->predictions[piece_pos.x][piece_pos.y] = 1;
    }
    else
    {
        game->predictions[piece_pos.x][piece_pos.y] = -1;
        if (piece_pos.x < 5 && game->predictions[piece_pos.x + 1][piece_pos.y] == 0 && is_movement_valid(game, board, (pos_t){piece_pos.x + 1, piece_pos.y}))
        {
            predictions_calculations(game, board, (pos_t){piece_pos.x + 1, piece_pos.y}, step - 1);
        }
        if (piece_pos.x > 0 && game->predictions[piece_pos.x - 1][piece_pos.y] == 0 && is_movement_valid(game, board, (pos_t){piece_pos.x - 1, piece_pos.y}))
        {
            predictions_calculations(game, board, (pos_t){piece_pos.x - 1, piece_pos.y}, step - 1);
        }
        if (piece_pos.y < 5 && game->predictions[piece_pos.x][piece_pos.y + 1] == 0 && is_movement_valid(game, board, (pos_t){piece_pos.x, piece_pos.y + 1}))
        {
            predictions_calculations(game, board, (pos_t){piece_pos.x, piece_pos.y + 1}, step - 1);
        }
        if (piece_pos.y > 0 && game->predictions[piece_pos.x][piece_pos.y - 1] == 0 && is_movement_valid(game, board, (pos_t){piece_pos.x, piece_pos.y - 1}))
        {
            predictions_calculations(game, board, (pos_t){piece_pos.x, piece_pos.y - 1}, step - 1);
        }
    }
}

void bird_predictions_calculations(game_t *game, board_t *board)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if(board->board_piece[i][j] == 0 && (board->board_case[i][j] == game->last_case_value))
            {
                game->predictions[i][j] = 1;
            }
            else
            {
                game->predictions[i][j] = -1;
            }
            printf("%d ", game->predictions[i][j]);
        }
        printf("\n");
        
    }
}

/* 0 si personne, 1 si joueur_1, 2 si joueur_2 */
int who_wins(board_t *board){

    bool found_black_daimio = false;
    bool found_white_daimio = false;
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if(board->board_piece[i][j] == 2)
            {
                found_black_daimio = true;
            }
            else if(board->board_piece[i][j] == 4)
            {
                found_white_daimio = true;
            }
        }
        
    }

    if(found_black_daimio && found_white_daimio)
    {
        return 0;
    }
    else if(found_black_daimio)
    {
        return 1;
    }
    else
    {
        return 2;
    }
    
}
