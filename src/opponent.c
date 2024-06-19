#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "headers/struct.h"
#include "headers/rules.h"

// Principalement là où sera utilisé min-max pour calculer le prochain coup.

#define BOARD_SIZE 6

/**
 * @brief Copie un plateau
 *
 * @param board Plateau à copier
 * @return int* Plateau copié
 */
int **copy_board(int board[BOARD_SIZE][BOARD_SIZE])
{
    int **new_board = malloc(6 * sizeof(int *));
    for (int i = 0; i < 6; i++)
    {
        new_board[i] = malloc(6 * sizeof(int));
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            new_board[i][j] = board[i][j];
        }
    }
    return new_board;
}

/**
 * @brief Évalue un plateau
 *
 * @param board Plateau à évaluer
 * @param player Joueur pour lequel évaluer le plateau
 * @return int Valeur du plateau
 */
int evaluate(board_t *board, int player)
{
    return 0;
}

/**
 * @brief Min-Max
 *
 * @param board Plateau
 * @param depth Profondeur
 * @param player Joueur
 * @param maximizingPlayer Joueur maximisant
 * @return int Valeur du plateau
 */
int min_max(board_t *board, int depth, int player, bool maximizingPlayer)
{
    /**
     * Itération de l'algo
     * - Si la profondeur est égale à 0 ou on ne peut plus jouer, on évalue le plateau (Cas de base)
     * - Si on est le joueur maximisant, on cherche le maximum des valeurs des enfants
     * - Sinon, on cherche le minimum des valeurs des enfants
     * - On retourne la valeur du plateau
     */
    if (depth == 0 /*|| !can_play(player, board)*/)
    {
        return evaluate(board, player);
    }
    else
    {
        if (maximizingPlayer)
        {
            // TODO
        }
    }
}