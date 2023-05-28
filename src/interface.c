#include "interface.h"

///=========================================================
//Creation de la fenetre
SDL_Window* create_window(const char* title, chessboard b)
{
    SDL_Window* window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window)
    {
        printf("Erreur lors de la création de la fenêtre SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    // Empêcher la redimension de la fenêtre
    SDL_SetWindowResizable(window, SDL_FALSE);

    return window;
}

///=========================================================
//Creation du rendu
SDL_Renderer* create_renderer(SDL_Window* window)
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
void destroy_window_and_renderer(SDL_Window* window, SDL_Renderer* renderer)
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
SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path)
{
    SDL_Surface* surface = SDL_LoadBMP(path);
    SDL_Texture* texture = NULL;

    if (surface == NULL) {
        printf("Erreur chargement image %s\n", path);
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
int isInt()
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
bool existeFile(char* file)
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
void rename_save()
{
    printf("\n");

    if(existeFile("./save/save1.txt")){
        printf("1 : Sauvegarde 1\n");
    } else {
        printf("1 : Empty \n");
    }

    if(existeFile("./save/save2.txt")){
        printf("2 : Sauvegarde 2\n");
    } else {
        printf("2 : Empty \n");
    }

    if(existeFile("./save/save3.txt")){
        printf("3 : Sauvegarde 3\n");
    } else {
        printf("3 : Empty \n\n");
    }

    int choix;
    bool boucle = true;

    while (boucle){
        printf("Attente du numero choisi : ");
        choix = isInt();

        switch(choix){
            case 1:
                if(existeFile("./save/save1.txt")){
                    remove("./save/save1.txt");
                }
                rename("./src/save.txt", "./save/save1.txt");
                boucle = false;
                break;

            case 2:
                if(existeFile("./save/save2.txt")){
                    remove("./save/save2.txt");
                }
                rename("./src/save.txt", "./save/save2.txt");
                boucle = false;
                break;

            case 3:
                if(existeFile("./save/save3.txt")){
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

// Fonction pour créer un bouton
button createbutton(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    button but;
    SDL_Color COLOR_WHITE = {255, 255, 255, 255};

    // Création de la surface de texte
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, COLOR_WHITE);
    if (surface == NULL) {
        printf("Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        exit(1);
    }

    // Création de la texture à partir de la surface
    but.texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (but.texture == NULL) {
        printf("Erreur lors de la création de la texture du bouton : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        exit(1);
    }

    // Libération de la surface
    SDL_FreeSurface(surface);

    // Définition de la position et de la taille du bouton
    but.rect.x = x;
    but.rect.y = y;
    but.rect.w = 300;
    but.rect.h = 100;
    //SDL_QueryTexture(but.texture, NULL, NULL, &but.rect.w, &but.rect.h);

    return but;
}

button createtitle(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    button but;
    SDL_Color COLOR_WHITE = {0, 0, 0, 255};

    // Création de la surface de texte
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, COLOR_WHITE);
    if (surface == NULL) {
        printf("Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        exit(1);
    }

    // Création de la texture à partir de la surface
    but.texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (but.texture == NULL) {
        printf("Erreur lors de la création de la texture du bouton : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        exit(1);
    }

    // Libération de la surface
    SDL_FreeSurface(surface);

    // Définition de la position et de la taille du bouton
    but.rect.x = x;
    but.rect.y = y;
    but.rect.w = 300;
    but.rect.h = 100;
    //SDL_QueryTexture(but.texture, NULL, NULL, &but.rect.w, &but.rect.h);

    return but;
}

// Fonction pour dessiner un bouton
void drawbutton(SDL_Renderer* renderer, button but) {
    SDL_Color marron = {150, 84, 26, 255};
    // Dessiner le rectangle du bouton
    SDL_SetRenderDrawColor(renderer, marron.r, marron.g, marron.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &but.rect);

    // Dessiner le texte du bouton
    SDL_RenderCopy(renderer, but.texture, NULL, &but.rect);
}

// Fonction pour dessiner un bouton
void drawtitle(SDL_Renderer* renderer, button but) {
    SDL_Color belge = {246, 195, 145, 255};
    // Dessiner le rectangle du bouton
    SDL_SetRenderDrawColor(renderer, belge.r, belge.g, belge.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &but.rect);

    // Dessiner le texte du bouton
    SDL_RenderCopy(renderer, but.texture, NULL, &but.rect);
}


///=========================================================
//Dessiner le plateau de jeu
void draw_board(SDL_Renderer* renderer, chessboard b)
{
    SDL_SetRenderDrawColor(renderer, 246, 195, 145, 255);  //belge
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //noir
    
    SDL_Rect rectangle;
    for (int x = 0; x <= (8*TAILLE_T)+TAILLE_SEPARATION; x+=TAILLE_T){
        rectangle.x = x+ESPACE_BOARD;
        rectangle.y = ESPACE_BOARD;
        rectangle.w = TAILLE_SEPARATION;
        rectangle.h = (8*TAILLE_T)+TAILLE_SEPARATION;

        SDL_RenderFillRect(renderer, &rectangle);
    }

    for (int y = 0; y <= (8*TAILLE_T)+TAILLE_SEPARATION; y+=TAILLE_T){
        rectangle.x = ESPACE_BOARD;
        rectangle.y = y+ESPACE_BOARD;
        rectangle.w = (8*TAILLE_T)+TAILLE_SEPARATION;
        rectangle.h = TAILLE_SEPARATION;

        SDL_RenderFillRect(renderer, &rectangle);
    }
    
    rectangle.x = BARRE_SEPARATION;
    rectangle.y = 20;
    rectangle.w = TAILLE_SEPARATION;
    rectangle.h = SCREEN_HEIGHT-40;
    
    SDL_RenderFillRect(renderer, &rectangle);

    //les case du plateau
    SDL_Texture* gris = loadTexture(renderer, "./image/case_grise.bmp");
    SDL_Texture* blanc = loadTexture(renderer, "./image/case_blanche.bmp");
    SDL_Texture* logo = loadTexture(renderer, "./image/logo.bmp");

    SDL_Rect rect_gris, rect_blanc, rect_logo;

    SDL_QueryTexture(gris, NULL, NULL, &rect_gris.w, &rect_gris.h);
    SDL_QueryTexture(blanc, NULL, NULL, &rect_blanc.w, &rect_blanc.h);
    SDL_QueryTexture(logo, NULL, NULL, &rect_logo.w, &rect_logo.h);

    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
       	    if ((x + y) % 2 != 0) {
       	    	rect_gris.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
                rect_gris.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
                SDL_RenderCopy(renderer, gris, NULL, &rect_gris);
            } else {
                rect_blanc.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
                rect_blanc.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
                SDL_RenderCopy(renderer, blanc, NULL, &rect_blanc);
            }
        }
    }
    
    SDL_Texture* tour_noir = loadTexture(renderer, "./image/tour_noir.bmp");
    SDL_Texture* cavalier_noir = loadTexture(renderer, "./image/cavalier_noir.bmp");
    SDL_Texture* fou_noir = loadTexture(renderer, "./image/fou_noir.bmp");
    SDL_Texture* reine_noir = loadTexture(renderer, "./image/reine_noir.bmp");
    SDL_Texture* roi_noir = loadTexture(renderer, "./image/roi_noir.bmp");
    SDL_Texture* pion_noir = loadTexture(renderer, "./image/pion_noir.bmp");
    SDL_Texture* tour_blanc = loadTexture(renderer, "./image/tour_blanc.bmp");
    SDL_Texture* cavalier_blanc = loadTexture(renderer, "./image/cavalier_blanc.bmp");
    SDL_Texture* fou_blanc = loadTexture(renderer, "./image/fou_blanc.bmp");
    SDL_Texture* reine_blanc = loadTexture(renderer, "./image/reine_blanc.bmp");
    SDL_Texture* roi_blanc = loadTexture(renderer, "./image/roi_blanc.bmp");
    SDL_Texture* pion_blanc = loadTexture(renderer, "./image/pion_blanc.bmp");
      
    SDL_Rect rect_tour_noir, rect_cavalier_noir, rect_fou_noir, rect_reine_noir, rect_roi_noir,
    	rect_pion_noir, rect_tour_blanc, rect_cavalier_blanc, rect_fou_blanc, rect_reine_blanc,
    	rect_roi_blanc, rect_pion_blanc;
    
    SDL_QueryTexture(tour_noir, NULL, NULL, &rect_tour_noir.w, &rect_tour_noir.h);
    SDL_QueryTexture(cavalier_noir, NULL, NULL, &rect_cavalier_noir.w, &rect_cavalier_noir.h);
    SDL_QueryTexture(fou_noir, NULL, NULL, &rect_fou_noir.w, &rect_fou_noir.h);
    SDL_QueryTexture(reine_noir, NULL, NULL, &rect_reine_noir.w, &rect_reine_noir.h);
    SDL_QueryTexture(roi_noir, NULL, NULL, &rect_roi_noir.w, &rect_roi_noir.h);
    SDL_QueryTexture(pion_noir, NULL, NULL, &rect_pion_noir.w, &rect_pion_noir.h);
    SDL_QueryTexture(tour_blanc, NULL, NULL, &rect_tour_blanc.w, &rect_tour_blanc.h);
    SDL_QueryTexture(cavalier_blanc, NULL, NULL, &rect_cavalier_blanc.w, &rect_cavalier_blanc.h);
    SDL_QueryTexture(fou_blanc, NULL, NULL, &rect_fou_blanc.w, &rect_fou_blanc.h);
    SDL_QueryTexture(reine_blanc, NULL, NULL, &rect_reine_blanc.w, &rect_reine_blanc.h);
    SDL_QueryTexture(roi_blanc, NULL, NULL, &rect_roi_blanc.w, &rect_roi_blanc.h);
    SDL_QueryTexture(pion_blanc, NULL, NULL, &rect_pion_blanc.w, &rect_pion_blanc.h);
    
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
        
  	    if(b->board[y][x] != NULL){
		if(b->board[y][x]->typePiece == PION){
		    if(b->board[y][x]->couleur == NOIR){
			rect_pion_noir.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_pion_noir.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, pion_noir, NULL, &rect_pion_noir);
		    } else {
		    	rect_pion_blanc.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_pion_blanc.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, pion_blanc, NULL, &rect_pion_blanc);
		    }
		} else if(b->board[y][x]->typePiece == TOUR){
		    if(b->board[y][x]->couleur == NOIR){
			rect_tour_noir.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_tour_noir.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, tour_noir, NULL, &rect_tour_noir);
		    } else {
		    	rect_tour_blanc.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_tour_blanc.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, tour_blanc, NULL, &rect_tour_blanc);
		    }
		} else if(b->board[y][x]->typePiece == CAVALIER){
		    if(b->board[y][x]->couleur == NOIR){
			rect_cavalier_noir.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_cavalier_noir.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, cavalier_noir, NULL, &rect_cavalier_noir);
		    } else {
		    	rect_cavalier_blanc.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_cavalier_blanc.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, cavalier_blanc, NULL, &rect_cavalier_blanc);
		    }
		} else if(b->board[y][x]->typePiece == FOU){
		    if(b->board[y][x]->couleur == NOIR){
			rect_fou_noir.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_fou_noir.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, fou_noir, NULL, &rect_fou_noir);
		    } else {
		    	rect_fou_blanc.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_fou_blanc.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, fou_blanc, NULL, &rect_fou_blanc);
		    }
		} else if(b->board[y][x]->typePiece == REINE){
		    if(b->board[y][x]->couleur == NOIR){
			rect_reine_noir.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_reine_noir.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, reine_noir, NULL, &rect_reine_noir);
		    } else {
		    	rect_reine_blanc.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_reine_blanc.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, reine_blanc, NULL, &rect_reine_blanc);
		    }
		} else if(b->board[y][x]->typePiece == ROI){
		    if(b->board[y][x]->couleur == NOIR){
			rect_roi_noir.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_roi_noir.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, roi_noir, NULL, &rect_roi_noir);
		    } else {
		    	rect_roi_blanc.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_roi_blanc.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, roi_blanc, NULL, &rect_roi_blanc);
		    }
		} 
	    }
        }
    }
    
    rect_logo.x = BARRE_SEPARATION + 60;
    rect_logo.y = 20;
    SDL_RenderCopy(renderer, logo, NULL, &rect_logo);
    
    SDL_DestroyTexture(gris);
    SDL_DestroyTexture(blanc);
    SDL_DestroyTexture(logo);
    SDL_DestroyTexture(tour_noir);
    SDL_DestroyTexture(cavalier_noir);
    SDL_DestroyTexture(fou_noir);
    SDL_DestroyTexture(reine_noir);
    SDL_DestroyTexture(roi_noir);
    SDL_DestroyTexture(pion_noir);
    SDL_DestroyTexture(tour_blanc);
    SDL_DestroyTexture(cavalier_blanc);
    SDL_DestroyTexture(fou_blanc);
    SDL_DestroyTexture(reine_blanc);
    SDL_DestroyTexture(roi_blanc);
    SDL_DestroyTexture(pion_blanc);
}


void actualise_board(SDL_Renderer* renderer, chessboard b)
{
    SDL_Rect rectangle;
    SDL_SetRenderDrawColor(renderer, 246, 195, 145, 255);  //belge

    rectangle.x = ESPACE_BOARD;
    rectangle.y = ESPACE_BOARD;
    rectangle.w = 614;
    rectangle.h = 614;
    
    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //noir
    
    for (int x = 0; x <= (8*TAILLE_T)+TAILLE_SEPARATION; x+=TAILLE_T){
        rectangle.x = x+ESPACE_BOARD;
        rectangle.y = ESPACE_BOARD;
        rectangle.w = TAILLE_SEPARATION;
        rectangle.h = (8*TAILLE_T)+TAILLE_SEPARATION;

        SDL_RenderFillRect(renderer, &rectangle);
    }

    for (int y = 0; y <= (8*TAILLE_T)+TAILLE_SEPARATION; y+=TAILLE_T){
        rectangle.x = ESPACE_BOARD;
        rectangle.y = y+ESPACE_BOARD;
        rectangle.w = (8*TAILLE_T)+TAILLE_SEPARATION;
        rectangle.h = TAILLE_SEPARATION;

        SDL_RenderFillRect(renderer, &rectangle);
    }
    
    rectangle.x = BARRE_SEPARATION;
    rectangle.y = 20;
    rectangle.w = TAILLE_SEPARATION;
    rectangle.h = SCREEN_HEIGHT-40;
    
    SDL_RenderFillRect(renderer, &rectangle);

    //les case du plateau
    SDL_Texture* gris = loadTexture(renderer, "./image/case_grise.bmp");
    SDL_Texture* blanc = loadTexture(renderer, "./image/case_blanche.bmp");

    SDL_Rect rect_gris, rect_blanc;

    SDL_QueryTexture(gris, NULL, NULL, &rect_gris.w, &rect_gris.h);
    SDL_QueryTexture(blanc, NULL, NULL, &rect_blanc.w, &rect_blanc.h);

    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
       	    if ((x + y) % 2 != 0) {
       	    	rect_gris.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
                rect_gris.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
                SDL_RenderCopy(renderer, gris, NULL, &rect_gris);
            } else {
                rect_blanc.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
                rect_blanc.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
                SDL_RenderCopy(renderer, blanc, NULL, &rect_blanc);
            }
        }
    }
    
    SDL_Texture* tour_noir = loadTexture(renderer, "./image/tour_noir.bmp");
    SDL_Texture* cavalier_noir = loadTexture(renderer, "./image/cavalier_noir.bmp");
    SDL_Texture* fou_noir = loadTexture(renderer, "./image/fou_noir.bmp");
    SDL_Texture* reine_noir = loadTexture(renderer, "./image/reine_noir.bmp");
    SDL_Texture* roi_noir = loadTexture(renderer, "./image/roi_noir.bmp");
    SDL_Texture* pion_noir = loadTexture(renderer, "./image/pion_noir.bmp");
    SDL_Texture* tour_blanc = loadTexture(renderer, "./image/tour_blanc.bmp");
    SDL_Texture* cavalier_blanc = loadTexture(renderer, "./image/cavalier_blanc.bmp");
    SDL_Texture* fou_blanc = loadTexture(renderer, "./image/fou_blanc.bmp");
    SDL_Texture* reine_blanc = loadTexture(renderer, "./image/reine_blanc.bmp");
    SDL_Texture* roi_blanc = loadTexture(renderer, "./image/roi_blanc.bmp");
    SDL_Texture* pion_blanc = loadTexture(renderer, "./image/pion_blanc.bmp");
      
    SDL_Rect rect_tour_noir, rect_cavalier_noir, rect_fou_noir, rect_reine_noir, rect_roi_noir,
    	rect_pion_noir, rect_tour_blanc, rect_cavalier_blanc, rect_fou_blanc, rect_reine_blanc,
    	rect_roi_blanc, rect_pion_blanc;
    
    SDL_QueryTexture(tour_noir, NULL, NULL, &rect_tour_noir.w, &rect_tour_noir.h);
    SDL_QueryTexture(cavalier_noir, NULL, NULL, &rect_cavalier_noir.w, &rect_cavalier_noir.h);
    SDL_QueryTexture(fou_noir, NULL, NULL, &rect_fou_noir.w, &rect_fou_noir.h);
    SDL_QueryTexture(reine_noir, NULL, NULL, &rect_reine_noir.w, &rect_reine_noir.h);
    SDL_QueryTexture(roi_noir, NULL, NULL, &rect_roi_noir.w, &rect_roi_noir.h);
    SDL_QueryTexture(pion_noir, NULL, NULL, &rect_pion_noir.w, &rect_pion_noir.h);
    SDL_QueryTexture(tour_blanc, NULL, NULL, &rect_tour_blanc.w, &rect_tour_blanc.h);
    SDL_QueryTexture(cavalier_blanc, NULL, NULL, &rect_cavalier_blanc.w, &rect_cavalier_blanc.h);
    SDL_QueryTexture(fou_blanc, NULL, NULL, &rect_fou_blanc.w, &rect_fou_blanc.h);
    SDL_QueryTexture(reine_blanc, NULL, NULL, &rect_reine_blanc.w, &rect_reine_blanc.h);
    SDL_QueryTexture(roi_blanc, NULL, NULL, &rect_roi_blanc.w, &rect_roi_blanc.h);
    SDL_QueryTexture(pion_blanc, NULL, NULL, &rect_pion_blanc.w, &rect_pion_blanc.h);
    
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
        
  	    if(b->board[y][x] != NULL){
		if(b->board[y][x]->typePiece == PION){
		    if(b->board[y][x]->couleur == NOIR){
			rect_pion_noir.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_pion_noir.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, pion_noir, NULL, &rect_pion_noir);
		    } else {
		    	rect_pion_blanc.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_pion_blanc.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, pion_blanc, NULL, &rect_pion_blanc);
		    }
		} else if(b->board[y][x]->typePiece == TOUR){
		    if(b->board[y][x]->couleur == NOIR){
			rect_tour_noir.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_tour_noir.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, tour_noir, NULL, &rect_tour_noir);
		    } else {
		    	rect_tour_blanc.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_tour_blanc.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, tour_blanc, NULL, &rect_tour_blanc);
		    }
		} else if(b->board[y][x]->typePiece == CAVALIER){
		    if(b->board[y][x]->couleur == NOIR){
			rect_cavalier_noir.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_cavalier_noir.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, cavalier_noir, NULL, &rect_cavalier_noir);
		    } else {
		    	rect_cavalier_blanc.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_cavalier_blanc.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, cavalier_blanc, NULL, &rect_cavalier_blanc);
		    }
		} else if(b->board[y][x]->typePiece == FOU){
		    if(b->board[y][x]->couleur == NOIR){
			rect_fou_noir.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_fou_noir.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, fou_noir, NULL, &rect_fou_noir);
		    } else {
		    	rect_fou_blanc.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_fou_blanc.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, fou_blanc, NULL, &rect_fou_blanc);
		    }
		} else if(b->board[y][x]->typePiece == REINE){
		    if(b->board[y][x]->couleur == NOIR){
			rect_reine_noir.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_reine_noir.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, reine_noir, NULL, &rect_reine_noir);
		    } else {
		    	rect_reine_blanc.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_reine_blanc.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, reine_blanc, NULL, &rect_reine_blanc);
		    }
		} else if(b->board[y][x]->typePiece == ROI){
		    if(b->board[y][x]->couleur == NOIR){
			rect_roi_noir.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_roi_noir.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, roi_noir, NULL, &rect_roi_noir);
		    } else {
		    	rect_roi_blanc.x = (x*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			rect_roi_blanc.y = (y*TAILLE_T) + TAILLE_SEPARATION + ESPACE_BOARD;
			SDL_RenderCopy(renderer, roi_blanc, NULL, &rect_roi_blanc);
		    }
		} 
	    }
        }
    }
    
    SDL_DestroyTexture(gris);
    SDL_DestroyTexture(blanc);
    SDL_DestroyTexture(tour_noir);
    SDL_DestroyTexture(cavalier_noir);
    SDL_DestroyTexture(fou_noir);
    SDL_DestroyTexture(reine_noir);
    SDL_DestroyTexture(roi_noir);
    SDL_DestroyTexture(pion_noir);
    SDL_DestroyTexture(tour_blanc);
    SDL_DestroyTexture(cavalier_blanc);
    SDL_DestroyTexture(fou_blanc);
    SDL_DestroyTexture(reine_blanc);
    SDL_DestroyTexture(roi_blanc);
    SDL_DestroyTexture(pion_blanc);
}


void render_menu(SDL_Renderer* renderer, chessboard b)
{
    TTF_Font* font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    
    SDL_Rect rectangle;
    SDL_SetRenderDrawColor(renderer, 246, 195, 145, 255);  //belge

    rectangle.x = BARRE_SEPARATION + 60;;
    rectangle.y = 2 * ESPACE_BOARD;
    rectangle.w = 300;
    rectangle.h = 602;
    
    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //noir
    char* t;
    char* b1;
    char* b2;
    char* b3;
    char* b4;
    
    if(b->menu == 1){
    	t = " Menu ";
    	b1 = " New Party ";
    	b2 = " Load Save ";
    	b3 = " Delete Save ";
    	b4 = " Quit ";
    }
    
    if(b->menu == 2){
    	t = " Nombre de Joueur ";
    	b1 = " 0 ";
    	b2 = " 1 ";
    	b3 = " 2 ";
    	b4 = " Quit ";
    }

    if(b->menu == 3){
    	if(b->nb_joueur == 1){
    	    t = " Position du Joueur ";
    	    b1 = " 1 ";
    	    b2 = " 2 ";
    	    b3 = " Quit ";
    	    b4 = "  ";
    	}
    }
    
    if(b->menu == 4){
    	t = " Partie en cours ";
    	b1 = " Save ";
    	b2 = " Quit ";
    	b3 = "  ";
    	b4 = "  ";
    }
    
    if(b->menu == 5){
    	t = " Load Save ";
    
    	if(existeFile("./save/save1.txt")){
	    b1 = " Save 1 ";
     	} else {
	    b1 = " Empty ";
    	}

        if(existeFile("./save/save2.txt")){
	    b2 = " Save 2 ";
        } else {
	    b2 = " Empty ";
        }

        if(existeFile("./save/save3.txt")){
	   b3 = " Save 3 ";
        } else {
	   b3 = " Empty ";
        }
    	
    	b4 = " Quit ";
    }
    
    if(b->menu == 6){
    	t = " Delete Save ";
    
    	if(existeFile("./save/save1.txt")){
	    b1 = " Save 1 ";
     	} else {
	    b1 = " Empty ";
    	}

        if(existeFile("./save/save2.txt")){
	    b2 = " Save 2 ";
        } else {
	    b2 = " Empty ";
        }

        if(existeFile("./save/save3.txt")){
	   b3 = " Save 3 ";
        } else {
	   b3 = " Empty ";
        }
    	
    	b4 = " Quit ";
    }
    
    if(b->menu == 7){
    	t = " Promotion ";
    	b1 = " TOUR ";
    	b2 = " CAVALIER ";
    	b3 = " FOU ";
    	b4 = " REINE ";
    }
    
    
    // Les boutons
    int y = 2 * ESPACE_BOARD;
    
    
    button title = createtitle(renderer, font, t, BARRE_SEPARATION + 60, y);
    y+=125;
    button button1 = createbutton(renderer, font, b1, BARRE_SEPARATION + 60, y);
    y+=125;
    button button2 = createbutton(renderer, font, b2, BARRE_SEPARATION + 60, y);
    y+=125;
    button button3;
    if(b->menu == 4){
    	button3 = createtitle(renderer, font, b3, BARRE_SEPARATION + 60, y);
    } else {
        button3 = createbutton(renderer, font, b3, BARRE_SEPARATION + 60, y);
    }
    y+=125;
    button button4;
    if(b->menu == 4 || b->menu == 3){
    	button4 = createtitle(renderer, font, b4, BARRE_SEPARATION + 60, y);
    } else {
        button4 = createbutton(renderer, font, b4, BARRE_SEPARATION + 60, y);
    }

    drawtitle(renderer, title);
    drawbutton(renderer, button1);
    drawbutton(renderer, button2);
    if(b->menu == 4){
    	drawtitle(renderer, button3);
    } else {
        drawbutton(renderer, button3);
    }
    if(b->menu == 4 ||  b->menu == 3){
    	drawtitle(renderer, button4);
    } else {
        drawbutton(renderer, button4);
    }

    SDL_RenderPresent(renderer);
}


///=========================================================
//Lancer une nouvelle partie
void new_game()
{
    chessboard b = create_board();
    SDL_Init(SDL_INIT_VIDEO);
    if (TTF_Init() < 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    window = create_window("chess", b);
    renderer = create_renderer(window);
    draw_board(renderer, b);
    
    TTF_Font* font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (font == NULL) {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    for(int i = 1; i < 8; i++){
        b->menu = i;
        render_menu(renderer, b);
        sleep(1);
    }

    SDL_RenderPresent(renderer);
    //Manche(renderer, b, 1, b->colonne * b->ligne);
    bool quit = false;
    while (!quit) {
        // Gestion des événements
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;  // Quitter le menu si l'événement de fermeture de la fenêtre est détecté
            }
        }
    }

    destroy_window_and_renderer(window, renderer);
    SDL_Quit();
    return 0;
}
