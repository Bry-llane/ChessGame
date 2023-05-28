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

SDL_Window* Create_window(const char* title, chessboard b);
SDL_Renderer* Create_renderer(SDL_Window* window);
void Destroy_window_and_renderer(SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture* LoadTexture(SDL_Renderer* renderer, char* path);
int IsInt();
bool ExisteFile(char* file);
void Rename_save();


#endif

