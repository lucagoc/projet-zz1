#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "headers/struct.h"
#include "headers/rules.h"
#include "headers/sdl_common.h"

#define GRID_SIZE 6

/**
 * @file opponent.c
 * @brief Fonctions correspondant aux actions de l'adversaire
 * @version 1.0
 * @date 2023-06-19
 * @author Team 21
 */


int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
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
            if (game_state->board->pieces[i][j] == player && (game_state->board->cases[i][j] == game_state->last_case || game_state->last_case == 0))
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

int min_max(game_state_t *game_state, int depth, bool is_max)
{
    // Création de l'input
    input_t *input = malloc(sizeof(input_t));
    init_input(input);

    int score = evaluate(game_state);
    if (depth == 0)
    {
        return score;
    }
    if (is_max) // Joueur Maximisant.
    {
        int best = -1000;
        l_path_t *cases = playable_cases(game_state, 1);
        l_path_t *current = cases;
        while (current != NULL) // Pour tous les coups
        {
            list_t *current_possibility = current->possibilities;
            while (current_possibility != NULL) // Pour tous les mouvements possibles pour ce coup
            {
                // Copier la situation du jeu
                game_state_t * copy = copy_game_state(game_state);

                // Mettre l'input à jour
                input->selected_case_1->x = current->pos->x;
                input->selected_case_1->y = current->pos->y;
                input->selected_case_2->x = current_possibility->value.x;
                input->selected_case_2->y = current_possibility->value.y;
                
                game_logic(copy, input); // Jouer le coup

                if(copy->winner == 2) // L'ia gagne
                {
                    return 1000;
                }
                else if(copy->winner == 1) // L'ia perd
                {
                    return -1000;
                }

                // Placement de l'oiseau
                if(copy->phase == 1)
                {
                    // L'oiseau est placé sur la case la plus proche du centre
                    // Input = ...

                    game_logic(copy, input); // Jouer le coup
                }

                int res = min_max(copy, depth-1, !is_max);
                best = max(best, res);

                // Libération de la mémoire
                free_game_state(copy);

                // Passage au prochain mouvement possible
                current_possibility = current_possibility->next;
            }

            // Passage au prochain coup
            current = current->next;
        }

        return best;
    }
    else // Description de la pire situation
    {
        int best = 1000;
        l_path_t *cases = playable_cases(game_state, 2);
        l_path_t *current = cases;
        while (current != NULL) // Pour tous les coups
        {
            list_t *current_possibility = current->possibilities;
            while (current_possibility != NULL) // Pour tous les mouvements possibles pour ce coup
            {
                // Copier la situation du jeu
                game_state_t * copy = copy_game_state(game_state);

                // Mettre l'input à jour
                input->selected_case_1->x = current->pos->x;
                input->selected_case_1->y = current->pos->y;
                input->selected_case_2->x = current_possibility->value.x;
                input->selected_case_2->y = current_possibility->value.y;
                
                game_logic(copy, input); // Jouer le coup

                if(copy->winner == 2) // L'ia gagne
                {
                    return 1000;
                }
                else if(copy->winner == 1) // L'ia perd
                {
                    return -1000;
                }

                // Placement de l'oiseau
                if(copy->phase == 1)
                {
                    // L'oiseau est placé sur la case la plus proche du centre
                    // Input = ...

                    game_logic(copy, input); // Jouer le coup
                }

                int res = min_max(copy, depth-1, !is_max);
                best = min(best, res);

                // Libération de la mémoire
                free_game_state(copy);

                // Passage au prochain mouvement possible
                current_possibility = current_possibility->next;
            }

            // Passage au prochain coup
            current = current->next;
        }

        return best;
    }

    // Libération de la mémoire.
    free_input(input);
}

/**
 * @brief Fonction qui retourne le meilleur coup à jouer pour l'IA
 * 
 * @param game_state Etat du jeu
 */
pos_t* best_move(game_state_t *game_state)
{
    // Lister tous les coups possibles
    l_path_t *cases = playable_cases(game_state, game_state->player);
    l_path_t *current = cases;
    pos_t *best_move = malloc(sizeof(pos_t));

    int max = -1000;

    while (current != NULL) // Pour tous les coups
    {
        list_t *current_possibility = current->possibilities;
        while (current_possibility != NULL) // Pour tous les mouvements possibles pour ce coup
        {
            int res = min_max(game_state, 2, true);
            if (res >= max){
                max = res;
                best_move->x = current->pos->x;
                best_move->y = current->pos->y;
            }
        }

        // Passage au prochain coup
        current = current->next;
    }

    return best_move;
}

void play_opponent(game_state_t *game_state)
{
    pos_t *best = best_move(game_state);
    input_t *input = malloc(sizeof(input_t));
    init_input(input);
    input->selected_case_1->x = best->x;
    input->selected_case_1->y = best->y;
    game_logic(game_state, input);
    
    // Placement de l'oiseau
    if(game_state->phase == 1)
    {
        // L'oiseau est placé sur la case la plus proche du centre
        // Input = ...

        game_logic(game_state, input); // Jouer le coup
    }


    // Libération de la mémoire
    free(input);
    free(best);
}