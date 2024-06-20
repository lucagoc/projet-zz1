#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "headers/struct.h"
#include "headers/rules.h"


#define GRID_SIZE 6

// Fonction d'évaluation ultra naïve basé sur le nombre de pièces de chaque joueur
int evaluate(game_state_t *game_state)
{
    int score = 0;
    int i, j;
    for (i = 0; i < GRID_SIZE; i++)
    {
        for (j = 0; j < GRID_SIZE; j++)
        {
            if (game_state->board->pieces[i][j] == 1)
            {
                score += 1;
            }
            else if (game_state->board->pieces[i][j] == 2)
            {
                score -= 1;
            }
        }
    }
    return score;
}

// Fonction qui liste toute les cases jouables pour le joueur donné
// Retourne une liste de cases jouables
l_path_t *playable_cases(game_state_t *game_state, int player)
{
    l_path_t *res = NULL;
    int i, j;
    for (i = 0; i < GRID_SIZE; i++)
    {
        for (j = 0; j < GRID_SIZE; j++)
        {
            if (game_state->board->pieces[i][j] == player && game_state->board->cases[i][j] == game_state->last_case)
            {
                // Ajouter un élément à la liste
                l_path_t *nouveau = malloc(sizeof(l_path_t));
                if (nouveau == NULL)
                {
                    fprintf(stderr, "Erreur d'allocation de mémoire\n");
                    exit(EXIT_FAILURE);
                }

                // Ajouter la position
                pos_t *pos = malloc(sizeof(pos_t));
                if (pos == NULL)
                {
                    fprintf(stderr, "Erreur d'allocation de mémoire\n");
                    exit(EXIT_FAILURE);
                }
                pos->x = i;
                pos->y = j;
                nouveau->pos = pos;

                // Ajouter les possibilités
                list_t *possibilities = NULL;
                possibilities = list_rhonin_possible_moves((pos_t){i, j}, game_state->board, game_state->board->cases[i][j], player);
                nouveau->possibilities = possibilities;

                // Ajouter à la liste
                nouveau->next = res;
            }
        }
    }

    return res;
}

board_t *copy_board(board_t *board)
{
    board_t *copy = malloc(sizeof(board_t));
    if (copy == NULL)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    int i, j;
    for (i = 0; i < GRID_SIZE; i++)
    {
        for (j = 0; j < GRID_SIZE; j++)
        {
            copy->cases[i][j] = board->cases[i][j];
            copy->pieces[i][j] = board->pieces[i][j];
        }
    }
    return copy;
}

game_state_t *copy_game_state(game_state_t *game_state)
{
    game_state_t *copy = malloc(sizeof(game_state_t));
    if (copy == NULL)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    copy->player = game_state->player;
    copy->round = game_state->round;
    copy->last_case = game_state->last_case;
    copy->player_blocked = game_state->player_blocked;
    copy->phase = game_state->phase;
    copy->captured_pieces[0] = game_state->captured_pieces[0];
    copy->captured_pieces[1] = game_state->captured_pieces[1];
    copy->captured_pieces[2] = game_state->captured_pieces[2];
    copy->board = copy_board(game_state->board);
    return copy;
}

/*
int min_max(game_state_t *game_state, int depth, bool is_max)
{
    int score = evaluate(game_state);
    if (depth == 0)
    {
        return score;
    }
    if (is_max)
    {
        int best = -1000;
        
        
        l_path_t *cases = playable_cases(game_state, 1);
        l_path_t *current = cases;
        while (current != NULL)
        {
            list_t *possibilities = current->possibilities;
            list_t *current_possibility = possibilities;
            while (current_possibility != NULL)
            {
                // Faire une copie de la possibilité
                // game_state_t *new_game_state = copy_game_state(game_state);
                

            }
            current = current->next;
        }

    }
    else
    {
        int best = 1000;
        // TODO
        return best;
    }
} */