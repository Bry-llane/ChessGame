#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

/*
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

    // Cr�ation de la fen�tre
    SDL_Window* window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la cr�ation de la fen�tre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Cr�ation du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur lors de la cr�ation du renderer : %s\n", SDL_GetError());
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

    // Cr�ation des boutons
    Button button1 = createButton(renderer, font, "Option 1", 100, 200);
    Button button2 = createButton(renderer, font, "Option 2", 100, 250);
    Button button3 = createButton(renderer, font, "Option 3", 100, 300);

    // Boucle principale du menu
    bool quit = false;
    while (!quit) {
        // Gestion des �v�nements
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;  // Quitter le menu si l'�v�nement de fermeture de la fen�tre est d�tect�
            }
            else if (event.type == SDL_KEYDOWN) {
                // G�rer les actions en fonction des touches du clavier
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        printf("Option 1 s�lectionn�e.\n");
                        break;
                    case SDLK_2:
                        printf("Option 2 s�lectionn�e.\n");
                        break;
                    case SDLK_3:
                        printf("Option 3 s�lectionn�e.\n");
                        break;
                    case SDLK_q:
                        quit = true;  // Quitter le menu si la touche 'q' est press�e
                        break;
                    default:
                        break;
                }
            }
        }

        // Effacer le contenu de la fen�tre
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessiner les boutons
        drawButton(renderer, button1);
        drawButton(renderer, button2);
        drawButton(renderer, button3);

        // Mettre � jour l'affichage
        SDL_RenderPresent(renderer);
    }

    // Lib�ration des ressources
    SDL_DestroyTexture(button1.texture);
    SDL_DestroyTexture(button2.texture);
    SDL_DestroyTexture(button3.texture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}*/

int main()
{
    new_game();
    return 0;
}
