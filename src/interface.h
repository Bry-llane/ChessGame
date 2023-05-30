#ifndef INTERFACE_H
#define INTERFACE_H
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <unistd.h>
#include "move.h"


#define TAILLE_CASE 70
#define TAILLE_SEPARATION 6
#define TAILLE_T (TAILLE_CASE+TAILLE_SEPARATION)
#define ESPACE_BOARD 90
#define BARRE_SEPARATION (8 * TAILLE_T) + TAILLE_SEPARATION + (2 * ESPACE_BOARD)


// Dimensions de la fenêtre
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 794

// Polices
#define FONT_SIZE 24
#define FONT_PATH "./format/font.ttf"

typedef struct {
    SDL_Rect rect;  // Rectangle pour la position et la taille du bouton
    SDL_Texture* texture;  // Texture pour le texte du bouton
} button;

SDL_Window* create_window(const char* title);
SDL_Renderer* create_renderer(SDL_Window* window);
void destroy_window_and_renderer(SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path);
int isInt();
bool existeFile(char* file);
button createbutton(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);
button createtitle(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);
void drawbutton(SDL_Renderer* renderer, button but);
void draw_board(SDL_Renderer* renderer);
void actualise_board(SDL_Renderer* renderer, chessboard b);
void render_menu(SDL_Renderer* renderer, chessboard b, int menu);
void menu_variation(SDL_Renderer* renderer, chessboard b, int but, int *menu);
void tour_de_jeu(SDL_Renderer* renderer);
int game();

#endif

