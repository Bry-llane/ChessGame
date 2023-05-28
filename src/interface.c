#include "interface.h"

#define TAILLE_CASE 70
#define TAILLE_SEPARATION 6
#define TAILLE_T (TAILLE_CASE+TAILLE_SEPARATION)

///=========================================================
//Creation de la fenetre
SDL_Window* Create_window(const char* title, chessboard b)
{
    SDL_Window* window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              (8*TAILLE_T)+TAILLE_SEPARATION,
                              (8*TAILLE_T)+TAILLE_SEPARATION,
                              SDL_WINDOW_SHOWN);

    if (!window)
    {
        printf("Erreur lors de la création de la fenêtre SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return window;
}

///=========================================================
//Creation du rendu
SDL_Renderer* Create_renderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        fprintf(stderr, "Erreur : impossible de créer le renderer SDL\n");
        return NULL;
    }
    return renderer;
}

///=========================================================
//Destruction de la fenetre et du rendu
void Destroy_window_and_renderer(SDL_Window* window, SDL_Renderer* renderer)
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
}

///=========================================================
//Creation d'une texture a partir d'une image
SDL_Texture* LoadTexture(SDL_Renderer* renderer, char* path)
{
    SDL_Surface* surface = SDL_LoadBMP(path);
    SDL_Texture* texture = NULL;

    if (surface == NULL) {
        printf("Erreur chargement image\n");
    }
    else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (texture == NULL) {
            printf("Erreur de création de la texture\n");
        }
        SDL_FreeSurface(surface);
    }

    return texture;
}

///=========================================================
//Verifie si le nombre entrer est un entier
int IsInt()
{
    int num;
    char c;

    while(true){
        if(scanf("%d", &num)!= 1){
            printf("Veuillez rentrer un chiffre : ");
            while((c = getchar()) != '\n' && c != EOF);
        } else {
           break;
        }
    }

    return num;
}

///=========================================================
//Verifie l'existence d'un fichier
bool ExisteFile(char* file)
{
    FILE *fichier = NULL;
    fichier = fopen(file, "r");

    if (fichier == NULL) {
        return false;
    } else {
        fclose(fichier);
        return true;
    }
}

///=========================================================
//Renommer un fichier
void Rename_save()
{
    printf("\n");

    if(ExisteFile("./save/save1.txt")){
        printf("1 : Sauvegarde 1\n");
    } else {
        printf("1 : Empty \n");
    }

    if(ExisteFile("./save/save2.txt")){
        printf("2 : Sauvegarde 2\n");
    } else {
        printf("2 : Empty \n");
    }

    if(ExisteFile("./save/save3.txt")){
        printf("3 : Sauvegarde 3\n");
    } else {
        printf("3 : Empty \n\n");
    }

    int choix;
    bool boucle = true;

    while (boucle){
        printf("Attente du numero choisi : ");
        choix = IsInt();

        switch(choix){
            case 1:
                if(ExisteFile("./save/save1.txt")){
                    remove("./save/save1.txt");
                }
                rename("./src/save.txt", "./save/save1.txt");
                boucle = false;
                break;

            case 2:
                if(ExisteFile("./save/save2.txt")){
                    remove("./save/save2.txt");
                }
                rename("./src/save.txt", "./save/save2.txt");
                boucle = false;
                break;

            case 3:
                if(ExisteFile("./save/save3.txt")){
                    remove("./save/save3.txt");
                }
                rename("./src/save.txt", "./save/save3.txt");
                boucle = false;
                break;

            case 4:
                boucle = false;
                break;

            default:
                break;
        }
    }
}


///=========================================================
//Dessiner le plateau de jeu
void Draw_morpion(SDL_Renderer* renderer, chessboard b)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_Rect rectangle;
    for (int x = 0; x <= (b->colonne*TAILLE_T)+TAILLE_SEPARATION; x+=TAILLE_T){
        rectangle.x = x;
        rectangle.y = 0;
        rectangle.w = TAILLE_SEPARATION;
        rectangle.h = (b->ligne*TAILLE_T)+TAILLE_SEPARATION;

        SDL_RenderFillRect(renderer, &rectangle);
    }

    for (int y = 0; y <= (b->ligne*TAILLE_T)+TAILLE_SEPARATION; y+=TAILLE_T){
        rectangle.x = 0;
        rectangle.y = y;
        rectangle.w = (b->colonne*TAILLE_T)+TAILLE_SEPARATION;
        rectangle.h = TAILLE_SEPARATION;

        SDL_RenderFillRect(renderer, &rectangle);
    }
}

///=========================================================
//Lancer une nouvelle partie
void New_game()
{
    chessboard b = create_board();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    window = Create_window("Morpion", b);
    renderer = Create_renderer(window);
    Draw_morpion(renderer, b);

    //Draw_morpion(renderer, b);

    SDL_RenderPresent(renderer);
    //Manche(renderer, b, 1, b->colonne * b->ligne);
sleep(5);
    Destroy_window_and_renderer(window, renderer);
    SDL_Quit();
}
