#include <SDL2/SDL_image.h>
  #include <SDL2/SDL_ttf.h>   

void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer) {
    char msg_formated[255];
    int l;

    if (!ok) {
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL) SDL_DestroyRenderer(renderer);
    if (window != NULL)   SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    if (!ok) {
        exit(EXIT_FAILURE);
    }
}

SDL_Texture* load_texture_from_image(char* file_image_name, SDL_Window* window, SDL_Renderer* renderer) {
    SDL_Surface* my_image = NULL;
    SDL_Texture* my_texture = NULL;

    my_image = IMG_Load(file_image_name);
    if (my_image == NULL) end_sdl(0, "Cannot load image", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image);
    SDL_FreeSurface(my_image);
    if (my_texture == NULL) end_sdl(0, "Cannot create texture from surface", window, renderer);

    return my_texture;
}

void play_with_texture_1(SDL_Texture* my_texture, SDL_Window* window, SDL_Renderer* renderer) {
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

    destination = window_dimensions;

    SDL_RenderCopy(renderer, my_texture, &source, &destination);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    SDL_RenderClear(renderer);
}

void play_with_texture_2(SDL_Texture* my_texture,
                  SDL_Window* window,
                  SDL_Renderer* renderer) {
       SDL_Rect 
         source = {0},                      // Rectangle définissant la zone de la texture à récupérer
         window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
         destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

       SDL_GetWindowSize(
       window, &window_dimensions.w,
       &window_dimensions.h);               // Récupération des dimensions de la fenêtre
       SDL_QueryTexture(my_texture, NULL, NULL,
            &source.w, &source.h);  // Récupération des dimensions de l'image

       float zoom = 1.5;                        // Facteur de zoom à appliquer    
       destination.w = source.w * zoom;         // La destination est un zoom de la source
       destination.h = source.h * zoom;         // La destination est un zoom de la source
       destination.x =
     (window_dimensions.w - destination.w) /2;     // La destination est au milieu de la largeur de la fenêtre
       destination.y =
       (window_dimensions.h - destination.h) / 2;  // La destination est au milieu de la hauteur de la fenêtre

       SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
              &source,
              &destination);            
       SDL_RenderPresent(renderer);             
       SDL_Delay(1000);                         

       SDL_RenderClear(renderer);               // Effacer la fenêtre
     }

void play_with_texture_3(SDL_Texture* my_texture,
               SDL_Window* window,
               SDL_Renderer* renderer) {
    SDL_Rect 
      source = {0},                             // Rectangle définissant la zone de la texture à récupérer
      window_dimensions = {0},                  // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
      destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer
                                
    SDL_GetWindowSize(                      
    window, &window_dimensions.w,               
    &window_dimensions.h);                      // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,         
                     &source.w,                 
             &source.h);                    // Récupération des dimensions de l'image
                                
    /* On décide de déplacer dans la fenêtre         cette image */
    float zoom = 0.25;                              // Facteur de zoom entre l'image source et l'image affichée
                                
    int nb_it = 200;                                // Nombre d'images de l'animation
    destination.w = source.w * zoom;                // On applique le zoom sur la largeur
    destination.h = source.h * zoom;                // On applique le zoom sur la hauteur
    destination.x =                     
    (window_dimensions.w - destination.w) / 2;  // On centre en largeur
    float h = window_dimensions.h - destination.h;  // hauteur du déplacement à effectuer

    for (int i = 0; i < nb_it; ++i) {
      destination.y =
      h * (1 - exp(-5.0 * i / nb_it) / 2 *
               (1 + cos(10.0 * i / nb_it * 2 *
                M_PI)));            // hauteur en fonction du numéro d'image

      SDL_RenderClear(renderer);                    // Effacer l'image précédente

      SDL_SetTextureAlphaMod(my_texture,(1.0-1.0*i/nb_it)*255);      // L'opacité va passer de 255 à 0 au fil de l'animation
      SDL_RenderCopy(renderer, my_texture, &source, &destination);   // Préparation de l'affichage
      SDL_RenderPresent(renderer);                  // Affichage de la nouvelle image
      SDL_Delay(30);                                // Pause en ms
    }                               
    SDL_RenderClear(renderer);                      // Effacer la fenêtre une fois le travail terminé
}

void play_with_texture_4(SDL_Texture* my_texture,
               SDL_Window* window,
               SDL_Renderer* renderer) {
     SDL_Rect 
           source = {0},                    // Rectangle définissant la zone totale de la planche
           window_dimensions = {0},         // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0},               // Rectangle définissant où la zone_source doit être déposée dans le renderer
           state = {0};                     // Rectangle de la vignette en cours dans la planche 

     SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
               &window_dimensions.w,
               &window_dimensions.h);
     SDL_QueryTexture(my_texture,           // Récupération des dimensions de l'image
              NULL, NULL,
              &source.w, &source.h);

     /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

     int nb_images = 8;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
     float zoom = 2;                        // zoom, car ces images sont un peu petites
     int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
         offset_y = source.h / 4;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée
       

     state.x = 0 ;                          // La première vignette est en début de ligne
     state.y = 3 * offset_y;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
     state.w = offset_x;                    // Largeur de la vignette
     state.h = offset_y;                    // Hauteur de la vignette

     destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
     destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran

     destination.y =                        // La course se fait en milieu d'écran (en vertical)
       (window_dimensions.h - destination.h) /2;

     int speed = 9;
     for (int x = 0; x < window_dimensions.w - destination.w; x += speed) {
       destination.x = x;                   // Position en x pour l'affichage du sprite
       state.x += offset_x;                 // On passe à la vignette suivante dans l'image
       state.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                        // celle de début de ligne

       SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
       SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
              &state,
              &destination);  
       SDL_RenderPresent(renderer);         // Affichage
       SDL_Delay(80);                       // Pause en ms
     }
     SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main
       }

void play_with_texture_5(SDL_Texture *bg_texture,
                 SDL_Texture *my_texture,
                 SDL_Window *window,
                 SDL_Renderer *renderer) {
    SDL_Rect
      source = {0},
      window_dimensions = {0},
      destination = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h); 
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h); 

    int nb_images = 40;
    int nb_images_animation = 1 * nb_images;
    float zoom = 2;
    int offset_x = source.w / 4,
    offset_y = source.h / 5;
    SDL_Rect state[40];

    int i = 0;                                   
    for (int y = 0; y < source.h ; y += offset_y) {
      for (int x = 0; x < source.w; x += offset_x) {
        state[i].x = x;
        state[i].y = y;
        state[i].w = offset_x;
        state[i].h = offset_y;
        ++i;
      }
    }

    state[15]  = state[14] = state[13]; 

    for(; i< nb_images ; ++i){                  
      state[i] = state[39-i];                   
    }

    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;
    destination.x = window_dimensions.w * 0.75;
    destination.y = window_dimensions.h * 0.7;

    i = 0;
    for (int cpt = 0; cpt < nb_images_animation ; ++cpt) {
      play_with_texture_1(bg_texture, window, renderer); 
      SDL_RenderCopy(renderer, my_texture, &state[i], &destination);
      i = (i + 1) % nb_images;
      SDL_RenderPresent(renderer);
      SDL_Delay(100);
    }
    SDL_RenderClear(renderer);
}

int main() {
    SDL_Texture* my_texture = NULL;
    SDL_Texture* bg_texture = NULL;

    // Initialize SDL, create window and renderer here...
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Window",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480, 0);
    if (!window) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load textures here...
    my_texture = load_texture_from_image("my_image.png", window, renderer);
    bg_texture = load_texture_from_image("bg_image.png", window, renderer);

    if (!my_texture || !bg_texture) {
        end_sdl(0, "Failed to load textures", window, renderer);
        return 1;
    }

    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            // Handle other events here...
        }

        // Call your functions here...
        play_with_texture_1(my_texture, window, renderer);
        play_with_texture_2(my_texture, window, renderer);
        play_with_texture_3(my_texture, window, renderer);
        play_with_texture_4(my_texture, window, renderer);
        play_with_texture_5(bg_texture, my_texture, window, renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000);  // Delay for 1 second
    }

    // Clean up and quit SDL here...
    SDL_DestroyTexture(my_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}