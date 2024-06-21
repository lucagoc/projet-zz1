#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "headers/struct.h"
#include "headers/rules.h"

#define GRID_SIZE 6


/**
 * @brief Fonction qui compte le nombre de pièce au centre
 * 
 * @param board Plateau de jeu
 */
int count_center_piece(board_t *board){
    int count = 0;
    board_t *current = board;
    
    for (int i = 2; i < 4 ; i++){
        for (int j = 2; j < 4; j++){
            if (current->pieces[i][j] != 0){
                count++;
            }
        }
    }
    return count;
}


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
                score += 2;
            }
            else if (game_state->board->pieces[i][j] == 2)
            {
                score -= 2;
            }
             /*On privilège les pièces au centre*/
            else if (count_center_piece(game_state->board) > 2){ /*On privilège les pièces au centre*/
                score += 1;
            }
            else if (count_center_piece(game_state->board) < 2){
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

/**
 * @brief Fonction qui copie un plateau
 * 
 * @param board Plateau à copier
 * @return board_t* Copie du plateau
 */
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

/**
 * @brief Fonction qui copie un état de jeu
 * 
 * @param game_state Etat de jeu à copier
 * @return game_state_t* Copie de l'état de jeu
 */
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


/**
 * @brief Liste des cases vides 
 * 
 * @param board plateau de jeu
 */
list_t *list_empty_cases(board_t *board){
    list_t * list_empty = malloc(sizeof(list_t));

    if (list_empty == NULL){
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        return NULL;
    } 
    
    board_t * current = board;
    int i, j;

    for (i = 0; i < GRID_SIZE; i++){
        for(j = 0; j < GRID_SIZE; j++ ){
            if (current->pieces[i][j] == 0){
                list_t *new_list_empty = malloc(sizeof(list_t));
                if (new_list_empty == NULL){
                    fprintf(stderr, "Erreur d'allocation de mémoire\n");
                    return NULL;
                }
                pos_t *pos = malloc(sizeof(pos_t));
                if (pos == NULL){
                    fprintf(stderr, "Erreur d'allocation de mémoire\n");
                    return NULL;
                }
                pos->x = i;
                pos->y = j;
                new_list_empty->value = *pos;
                new_list_empty->next = NULL;
                list_empty->next = new_list_empty;
            }
        }
    }
    return list_empty;
}



