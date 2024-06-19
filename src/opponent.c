#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Principalement là où sera utilisé min-max pour calculer le prochain coup.


#define BOARD_SIZE 6

/**
 * @brief Copie un plateau
 * 
 * @param board Plateau à copier
 * @return int* Plateau copié
 */
int** copy_board(int board[BOARD_SIZE][BOARD_SIZE])
{
    int** new_board = malloc(6 * sizeof(int *));
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

