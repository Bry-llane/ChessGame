#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "piece.h"
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct chessboard {
    piece **board;
    int nb_joueur;
    int position;
    int manche;
} *chessboard;

chessboard create_board ();
void free_board(chessboard b);
void print_board(chessboard b);
bool in_board(pos from);
void new_board(chessboard b);
pos recup_roi(piece piece, chessboard b);
pos recup_roi_with_color(color c, chessboard b);
void sauvegarder_plateau(chessboard b, const char* nom_fichier);
void charger_plateau(chessboard b, const char* nom_fichier);
void remplir_plateau(chessboard b);
void faire_promotion(chessboard b, int sh);


#endif
