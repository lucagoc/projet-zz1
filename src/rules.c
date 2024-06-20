#include <stdbool.h>
#include <stdlib.h>
#include "headers/struct.h"

#define GRID_SIZE 6
#define BOARD_SIZE 6

/**
 * @file rules.c
 * @brief Fonctions correspondant aux règles du jeu (algorithmique)
 * @version 1.0
 * @date 2023-06-19
 * @author Team 21
 */

/**
 * @brief Initialise l'état de la partie
 *
 * @param game_state Etat de la partie
 * @return void
 */
void init_game_state(game_state_t *game_state)
{
    game_state->player = 1;
    game_state->round = 0;
    game_state->last_case = 0;
    game_state->player_blocked = false;
    game_state->phase = 0;

    game_state->captured_pieces[0] = 0; // Inutilisé
    game_state->captured_pieces[1] = 0;
    game_state->captured_pieces[2] = 0;
}

/**
 * @brief Initialise le plateau avec les cases 1 2 3 (noir en bas, blanc en haut)
 *
 * @param board Fin normale : plateau initialisé ; anormale plateau mal initialisé
 */
board_t *init_board(board_t *board)
{
    // Initialisation des cases
    board->cases[0][0] = 2;
    board->cases[1][0] = 3;
    board->cases[2][0] = 1;
    board->cases[3][0] = 2;
    board->cases[4][0] = 2;
    board->cases[5][0] = 3;
    board->cases[0][1] = 2;
    board->cases[1][1] = 1;
    board->cases[2][1] = 3;
    board->cases[3][1] = 1;
    board->cases[4][1] = 3;
    board->cases[5][1] = 1;
    board->cases[0][2] = 1;
    board->cases[1][2] = 3;
    board->cases[2][2] = 2;
    board->cases[3][2] = 3;
    board->cases[4][2] = 1;
    board->cases[5][2] = 2;
    board->cases[0][3] = 3;
    board->cases[1][3] = 1;
    board->cases[2][3] = 2;
    board->cases[3][3] = 1;
    board->cases[4][3] = 3;
    board->cases[5][3] = 2;
    board->cases[0][4] = 2;
    board->cases[1][4] = 3;
    board->cases[2][4] = 1;
    board->cases[3][4] = 3;
    board->cases[4][4] = 1;
    board->cases[5][4] = 3;
    board->cases[0][5] = 2;
    board->cases[1][5] = 1;
    board->cases[2][5] = 3;
    board->cases[3][5] = 2;
    board->cases[4][5] = 2;
    board->cases[5][5] = 1;

    // Initialisation de l'oiseau
    board->bird = (pos_t *)malloc(sizeof(pos_t));
    board->bird->x = -1;
    board->bird->y = -1;

    // Initialisation des pièces
    for (int i = 0; i < BOARD_SIZE; i++) // Placement de 0 sur tout le plateau
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board->pieces[i][j] = 0;
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++) // Placement de 1 sur la première ligne
    {
        board->pieces[i][0] = 1;
    }
    for (int i = 0; i < BOARD_SIZE; i++) // Placement de 2 sur la dernière ligne
    {
        board->pieces[i][BOARD_SIZE - 1] = 2;
    }

    // Initialisation des daimyos
    board->daimyo_1 = (pos_t *)malloc(sizeof(pos_t));
    board->daimyo_1->x = 2;
    board->daimyo_1->y = 0;
    board->daimyo_2 = (pos_t *)malloc(sizeof(pos_t));
    board->daimyo_2->x = 3;
    board->daimyo_2->y = 5;

    return board;
}

/*
 * @brief Vérifie si la position donnée en entrée est un daimyo
 *
 * @param position Position à vérifier
 * @param board Plateau de jeu
 * @return true Si la position est un daimyo
 * @return false Si la position n'est pas un daimyo
 */
bool is_daimyo(pos_t position, board_t *board)
{
    return (board->daimyo_1->x == position.x && board->daimyo_1->y == position.y) || (board->daimyo_2->x == position.x && board->daimyo_2->y == position.y);
}

/*
 * @brief Vérifie si la position donnée en entrée est valide
 *
 * @param position Position à vérifier
 * @return true Si la position est valide
 * @return false Si la position n'est pas valide
 */
bool is_pos_valid(pos_t position)
{
    return position.x >= 0 && position.y >= 0 && position.x < GRID_SIZE && position.y < GRID_SIZE;
}

/*
 * @brief Vérifie si la position donnée en entrée est vide
 *
 * @param position Position à vérifier
 * @param board Plateau de jeu
 * @return true Si la position est vide
 * @return false Si la position n'est pas vide
 */
bool is_pos_empty(pos_t position, board_t *board)
{
    return board->pieces[position.x][position.y] == 0;
}

/*
 * @brief Vérifie si la position donnée en entrée est occupée
 *
 * @param position Position à vérifier
 * @param board Plateau de jeu
 * @return int 0 Si la position est vide
 * @return int 1 Si la position est occupée par le joueur 1
 * @return int 2 Si la position est occupée par le joueur 2
 */
int is_pos_occupied(pos_t position, board_t *board)
{
    return board->pieces[position.x][position.y];
}

/*
 * @brief Vérifie si un mouvement est valide pour un joueur donné
 *
 * @param origin Position de départ
 * @param destination Position d'arrivée
 * @param board Plateau de jeu
 * @param player Joueur
 * @return true Si le mouvement est valide
 * @return false Si le mouvement n'est pas valide
 */
bool is_move_valid(pos_t origin, pos_t destination, board_t *board, int player)
{
    if (board->bird->x == destination.x && board->bird->y == destination.y)
    {
        return false;
    }
    if (!is_pos_valid(origin) || !is_pos_valid(destination))
    {
        return false;
    }
    if (is_pos_empty(destination, board))
    {
        return true;
    }
    else
    {
        if (is_pos_occupied(destination, board) == player)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

/*
 * @brief Vérifie si un mouvement est valide pour un joueur donné
 *
 * @param destination Position d'arrivée
 * @param board Plateau de jeu
 * @param input Entrée utilisateur
 * @param player Joueur
 * @return true Si le mouvement est valide
 * @return false Si le mouvement n'est pas valide
 */
bool is_move_valid_play(pos_t destination, board_t *board, input_t *input, int player)
{
    if (!is_pos_valid(destination) || is_pos_occupied(destination, board) == player)
    {
        return false;
    }
    else
    {
        // Vérifier que le mouvement est dans la liste des mouvements possibles
        list_t *current = input->possible_moves;
        while (current != NULL)
        {
            if (current->value.x == destination.x && current->value.y == destination.y)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }
}

/*
 * @brief Concatène deux listes
 *
 * @param list1 Première liste
 * @param list2 Deuxième liste
 * @return list_t* Liste concaténée
 */
list_t *concat_list(list_t *list1, list_t *list2)
{
    if (list2 == NULL)
    {
        return list1;
    }
    else
    {
        list_t *current = list2;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = list1;
    }

    return list2;
}

/*
 * @brief Liste des mouvements possibles pour un rhonin (fonction auxiliaire)
 *
 * @param position Position actuelle
 * @param board Plateau de jeu
 * @param step Nombre de cases à parcourir
 * @param player Joueur
 * @param previous_tab Tableau des cases déjà visitées
 * @return list_t* Liste des mouvements possibles
 * @return NULL Si aucun mouvement possible ou si la case est déjà visitée
 */
list_t *list_rhonin_possible_moves_aux(pos_t position, board_t *board, int step, int player, int **previous_tab)
{
    if (is_pos_valid(position) && previous_tab[position.x][position.y] == 0 && (position.x != board->bird->x || position.y != board->bird->y) && is_pos_occupied(position, board) != player)
    {
        if (step == 0 && is_move_valid(position, position, board, player))
        {
            list_t *new_move = (list_t *)malloc(sizeof(list_t));
            new_move->value = position;
            new_move->next = NULL;
            return new_move;
        }
        else if (step == 0)
        {
            return NULL;
        }
        else
        {
            // Copier le tableau previous_tab
            int **previous_moves = malloc(GRID_SIZE * sizeof(int *));
            for (int i = 0; i < GRID_SIZE; i++)
            {
                previous_moves[i] = (int *)malloc(GRID_SIZE * sizeof(int));
                for (int j = 0; j < GRID_SIZE; j++)
                {
                    previous_moves[i][j] = previous_tab[i][j];
                }
            }
            previous_moves[position.x][position.y] = 1;

            list_t *possible_moves_list = NULL;
            // Déplacement vers le haut;
            possible_moves_list = concat_list(possible_moves_list, list_rhonin_possible_moves_aux((pos_t){position.x, position.y - 1}, board, step - 1, player, previous_moves));
            // Déplacement vers le bas
            possible_moves_list = concat_list(possible_moves_list, list_rhonin_possible_moves_aux((pos_t){position.x, position.y + 1}, board, step - 1, player, previous_moves));
            // Déplacement vers la gauche
            possible_moves_list = concat_list(possible_moves_list, list_rhonin_possible_moves_aux((pos_t){position.x - 1, position.y}, board, step - 1, player, previous_moves));
            // Déplacement vers la droite
            possible_moves_list = concat_list(possible_moves_list, list_rhonin_possible_moves_aux((pos_t){position.x + 1, position.y}, board, step - 1, player, previous_moves));

            free(previous_moves);
            return possible_moves_list;
        }
    }
    else
    {
        return NULL;
    }
}

/*
 * @brief Liste des mouvements possibles pour un rhonin
 *
 * @param position Position actuelle
 * @param board Plateau de jeu
 * @param step Nombre de cases à parcourir
 * @param player Joueur
 * @return list_t* Liste des mouvements possibles
 */
list_t *list_rhonin_possible_moves(pos_t position, board_t *board, int step, int player)
{
    int **previous_moves = malloc(GRID_SIZE * sizeof(int *));
    for (int i = 0; i < GRID_SIZE; i++)
    {
        previous_moves[i] = (int *)malloc(GRID_SIZE * sizeof(int));
        for (int j = 0; j < GRID_SIZE; j++)
        {
            previous_moves[i][j] = 0;
        }
    }

    list_t *res = NULL;
    // Déplacement vers le haut;
    res = concat_list(res, list_rhonin_possible_moves_aux((pos_t){position.x, position.y - 1}, board, step - 1, player, previous_moves));
    // Déplacement vers le bas
    res = concat_list(res, list_rhonin_possible_moves_aux((pos_t){position.x, position.y + 1}, board, step - 1, player, previous_moves));
    // Déplacement vers la gauche
    res = concat_list(res, list_rhonin_possible_moves_aux((pos_t){position.x - 1, position.y}, board, step - 1, player, previous_moves));
    // Déplacement vers la droite
    res = concat_list(res, list_rhonin_possible_moves_aux((pos_t){position.x + 1, position.y}, board, step - 1, player, previous_moves));

    free(previous_moves);
    return res;
}

/*
 * @brief Liste des mouvements possibles pour un oiseau
 *
 * @param board Plateau de jeu
 * @return list_t* Liste des mouvements possibles
 */
list_t *list_bird_possible_moves(game_state_t *game_state)
{
    list_t *possible_moves_list = NULL;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (is_pos_valid((pos_t){i, j}) && is_pos_occupied((pos_t){i, j}, game_state->board) == 0 && (game_state->board->cases[i][j] == game_state->last_case))
            {
                list_t *new_move = (list_t *)malloc(sizeof(list_t));
                new_move->value = (pos_t){i, j};
                new_move->next = possible_moves_list;
                possible_moves_list = new_move;
            }
        }
    }

    return possible_moves_list;
}

/*
 * @brief Déplace une pièce d'une position à une autre
 *
 * @param origin Position de départ
 * @param destination Position d'arrivée
 * @param game_state Etat de la partie
 * @return void
 */
void move_piece(pos_t origin, pos_t destination, game_state_t *game_state)
{
    // Si c'est un daimyo, il faut déplacer ses coordonnée aussi
    if (is_daimyo(origin, game_state->board))
    {
        if (game_state->player == 1)
        {
            game_state->board->daimyo_1->x = destination.x;
            game_state->board->daimyo_1->y = destination.y;
        }
        else
        {
            game_state->board->daimyo_2->x = destination.x;
            game_state->board->daimyo_2->y = destination.y;
        }
    }
    game_state->board->pieces[destination.x][destination.y] = game_state->board->pieces[origin.x][origin.y];
    game_state->board->pieces[origin.x][origin.y] = 0;
}

/*
 * @brief Détermine le gagnant de la partie
 *
 * @param board Plateau de jeu
 * @return int 0 Si personne n'a gagné
 * @return int 1 Si le joueur 1 a gagné
 * @return int 2 Si le joueur 2 a gagné
 */
int who_wins(board_t *board)
{
    if (board->pieces[board->daimyo_1->x][board->daimyo_1->y] != 1)
    {
        return 2;
    }
    if (board->pieces[board->daimyo_2->x][board->daimyo_2->y] != 2)
    {
        return 1;
    }
    return 0;
}

/*
 * @brief Filtrer une liste de cases en fonction de leur valeur
 *
 * @param list Liste à filtrer
 * @param case_value Valeur de la case à garder
 * @param board Plateau de jeu
 */
list_t *filter_case_list(list_t *list, int case_value, board_t *board)
{
    list_t *current = list;
    list_t *previous = NULL;
    while (current != NULL)
    {
        if (board->cases[current->value.x][current->value.y] != case_value)
        {
            if (previous == NULL)
            {
                list = current->next;
                free(current);
                current = list;
            }
            else
            {
                previous->next = current->next;
                free(current);
                current = previous->next;
            }
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    return list;
}

/*
 * @brief Vérifie si un joueur est bloqué totalement
 *
 * @param game_state Etat de la partie
 * @param player Joueur
 * @return true Si le joueur est bloqué
 * @return false Si le joueur n'est pas bloqué
 */
bool is_player_partially_blocked(game_state_t *game_state, int player)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (game_state->board->pieces[i][j] == player && game_state->board->cases[i][j] == game_state->last_case)
            {
                list_t *possible_moves = list_rhonin_possible_moves((pos_t){i, j}, game_state->board, game_state->board->cases[i][j], player);
                if (possible_moves != NULL)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

/*
 * @brief Vérifie si un joueur est bloqué totalement
 *
 * @param game_state Etat de la partie
 * @param player Joueur
 * @return true Si le joueur est bloqué
 * @return false Si le joueur n'est pas bloqué
 */
bool is_player_blocked(game_state_t *game_state, int player)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (game_state->board->pieces[i][j] == player && game_state->board->cases[i][j] == game_state->last_case)
            {
                return false;
            }
        }
    }
    return true;
}

/*
 * @brief Logique du jeu
 *
 * @param game_state Etat de la partie
 * @param input Entrée utilisateur
 * @return void
 */
void game_logic(game_state_t *game_state, input_t *input)
{
    int winner = who_wins(game_state->board);
    if (winner != 0)
    {
        printf("Joueur %d a gagné\n", who_wins(game_state->board));
        return;
    }
    else
    {
        if (game_state->player_blocked)
        {
            if ((input->selected_case_1->x < -1 || input->selected_case_1->x > 6) && game_state->captured_pieces[game_state->player] != 0) // Un peu sale
            {
                // Cliquer en dehors du plateau prend la décision de ressuciter une pièce
                if (input->selected_case_2->x != -1 && input->selected_case_2->y != -1)
                {
                    input->selected_case_1->x = input->selected_case_2->x;
                    input->selected_case_1->y = input->selected_case_2->y;
                    input->selected_case_2->x = -1;
                    input->selected_case_2->y = -1;

                    if (game_state->board->pieces[input->selected_case_1->x][input->selected_case_1->y] == 0)
                    {
                        game_state->board->pieces[input->selected_case_1->x][input->selected_case_1->y] = game_state->player;
                        game_state->captured_pieces[game_state->player]--;
                        game_state->phase = 1;
                    }
                }
            }
            else
            {
                // Cliquer dans le plateau prend la décision jouer un pion sans restriction de case.
                input->selected_case_1->x = -1;
                input->selected_case_1->y = -1;
                input->selected_case_2->x = -1;
                input->selected_case_2->y = -1;
                game_state->last_case = 0;
                game_state->player_blocked = false;
            }
        }
        // Vérification si il y a une input valide
        if (input->selected_case_1->x == -1 && input->selected_case_1->y == -1 && input->selected_case_2->x == -1 && input->selected_case_2->y == -1)
        {
            return;
        }

        // Sélection d'un pion
        if (input->selected_case_1->x != -1 && input->selected_case_1->y != -1) // Case 1 sélectionné
        {
            if (game_state->phase == 0) // Phase de choix du pion
            {
                // Vérifier si le pion peut être sélectionné
                if (is_pos_occupied(*input->selected_case_1, game_state->board) == game_state->player && (game_state->last_case == 0 || game_state->last_case == game_state->board->cases[input->selected_case_1->x][input->selected_case_1->y]))
                {
                    if (input->selected_case_2->x != -1 && input->selected_case_2->y != -1) // Case 2 sélectionné
                    {
                        // Déplacer le pion
                        if (is_move_valid_play(*input->selected_case_2, game_state->board, input, game_state->player))
                        {
                            move_piece(*input->selected_case_1, *input->selected_case_2, game_state);
                            game_state->last_case = game_state->board->cases[input->selected_case_2->x][input->selected_case_2->y];

                            game_state->phase = 1;
                            input->possible_moves = free_list(input->possible_moves);
                            input->possible_moves = list_bird_possible_moves(game_state);
                        }
                        else
                        {
                            fprintf(stderr, "Mouvement invalide\n");
                            input->possible_moves = free_list(input->possible_moves);
                        }
                        input->selected_case_1->x = -1;
                        input->selected_case_1->y = -1;
                        input->selected_case_2->x = -1;
                        input->selected_case_2->y = -1;
                    }
                    else // Case 1 sélectionné, pas de case 2
                    {
                        // Calcul des mouvements possibles
                        if (input->possible_moves != NULL)
                        {
                            free_list(input->possible_moves);
                        }

                        // Si c'est un rhonin
                        if (game_state->board->pieces[input->selected_case_1->x][input->selected_case_1->y] == game_state->player && game_state->phase == 0)
                        {
                            input->possible_moves = list_rhonin_possible_moves(*input->selected_case_1, game_state->board, game_state->board->cases[input->selected_case_1->x][input->selected_case_1->y], game_state->player);
                        }
                        else if (game_state->phase == 1)
                        {
                            input->possible_moves = list_bird_possible_moves(game_state);
                            print_list(input->possible_moves);
                        }
                    }
                }
                else
                {
                    input->selected_case_1->x = -1;
                    input->selected_case_1->y = -1;
                    input->selected_case_2->x = -1;
                    input->selected_case_2->y = -1;
                }
            }
            else if (game_state->phase == 1) // Choix de l'emplacement de l'oiseau si valide
            {
                if (is_pos_valid(*input->selected_case_1) && is_pos_empty(*input->selected_case_1, game_state->board) && game_state->last_case == game_state->board->cases[input->selected_case_1->x][input->selected_case_1->y])
                {
                    game_state->board->bird->x = input->selected_case_1->x;
                    game_state->board->bird->y = input->selected_case_1->y;
                    game_state->player = game_state->player == 1 ? 2 : 1;
                    game_state->phase = 0;
                    input->possible_moves = free_list(input->possible_moves);
                    game_state->round++;

                    bool player_1_blocked = is_player_blocked(game_state, 1);

                    if (is_player_partially_blocked(game_state, game_state->player) && !player_1_blocked)
                    {
                        // Changement de joueur
                        fprintf(stderr, "Joueur %d bloqué partiellement, changement de joueur\n", game_state->player);
                        game_state->player = game_state->player == 1 ? 2 : 1;
                        game_state->player_blocked = true;
                    }
                    else
                    {   
                        if(player_1_blocked)
                        {
                            game_state->player_blocked = true;
                            fprintf(stderr, "Joueur %d bloqué totalement\n", game_state->player);
                        }
                    }
                }
                else
                {
                    input->selected_case_1->x = -1;
                    input->selected_case_1->y = -1;
                    input->selected_case_2->x = -1;
                    input->selected_case_2->y = -1;
                }
            }
        }
        else
        {
            // Clear de la liste
            if (input->possible_moves != NULL)
            {
                input->possible_moves = free_list(input->possible_moves);
            }
        }
    }
}