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
                                  ui->screen_w,
                                  ui->screen_h,
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
    pos.x = (x - (ui->screen_w / 2 - ui->board_size / 2)) / 100;
    pos.y = (y - (ui->screen_h / 2 - ui->board_size / 2)) / 100;
    return pos;
}

/*
 * @brief Fonction pour récupérer les événements
 *
 * @param game Structure de l'état du jeu
 */
void get_input(ui_t *ui, input_t *input)
{
    int selection = 1;
    if (input->selected_case_1->x != -1 && input->selected_case_1 != -1)
    {
        selection = 2;
    }

    /* Gestion des événements */
    while (SDL_PollEvent(&ui->event))
    {
        switch (ui->event.type)
        {
        case SDL_QUIT:
            ui->program_on = SDL_FALSE;
            break;

        case SDL_MOUSEBUTTONDOWN: // Clic souris
            if (ui->event.button.button == SDL_BUTTON_LEFT)
            {
                int x = ui->event.button.x;
                int y = ui->event.button.y;

                pos_t case_grid = cord2grid(ui, x, y);

                if (selection == 1)
                {
                    input->selected_case_1->x = case_grid.x;
                    input->selected_case_1->y = case_grid.y;
                }
                else
                {
                    input->selected_case_2->x = case_grid.x;
                    input->selected_case_2->y = case_grid.y;
                }
            }
            break;
        }
    }
}

/*
    // Charger les ressources pour le menu pause
    SDL_Texture *background_texture = NULL;
    SDL_Texture *continue_text = NULL;
    SDL_Texture *quit_text = NULL;

    if (!load_resources(ui->renderer, &background_texture, ui->window, &continue_text, &quit_text)) {
        // Gestion de l'échec du chargement des ressources
        SDL_Log("Échec du chargement des ressources");
        free(game);
        free(board);
        unload_textures(ui->textures);
        end_sdl(0, "Le programme s'est terminé correctement", ui->window, ui->renderer);
        free(ui);
        return -1;
    }

    // Définitions des rectangles des boutons pour le menu pause
    int text_width, text_height;

    SDL_QueryTexture(continue_text, NULL, NULL, &text_width, &text_height);
    SDL_Rect continue_button_rect = {ui->SCREEN_WIDTH / 2 - 100 - 5, 250, 200, text_height + 20};

    SDL_QueryTexture(quit_text, NULL, NULL, &text_width, &text_height);
    SDL_Rect quit_button_rect = {ui->SCREEN_WIDTH / 2 - 100, ui->SCREEN_HEIGHT - 200 - 10, 200, text_height + 20};
     */

// Libération des ressources et nettoyage
/*
SDL_DestroyTexture(background_texture);
SDL_DestroyTexture(continue_text);
SDL_DestroyTexture(quit_text);*/