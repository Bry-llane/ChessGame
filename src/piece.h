#ifndef PIECE_H
#define PIECE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum shape {PION = 1, FOU = 2, CAVALIER = 3, TOUR = 5, REINE = 9, ROI = 0} shape;
typedef enum color {NOIR, BLANC} color;

typedef struct pos{
    int x;
    int y;
} pos;

typedef struct piece{
    shape typePiece;
    color couleur;
} *piece;


piece create_piece(shape type, color couleur);
color piece_color(piece p);
bool empty_piece(piece p);
void free_piece(piece *p);
void piece_promotion(shape newShape, piece *p);
char piece_caractere(piece p);
void print_piece_caractere(piece p);

#endif
