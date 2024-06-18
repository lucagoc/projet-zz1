#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>


void end_sdl(char ok, //fin normale : ok = 0; anormale ok = 1
        char const *msg, //message à afficher
        SDL_Window* window, //fenêtre à fermé
        SDL_Renderer* renderer){ //renderer à fermer
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
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    if (!ok)
    {
        exit(EXIT_FAILURE);
    }
        }


SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture
    my_image = IMG_Load(file_image_name);   // Chargement de l'image

    if (my_image == NULL) {
        
        end_sdl(0, "Chargement de l'image impossible", window, renderer);
    }

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); //Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);
    
    if (my_image == NULL)
    {
        end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);
    }
    
    return my_texture;
}



void play_with_texture_1 (SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect 
        source = {0},                         // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window,
        &window_dimensions.w,
        &window_dimensions.h
    );

    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);
    
    destination = window_dimensions;

    SDL_RenderCopy(renderer, my_texture,
                &source,
                &destination);
    
    SDL_RenderPresent(renderer);
    SDL_Delay(1500);

    SDL_RenderClear(renderer);

}

void play_with_texture_2 (SDL_Texture* my_texture,
                    SDL_Window* window,
                    SDL_Renderer* renderer){
    
    SDL_Rect
        source = {0},                       // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},            // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                  // Rectangle définissant où la zone_source doit être déposée dans le renderer


    SDL_GetWindowSize(
        window,
        &window_dimensions.w,
        &window_dimensions.h
    );

    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

    float zoom = 1.5;

    destination.w = source.w * zoom;                                                    //La destination est un zoom de la source
    destination.h = source.h * zoom;                                                    //La destination est un zoom de la source
    destination.x = (window_dimensions.w - destination.w) / 2;                          //La destination est au milieu de la largeur de la fenêtre
    destination.y = (window_dimensions.h - destination.h) / 2;                          //La destination est au milieu de la hauteur de la fenêtre

    SDL_RenderCopy(renderer, my_texture,
                    &source,
                    &destination);                                                      //Préparation de l'affichage

    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    SDL_RenderClear(renderer);            
}

void play_with_texture_3 (SDL_Texture* my_texture,
                    SDL_Window* window,
                    SDL_Renderer* renderer){

    SDL_Rect
        source = {0},
        window_dimensions = {0},
        destination = {0};

    SDL_GetWindowSize(
        window,
        &window_dimensions.w,
        &window_dimensions.h
    );

    SDL_QueryTexture(my_texture, NULL, NULL, 
                    &source.w,
                    &source.h);
    
    float zoom = 0.25;

    int nb_it = 200;                                                            //nombre d'images de l'animation
    destination.w = source.w * zoom;                                            //on applique le zoom sur la largeur
    destination.h = source.h * zoom;                                            //on applique sur la hauteur
    destination.x = (window_dimensions.w - destination.w) / 2;                  //on centre en largeur
    
    float h = window_dimensions.h - destination.h;                              //hauteur du déplacement à effectuer

    for (int i = 0; i < nb_it ; i++)
    {
        destination.y =
                h * (1 - exp(-5.0 * i / nb_it) / 2 *
               (1 + cos(10.0 * i / nb_it * 2 *
                M_PI)));            // hauteur en fonction du numéro d'image
    

        SDL_RenderClear(renderer);

        SDL_SetTextureAlphaMod(my_texture, (1.0 - 1.0 * i/nb_it) * 255);
        SDL_RenderCopy(renderer, my_texture, &source, &destination);
        SDL_RenderPresent(renderer);
        SDL_Delay(30);

    }

    SDL_RenderClear(renderer);

                    }



//Animé un sprite

void play_with_texture_4(SDL_Texture* my_texture,
                SDL_Window* window,
                SDL_Renderer* renderer){

    SDL_Rect
        source = {0},
        window_dimensions = {0},
        destination = {0},
        state = {0};

    SDL_GetWindowSize(window,
                    &window_dimensions.w,
                    &window_dimensions.h);

    SDL_QueryTexture(my_texture, NULL , NULL , &source.w , &source.h);

    int nb_images = 8;
    float zoom = 2;

    int offset_x = source.w / nb_images, 
        offset_y = source.h / nb_images;

    state.x = 0;
    state.y = 3 * offset_y;
    state.w = offset_x;
    state.h = offset_y;

    destination.y = (window_dimensions.h - destination.h) / 2;

    int speed = 9;

    for (int x = 0 ; x < window_dimensions.w - destination.w ; x +=speed)
    {
        destination.x = x;                                             //position en x pour l'affichage du sprite
        state.x += offset_x;
        state.x %= source.w;


        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, my_texture, &state, &destination);

        SDL_RenderPresent(renderer);
        SDL_Delay(80);
        
    }
    SDL_RenderClear(renderer);

        }

void play_with_texture_5(SDL_Texture* bg_texture,
                    SDL_Texture* my_texture,
                    SDL_Window* window,
                    SDL_Renderer* renderer){

    SDL_Rect
        source = {0},
        window_dimensions = {0},
        destination = {0};


    SDL_GetWindowSize(window,
                &window_dimensions.w,
                &window_dimensions.h);
    
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

    int nb_images = 40;
    int nb_images_animation = 1* nb_images;
    float zoom = 10;
    int offset_x = source.w / 4,
        offset_y = source.h /5;

    SDL_Rect state[40];                             //Tableau qui stocke les vignettes dans le bon ordre d'animation

    /* construction des différents rectangles autour de chacune des vignettes de la planche */
    int i = 0;                                   
    for (int y = 0; y < source.h ; y += offset_y) {
        for (int x = 0; x < source.w; x += offset_x) {
            state[i].x = x;
            state[i].y = y;
            state[i].w = offset_x;
            state[i].h = offset_y;
            i++;
        }
    }
    
    state[15] = state[14]
            = state[13];

    for (; i < nb_images ; i++)
    {
        state[i] = state[39 - i];
    }

    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;
    destination.x = window_dimensions.w * 0.75;
    destination.y = window_dimensions.h * 0.7;

    i = 0;

    for (int cpt = 0; cpt < nb_images_animation ; cpt++)
    {
        play_with_texture_1(bg_texture, window, renderer);
        SDL_RenderCopy(renderer, my_texture, &state[i], &destination);

        i = (i + 1) % nb_images;
        
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        SDL_RenderClear(renderer);
    }

    


                    }



int main (){

    SDL_Texture* my_texture = NULL;
    SDL_Texture* bg_texture = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());

        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Window",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          1000, 1000, 0);
    
    if (window == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());

        SDL_Quit();

        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());

        SDL_DestroyWindow(window);

        SDL_Quit();

        return 1;
    }


    //Prendre les textures

    my_texture = load_texture_from_image("bat-fly-000.png", window, renderer);
    bg_texture = load_texture_from_image("background.png", window,renderer);

    if (!my_texture || !bg_texture )
    {
        end_sdl(1 , "Erreur d'initialisation des textures", window, renderer);

        return 1;
    }

    SDL_Event event;

    int quit = 0;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {

                quit = 1;
            }
        }

        play_with_texture_5(bg_texture,my_texture, window, renderer);
        
        
    }

    SDL_DestroyTexture(my_texture);
    SDL_DestroyTexture(bg_texture);
    

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);


    return 0;
}