#define STRUCT_H

#include <SDL2/SDL.h>
#include <stdbool.h>


struct pos_s
{
    int x;
    int y;
};
typedef struct pos_s pos_t;

struct list_s
{
    pos_t value;            // Valeur de la case
    struct list_s *next;    // Case suivante
};
typedef struct list_s list_t;

struct ui_s
{
    SDL_Renderer *renderer;             // Rendu SDL
    SDL_Window *window;                 // Fenêtre SDL
    SDL_Event event;                    // Évènement SDL
    SDL_Texture *textures[10];          // Textures
    SDL_Texture *textures_pause[10];    // Textures pour la pause

    int screen_w;          // Largeur de l'écran
    int screen_h;          // Hauteur de l'écran
    int board_size;        // Taille du plateau

    pos_t* selected_case;       // Case sélectionnée
    bool in_pause;              // Booléen pour la pause
    bool program_on;            // Booléen pour le programme
};
typedef struct ui_s ui_t;

struct board_s
{
    int cases[6][6];    // 1, 2 ou 3
    int pieces[6][6];   // 0 si case vide, 1 si joueur 1, 2 si joueur 2, 3 si oiseau
    pos_t *bird;        // Position de l'oiseau
    pos_t *daimyo_1;    // Position du daimyo du joueur 1
    pos_t *daimyo_2;    // Position du daimyo du joueur 2
};
typedef struct board_s board_t;

struct game_state_s
{
    int player;             // Indique quel joueur doit jouer
    int phase;              // Indique la phase de jeu (0 pion, 1 oiseau)
    bool player_blocked;    // Indique si le joueur est bloqué
    int round;              // Indique le tour actuel
    int last_case;          // Indique la valeur de la dernière case jouée
    int winner;             // Indique le gagnant

    int captured_pieces[3]; // Nombre de pièces capturées par chaque joueur
    board_t *board;          // Plateau de jeu
};
typedef struct game_state_s game_state_t;

struct input_s
{
    pos_t *selected_case_1;  // Case sélectionnée
    pos_t *selected_case_2;  // Case prédite
    list_t *possible_moves;  // Liste des cases possibles
};
typedef struct input_s input_t;

// Utilisé pour min-max.
struct l_path_s
{
    list_t *possibilities;
    pos_t *pos;
    struct l_path_s *next;
};
typedef struct l_path_s l_path_t;

list_t* free_list(list_t *list);
void print_list(list_t *list);