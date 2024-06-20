#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "headers/struct.h"
#include "headers/rules.h"

#define GRID_SIZE 6

/**
 * @file sdl_common.c
 * @brief Fonctions communes à l'initialisation de la SDL
 * @version 1.0
 * @date 2023-06-18
 * @author Team 21
 */

/**
 * @brief Fermeture de la SDL
 *
 * @param ok Fin normale : ok = 0 ; anormale ok = 1
 * @param msg Message à afficher
 * @param window Fenêtre à fermer
 * @param renderer Renderer à fermer
 */
void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer)
{
    char msg_formated[255];
    int l;

    if (!ok)
    {
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL)
    {                                  // Destruction si nécessaire du renderer
        SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
        renderer = NULL;
    }
    if (window != NULL)
    {                              // Destruction si nécessaire de la fenêtre
        SDL_DestroyWindow(window); // Attention : on suppose que les NULL sont maintenus !!
        window = NULL;
    }

    SDL_Quit();

    if (!ok)
    {
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Charge une texture à partir d'une image
 *
 * @param file_image_name Nom du fichier image
 * @param window Fenêtre SDL
 * @param renderer Renderer SDL
 * @return SDL_Texture* Texture chargée
 */
SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Surface *my_image = NULL;   // Variable de passage
    SDL_Texture *my_texture = NULL; // La texture

    my_image = IMG_Load(file_image_name); // Chargement de l'image dans la surface
                                          // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL,
                                          // uniquement possible si l'image est au format bmp */
    if (my_image == NULL)
        end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire
    if (my_texture == NULL)
        end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}

/**
 * @brief Charge toutes les textures du jeu
 *
 * @param textures Tableau de textures
 * @param renderer Renderer SDL
 * @param window Fenêtre SDL
 */
void load_textures(SDL_Texture *textures[10], SDL_Renderer *renderer, SDL_Window *window)
{
    /* Assets d'images */
    // textures[0] = load_texture_from_image("assets/board/board.png", window, renderer);
    textures[1] = load_texture_from_image("assets/pieces/rhonin_black.png", window, renderer);
    textures[2] = load_texture_from_image("assets/pieces/rhonin_white.png", window, renderer);
    textures[3] = load_texture_from_image("assets/pieces/daimio_black.png", window, renderer);
    textures[4] = load_texture_from_image("assets/pieces/daimio_white.png", window, renderer);
    textures[5] = load_texture_from_image("assets/board/case1.png", window, renderer);
    textures[6] = load_texture_from_image("assets/board/case2.png", window, renderer);
    textures[7] = load_texture_from_image("assets/board/case3.png", window, renderer);

    /* Assets de texte */
    TTF_Font *metal_lord = TTF_OpenFont("assets/otf/metal_lord.otf", 100);
    SDL_Color Black = {0, 0, 0, 255};
    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(metal_lord, "Mana", Black);
    if (surfaceMessage == NULL)
        end_sdl(0, "Erreur lors de la création de la surface de texte", window, renderer);
    textures[8] = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    textures[9] = load_texture_from_image("assets/pieces/bird.png", window, renderer);

    return;
}

void init_sdl(ui_t *ui)
{
    /* Initialisation de la SDL */
    ui->renderer = NULL;
    ui->window = NULL;
    /* Initialisation SDL */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Création de la fenêtre et du renderer */
    ui->window = SDL_CreateWindow("Mana (pre-alpha)",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  ui->SCREEN_WIDTH,
                                  ui->SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
    if (ui->window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", ui->window, ui->renderer);
    ui->renderer = SDL_CreateRenderer(ui->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ui->renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", ui->window, ui->renderer);
    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", ui->window, ui->renderer);

    /* Loading de toutes les textures dans un tableau */
    load_textures(ui->textures, ui->renderer, ui->window);
}

/**
 * @brief Décharge toutes les textures du jeu
 *
 * @param textures Tableau de textures
 */
void unload_textures(SDL_Texture *textures[10])
{
    SDL_DestroyTexture(textures[1]);
    SDL_DestroyTexture(textures[2]);
    SDL_DestroyTexture(textures[3]);
    SDL_DestroyTexture(textures[4]);
    SDL_DestroyTexture(textures[5]);
    SDL_DestroyTexture(textures[6]);
    SDL_DestroyTexture(textures[7]);
    SDL_DestroyTexture(textures[8]);
}

/**
 * @brief Charge la police d'écriture
 *
 * @param message Message afficher
 * @param font_file Le path à charger
 * @param color  La couleur de la police
 * @param font_size La taille de la police
 * @param renderer Renderer SDL
 */
SDL_Texture *render_text(const char *message, const char *font_file, SDL_Color color, int font_size, SDL_Renderer *renderer)
{
    TTF_Font *font = TTF_OpenFont(font_file, font_size);
    if (!font)
    {
        SDL_Log("ERROR: Unable to open font %s: %s\n", font_file, TTF_GetError());
        return NULL;
    }
    SDL_Surface *surface = TTF_RenderText_Blended(font, message, color);
    if (!surface)
    {
        SDL_Log("ERROR: Unable to create text surface: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    if (!texture)
    {
        SDL_Log("ERROR: Unable to create texture from text: %s\n", SDL_GetError());
        return NULL;
    }
    return texture;
}

pos_t cord2grid(ui_t *ui, int x, int y)
{
    pos_t pos;
    pos.x = (x - (ui->SCREEN_WIDTH / 2 - ui->BOARD_SIZE / 2)) / 100;
    pos.y = (y - (ui->SCREEN_HEIGHT / 2 - ui->BOARD_SIZE / 2)) / 100;
    return pos;
}

void move_piece_to(board_t *board, pos_t origin, pos_t destination)
{
    board->board_piece[destination.x][destination.y] = board->board_piece[origin.x][origin.y];
    board->board_piece[origin.x][origin.y] = 0;
}

void print_list(list_t *list)
{
    list_t *tmp = list;
    while (tmp != NULL)
    {
        printf("(%d, %d)\n", tmp->pos.x, tmp->pos.y);
        tmp = tmp->next;
    }
}

void free_list(list_t *list)
{
    list_t *tmp = list;
    while (tmp != NULL)
    {
        list_t *next = tmp->next;
        free(tmp);
        tmp = next;
    }
}

bool can_be_selected(game_t *game, board_t *board, pos_t pos_grid)
{
    bool good_player = board->board_piece[pos_grid.x][pos_grid.y] == game->playing_player || board->board_piece[pos_grid.x][pos_grid.y] == game->playing_player + 2;
    if (game->last_case_value == 0)
    {
        return good_player;
    }
    else
    {
        return good_player && board->board_case[pos_grid.x][pos_grid.y] == game->last_case_value;
    }
}

void init_predictions(game_t *game)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            game->predictions[i][j] = 0;
        }
    }
}

// Vérifie si une pièce est bloquée
bool is_piece_blocked(game_t *game, board_t *board, int i, int j)
{
    // Si la pièce n'est pas sur la dernière case sélectionnée.
    /*if (board->board_case[i][j] != game->last_case_value)
    {
        return true;
    }*/

    init_predictions(game);
    predictions_calculations(game, board, (pos_t){i, j}, board->board_case[i][j], 1);
    for (int k = 0; k < GRID_SIZE; k++)
    {
        for (int k = 0; k < GRID_SIZE; k++)
        {
            if (game->predictions[i][j] == 1)
            {
                return false;
            }
        }
    }
}

// blocage total: aucune pièce positionnée sur une case de bonne valeur ?
bool is_active_player_blocked(game_t *game, board_t *board)
{

    if (game->last_case_value==-1){
        return false;
    }
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (game->playing_player==1){  //joueur noir
                if (board->board_piece[i][j]==1 || board->board_piece[i][j]==3){
                    //si on a une piece noire
                    if (game->last_case_value==board->board_case[i][j]){
                        //et qu'elle est sur une case bonne valeur
                        return false;
                    }
                }
            } else {  //joueur blanc
                if (board->board_piece[i][j]==2 || board->board_piece[i][j]==4){
                    //si on a une pièce blanche
                    if (game->last_case_value==board->board_case[i][j]){
                        //et qu'elle est sur une case bonne valeur

                        return false;
                    }
                }
            }
            
            
            /*if ((board->board_piece[i][j] == 1 || board->board_piece[i][j] == 3) && game->playing_player == 1)
            {
                if (!is_piece_blocked(game, board, i, j))
                {
                    return false;
                }
            }
            else if ((board->board_piece[i][j] == 2 || board->board_piece[i][j] == 4) && game->playing_player == 2)
            {
                if (!is_piece_blocked(game, board, i, j))
                {
                    return false;
                }
            }*/
        }
    }

    return true; //aucune pièce sur une case de bonne valeur
}

void capturing_piece(game_t *game, board_t *board, pos_t destination)
{
    if (game->playing_player == 1)
    { // joueur noir
        if (board->board_piece[destination.x][destination.y] == 2)
        { // on va sur un ronin blanc
            board->captured_white_pieces += 1;
        }
    }
    else
    { // joueur blanc
        if (board->board_piece[destination.x][destination.y] == 1)
        { // on va sur un ronin noir
            board->captured_black_pieces += 1;
        }
    }
}

//blocage partiel: une pièce est sur une case de bonne valeur mais elle ne peut être jouée ?
bool pieces_are_blocked(game_t *game, board_t *board){

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (game->playing_player==1){  //joueur noir
                if (board->board_piece[i][j]==1 || board->board_piece[i][j]==3){
                    //si on a une piece noire
                    if (game->last_case_value==board->board_case[i][j] && is_piece_blocked(game, board, i, j)){
                        //et qu'elle est sur une case bonne valeur mais est bloquée
                        return true;
                    }
                }
            } else {  //joueur blanc
                if (board->board_piece[i][j]==2 || board->board_piece[i][j]==4){
                    //si on a une pièce blanche
                    if (game->last_case_value==board->board_case[i][j] && is_piece_blocked(game, board, i, j)){
                        //et qu'elle est sur une case bonne valeur mais est bloquée

                        return true;
                    }
                }
            }

        }
        
    }
    return false;    
}

void player_change(game_t * game){
    if (game->playing_player == 1)
    {
        game->playing_player = 2;
    }
    else
    {
        game->playing_player = 1;
    }
}
/*
 * @brief Fonction pour récupérer les événements
 *
 * @param game Structure de l'état du jeu
 */
void get_input(ui_t *ui, game_t *game, board_t *board)
{
    /* Gestion des événements */
    while (SDL_PollEvent(&game->event))
    {
        if (game->playing_player == -1)
        {
            fprintf(stderr, "WARNING : playing_player = -1\n");
        }

        switch (game->event.type)
        {
        case SDL_QUIT:
            game->program_on = SDL_FALSE;
            break;
            if (game->inPause)
            {
                /*handle_events(&game->event, &game->program_on, &game->inPause, ui->continue_button_rect, ui->quit_button_rect);*/
            }
            else
            {
            case SDL_MOUSEBUTTONDOWN: // Clic souris
                if (game->event.button.button == SDL_BUTTON_LEFT)
                {
                    int x = game->event.button.x;
                    int y = game->event.button.y;

                    pos_t case_grid = cord2grid(ui, x, y);

                    // Cliquer dans le plateau
                    if (case_grid.x >= 0 && case_grid.x < GRID_SIZE && case_grid.y >= 0 && case_grid.y < GRID_SIZE)
                    {
                        if (game->case_is_selected)
                        {
                            
                            if (is_active_player_blocked(game, board)) //blocage total
                            {
                                //printf("Joueur %d bloqué\n", game->playing_player);
                                //init_predictions(game);
                                
                                if (game->playing_player==1){
                                    game->blocage=1;
                                } else {
                                    game->blocage=2;

                                }

                                if (respawning_possible(game, board, case_grid)){
                                    respawning(game, board, case_grid);
                                    game->blocage=0;
                                }
                                player_change(game);

                            } else if (pieces_are_blocked(game, board)) { //blocage partiel

                                player_change(game);
                                if (game->playing_player==1){
                                    game->blocage=1;
                                } else {
                                    game->blocage=2;

                                }
                                if (respawning_possible(game, board, case_grid)){
                                    respawning(game, board, case_grid);
                                    game->blocage=0;
                                }                            
                                player_change(game);

                            } 
                            
                            if (game->predictions[case_grid.x][case_grid.y] == 1)
                            {
                                // Déplacer le pion sur la case
                                capturing_piece(game, board, case_grid);
                                move_piece_to(board, *game->selected_case, case_grid);
                                game->last_case_value = board->board_case[case_grid.x][case_grid.y];
                                fprintf(stderr, "LAST CASE VALUE %d\n", game->last_case_value);
                                game->case_is_selected = false;
                                game->selected_case->x = -1;
                                game->selected_case->y = -1;

                                // Passage en mode oiseau
                                game->bird_is_selected = true;
                                init_predictions(game);
                                bird_predictions_calculations(game, board);
                                // game->predictions[board->bird->x][board->bird->y] = -1; WTF
                            }
                            else
                            {
                                game->selected_case->x = -1;
                                game->selected_case->y = -1;
                                game->case_is_selected = false;
                            }
                        }
                        else if (!game->bird_is_selected && can_be_selected(game, board, case_grid))
                        {
                            printf("Case sélectionnée\n");
                            game->selected_case->x = case_grid.x;
                            game->selected_case->y = case_grid.y;
                            game->case_is_selected = true;

                            init_predictions(game);
                            predictions_calculations(game, board, *game->selected_case, board->board_case[game->selected_case->x][game->selected_case->y], game->playing_player);
                        }
                        else if (game->bird_is_selected && game->predictions[case_grid.x][case_grid.y] == 1) // Sélection de l'oiseau
                        {
                            if (board->bird->x == -1 && board->bird->y == -1)
                            {
                                board->bird->x = case_grid.x;
                                board->bird->y = case_grid.y;

                                board->board_piece[board->bird->x][board->bird->y] = 5;
                            }
                            else
                            {
                                move_piece_to(board, (pos_t){board->bird->x, board->bird->y}, case_grid);
                                board->bird->x = case_grid.x;
                                board->bird->y = case_grid.y;
                            }

                            game->bird_is_selected = false;

                            // Changement de joueur
                            player_change(game);

                        }
                        else
                        {
                            game->selected_case->x = -1;
                            game->selected_case->y = -1;
                            game->case_is_selected = false;
                            printf("Case non sélectionnée\n");
                        }
                    }
                    int winner = who_wins(board);
                    if (winner != 0)
                    {
                        printf("Joueur %d a gagné\n", winner);
                        game->program_on = SDL_FALSE;
                    }

                    printf("Clic en (%d, %d)\n", x, y);
                    printf("Case en (%d, %d)\n", case_grid.x, case_grid.y);
                }
                break;
            }
        }
    }
}
