#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

// Dimensions de la fenêtre
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Couleurs
SDL_Color COLOR_WHITE = {255, 255, 255, 255};
SDL_Color COLOR_RED = {255, 0, 0, 255};

// Polices
#define FONT_SIZE 24
#define FONT_PATH "front.ttf"

// Structure pour représenter un bouton
typedef struct {
    SDL_Rect rect;  // Rectangle pour la position et la taille du bouton
    SDL_Texture* texture;  // Texture pour le texte du bouton
} Button;

// Fonction pour créer un bouton
Button createButton(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    Button button;

    // Création de la surface de texte
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, COLOR_WHITE);
    if (surface == NULL) {
        printf("Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        exit(1);
    }

    // Création de la texture à partir de la surface
    button.texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (button.texture == NULL) {
        printf("Erreur lors de la création de la texture du bouton : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        exit(1);
    }

    // Libération de la surface
    SDL_FreeSurface(surface);

    // Définition de la position et de la taille du bouton
    button.rect.x = x;
    button.rect.y = y;
    SDL_QueryTexture(button.texture, NULL, NULL, &button.rect.w, &button.rect.h);

    return button;
}

// Fonction pour dessiner un bouton
void drawButton(SDL_Renderer* renderer, Button button) {
    // Dessiner le rectangle du bouton
    SDL_SetRenderDrawColor(renderer, COLOR_RED.r, COLOR_RED.g, COLOR_RED.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &button.rect);

    // Dessiner le texte du bouton
    SDL_RenderCopy(renderer, button.texture, NULL, &button.rect);
}

int main(int argc, char** argv) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() < 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Chargement de la police
    TTF_Font* font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (font == NULL) {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Création des boutons
    Button button1 = createButton(renderer, font, "Option 1", 100, 200);
    Button button2 = createButton(renderer, font, "Option 2", 100, 250);
    Button button3 = createButton(renderer, font, "Option 3", 100, 300);

    // Boucle principale du menu
    bool quit = false;
    while (!quit) {
        // Gestion des événements
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;  // Quitter le menu si l'événement de fermeture de la fenêtre est détecté
            }
            else if (event.type == SDL_KEYDOWN) {
                // Gérer les actions en fonction des touches du clavier
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        printf("Option 1 sélectionnée.\n");
                        break;
                    case SDLK_2:
                        printf("Option 2 sélectionnée.\n");
                        break;
                    case SDLK_3:
                        printf("Option 3 sélectionnée.\n");
                        break;
                    case SDLK_q:
                        quit = true;  // Quitter le menu si la touche 'q' est pressée
                        break;
                    default:
                        break;
                }
            }
        }

        // Effacer le contenu de la fenêtre
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessiner les boutons
        drawButton(renderer, button1);
        drawButton(renderer, button2);
        drawButton(renderer, button3);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources
    SDL_DestroyTexture(button1.texture);
    SDL_DestroyTexture(button2.texture);
    SDL_DestroyTexture(button3.texture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
