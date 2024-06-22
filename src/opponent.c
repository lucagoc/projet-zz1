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

/**
 * @brief Fonction qui compte le nombre de pièce au centre
 *
 * @param board Plateau de jeu
 */
int count_center_piece(board_t *board)
{
    int count = 0;
    board_t *current = board;

    for (int i = 2; i < 4; i++)
    {
        for (int j = 2; j < 4; j++)
        {
            if (current->pieces[i][j] != 0)
            {
                count++;
            }
        }
    }
    return count;
}

/**
 * @brief Renvoie la case la plus au centre parmi une liste de cases (la première s'il y en a plusieurs de même distance)
 *
 * @param L list_t de cases sur le plateau
 * @return la position pos_t la plus centrée
 */
pos_t center_position(list_t *L)
{

    list_t *parcours = L;

    if (parcours != NULL)
    {

        pos_t center;
        center.x = parcours->value.x;
        center.y = parcours->value.y;
        pos_t elt;

        while (parcours != NULL)
        {

            elt.x = parcours->value.x;
            elt.y = parcours->value.y;

            if ((1 < elt.x && elt.x < 4) && (1 < elt.y && elt.y < 4))
            {
                return elt; // si on a un élément centré on le renvoie direct
            }
            else if ((elt.x != 0 && elt.x != 5) && (elt.y != 0 && elt.y != 5))
            {
                // si on a un élément pas au bord

                if ((center.x == 0 || center.x == 5) && (center.y == 0 || center.y == 5))
                {
                    // mais que le centre précédent est au bord

                    center.x = elt.x;
                    center.y = elt.y;

                    // alors on a le centre qui prend cette valeur
                }
            }

            parcours = parcours->next;
        }

        return center;
    }
    else
    {

        // si la liste des positions est vide

        pos_t erreur;
        erreur.x = -1;
        erreur.y = -1;

        return erreur;
    }
}

/**
 * @brief Liste des cases vides
 *
 * @param board plateau de jeu
 */
list_t *list_empty_cases(board_t *board)
{
    list_t *res = NULL;
    int i, j;
    for (i = 0; i < GRID_SIZE; i++)
    {
        for (j = 0; j < GRID_SIZE; j++)
        {
            if (board->pieces[i][j] == 0)
            {
                // Ajouter un élément à la liste
                list_t *nouveau = malloc(sizeof(list_t));
                if (nouveau == NULL)
                {
                    fprintf(stderr, "Erreur d'allocation de mémoire\n");
                    exit(EXIT_FAILURE);
                }

                // Ajouter la position
                pos_t pos;
                pos.x = i;
                pos.y = j;
                nouveau->value = pos;

                // Ajouter à la liste
                nouveau->next = res;
                res = nouveau;
            }
        }
    }

    return res;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
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
                res = nouveau;
            }
        }
    }

    return res;
}

// Fonction qui renvoie une position la plus proche d'un pion ennemi parmi une liste de positions
pos_t closest_enemy(list_t *cases, game_state_t *game_state)
{
    list_t *current = cases;
    pos_t closest;
    closest.x = -1;
    closest.y = -1;
    int min_distance = 1000;
    while (current != NULL)
    {
        int i, j;
        for (i = 0; i < GRID_SIZE; i++)
        {
            for (j = 0; j < GRID_SIZE; j++)
            {
                if (game_state->board->pieces[i][j] == 3 - game_state->player) // Petit tricks
                {
                    int distance = abs(i - current->value.x) + abs(j - current->value.y);
                    if (distance < min_distance)
                    {
                        min_distance = distance;
                        closest.x = current->value.x;
                        closest.y = current->value.y;
                    }
                }
            }
        }
        current = current->next;
    }
    return closest;
}

void bird_placement(game_state_t *game_state, input_t *input)
{
    // Stratégie appliquée : placer l'oiseau sur la case
    pos_t pos_bird = closest_enemy(input->possible_moves, game_state);
    if (pos_bird.x == -1 && pos_bird.y == -1)
    {
        pos_bird = center_position(input->possible_moves);
    }

    // Placement de l'oiseau
    input->selected_case_1->x = pos_bird.x;
    input->selected_case_1->y = pos_bird.y;
    input->selected_case_2->x = -1;
    input->selected_case_2->y = -1;

    game_logic(game_state, input);
}

l_path_t *free_l_path(l_path_t *l_path)
{
    l_path_t *tmp = l_path;
    while (tmp != NULL)
    {
        l_path_t *next = tmp->next;
        free_list(tmp->possibilities);
        free(tmp->pos);
        free(tmp);
        tmp = next;
    }
    return NULL;
}

// Fonction d'évaluation ultra naïve basé sur le nombre de pièces de chaque joueur
int evaluate(game_state_t *game_state)
{
    int score = 0;

    if (game_state->winner == 2)
    {
        score = 1000;
    }
    else if (game_state->winner == 1)
    {
        score = -1000;
    }

    // Comptage des pièces sur le plateau
    int i, j;
    for (i = 0; i < GRID_SIZE; i++)
    {
        for (j = 0; j < GRID_SIZE; j++)
        {
            if (game_state->board->pieces[i][j] == 1)
            {
                score += 100;
            }
            else if (game_state->board->pieces[i][j] == 2)
            {
                score -= 100;
            }
        }
    }

    // Vérification au nombre de pièces menacées
    l_path_t *cases = playable_cases(game_state, 1);
    l_path_t *current = cases;
    while (current != NULL)
    {
        if (game_state->board->cases[current->pos->x][current->pos->y] == game_state->last_case)
        {
            list_t *current_possibility = current->possibilities;
            while (current_possibility != NULL)
            {
                if (game_state->board->pieces[current_possibility->value.x][current_possibility->value.y] == 2)
                {
                    if (game_state->board->daimyo_2->x == current_possibility->value.x && game_state->board->daimyo_2->y == current_possibility->value.y)
                    {
                        score -= 200; // Si le daimyo est menacé c'est encore pire
                    }
                    score -= 5; // Forcer l' aggression
                }
                current_possibility = current_possibility->next;
            }
        }

        current = current->next;
    }
    free_l_path(cases);

    // Même chose pour le joueur 2
    cases = playable_cases(game_state, 2);
    current = cases;
    while (current != NULL)
    {
        if (game_state->board->cases[current->pos->x][current->pos->y] == game_state->last_case)
        {
            list_t *current_possibility = current->possibilities;
            while (current_possibility != NULL)
            {
                if (game_state->board->pieces[current_possibility->value.x][current_possibility->value.y] == 1)
                {
                    if (game_state->board->daimyo_1->x == current_possibility->value.x && game_state->board->daimyo_1->y == current_possibility->value.y)
                    {
                        score += 200; // Si le daimyo est menacé c'est lezzgo
                    }
                    score += 10;
                }
                current_possibility = current_possibility->next;
            }
        }

        current = current->next;
    }
    free_l_path(cases);

    return score;
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

    copy->daimyo_1 = malloc(sizeof(pos_t));
    copy->daimyo_2 = malloc(sizeof(pos_t));
    copy->daimyo_1->x = board->daimyo_1->x;
    copy->daimyo_1->y = board->daimyo_1->y;
    copy->daimyo_2->x = board->daimyo_2->x;
    copy->daimyo_2->y = board->daimyo_2->y;

    copy->bird = malloc(sizeof(pos_t));
    copy->bird->x = board->bird->x;
    copy->bird->y = board->bird->y;

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

int min_max(game_state_t *game_state, int depth)
{
    // Création de l'input
    input_t *input = malloc(sizeof(input_t));
    init_input(input);

    int score = evaluate(game_state);
    if (depth == 0)
    {
        free_input(input);
        return score;
    }

    int best;

    if (game_state->player == 2) // Bot = max
    {
        best = -1000;
    }
    else // Joueur = min
    {
        best = 1000;
    }
    l_path_t *cases = playable_cases(game_state, game_state->player);
    l_path_t *current = cases;
    while (current != NULL) // Pour tous les coups
    {
        list_t *current_possibility = current->possibilities;
        while (current_possibility != NULL) // Pour tous les mouvements possibles pour ce coup
        {
            // Copier la situation du jeu
            game_state_t *copy = copy_game_state(game_state);

            // Si le joueur est bloqué, Restaurer le pion au plus proche du centre
            if (copy->player_blocked)
            {
                if (copy->player == 1) // Exception si c'est le joueur adverse, on ne veut surtout pas ça (pire situation)
                {
                    cases = free_l_path(cases);
                    free_game_state(copy);
                    free_input(input);
                    return -999;
                }
                else
                {
                    if (game_state->captured_pieces[game_state->player] > 0) // Restaurer un pion si possible.
                    {
                        list_t *empty_cases = list_empty_cases(copy->board);
                        pos_t center = center_position(empty_cases);
                        input->selected_case_1->x = center.x;
                        input->selected_case_1->y = center.y;
                        input->selected_case_2->x = -1;
                        input->selected_case_2->y = -1;
                        free_list(empty_cases);
                    }
                    else
                    {
                        input->selected_case_1->x = current->pos->x;
                        input->selected_case_1->y = current->pos->y;
                        input->selected_case_2->x = -1;
                        input->selected_case_2->y = -1;
                        game_logic(copy, input); // Prendre le focus dans la fonction...
                        input->selected_case_1->x = current->pos->x;
                        input->selected_case_1->y = current->pos->y;
                        input->selected_case_2->x = current_possibility->value.x;
                        input->selected_case_2->y = current_possibility->value.y;
                    }
                    game_logic(copy, input); // Jouer le coup
                }
            }
            else // Situation normale
            {
                // Mettre l'input à jour
                input->selected_case_1->x = current->pos->x;
                input->selected_case_1->y = current->pos->y;
                input->selected_case_2->x = current_possibility->value.x;
                input->selected_case_2->y = current_possibility->value.y;

                game_logic(copy, input); // Jouer le coup

                if (copy->winner == 2) // L'ia gagne
                {
                    cases = free_l_path(cases);
                    free_game_state(copy);
                    free_input(input);
                    return 1000;
                }
                else if (copy->winner == 1) // L'ia perd
                {
                    cases = free_l_path(cases);
                    free_game_state(copy);
                    free_input(input);
                    return -1000;
                }
            }

            // Placement de l'oiseau
            if (copy->phase == 1)
            {
                bird_placement(copy, input);
            }

            int res = min_max(copy, depth - 1);
            if (game_state->player == 2) // Bot = max
            {
                best = max(best, res);
            }
            else // Joueur = min
            {
                best = min(best, res);
            }

            free_game_state(copy);

            // Passage au prochain mouvement possible
            current_possibility = current_possibility->next;
        }

        // Passage au prochain coup
        current = current->next;
    }
    cases = free_l_path(cases);
    free_input(input);
    return best;
}

/**
 * @brief Fonction qui retourne le meilleur coup à jouer pour l'IA (sans tenir compte de l'oiseau)
 *
 * @param game_state Etat du jeu
 */
input_t *best_move(game_state_t *game_state)
{
    // Lister tous les coups possibles
    l_path_t *cases = playable_cases(game_state, game_state->player);
    l_path_t *current = cases;

    input_t *best_move = malloc(sizeof(input_t));
    best_move->selected_case_1 = malloc(sizeof(pos_t));
    best_move->selected_case_2 = malloc(sizeof(pos_t));
    best_move->possible_moves = NULL;

    int max = -1000;

    if (current == NULL)
    {
        fprintf(stderr, "[WARNING] Aucune pièce disponible pour l'IA \n");
    }
    while (current != NULL) // Pour tous les coups
    {
        list_t *current_possibility = current->possibilities;
        while (current_possibility != NULL) // Pour tous les mouvements possibles pour ce coup
        {
            int res = min_max(game_state, 3);
            if (res >= max)
            {
                max = res;
                best_move->selected_case_1->x = current->pos->x;
                best_move->selected_case_1->y = current->pos->y;
                best_move->selected_case_2->x = current_possibility->value.x;
                best_move->selected_case_2->y = current_possibility->value.y;
            }

            current_possibility = current_possibility->next;
        }

        // Passage au prochain coup
        current = current->next;
    }
    cases = free_l_path(cases);
    return best_move;
}

/**
 * @brief Fonction qui joue le coup de l'adversaire
 *
 * @param game_state Etat du jeu
 */
void play_opponent(game_state_t *game_state)
{
    input_t *best = best_move(game_state);

    game_logic(game_state, best);

    // Placement de l'oiseau
    if (game_state->phase == 1)
    {
        bird_placement(game_state, best);
    }

    // Libération de la mémoire
    free_input(best);
}