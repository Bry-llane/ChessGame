#ifndef INTERFACE_H
#define INTERFACE_H
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <unistd.h>
#include "move.h"

typedef struct {
    SDL_Rect rect;  // Rectangle pour la position et la taille du bouton
    SDL_Texture* texture;  // Texture pour le texte du bouton
} button;

SDL_Window* create_window(const char* title, chessboard b);
SDL_Renderer* create_renderer(SDL_Window* window);
void cestroy_window_and_renderer(SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path);
int isInt();
bool existeFile(char* file);
void rename_save();


#endif

