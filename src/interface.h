#ifndef INTERFACE_H
#define INTERFACE_H

#include <unistd.h>
#include "interface.h"

SDL_Window* Create_window(const char* title, chessboard b);
SDL_Renderer* Create_renderer(SDL_Window* window);
void Destroy_window_and_renderer(SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture* LoadTexture(SDL_Renderer* renderer, char* path);
int IsInt();
bool ExisteFile(char* file);
void Rename_save();


#endif

