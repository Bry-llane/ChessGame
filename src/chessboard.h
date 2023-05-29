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
void vider_board(chessboard b);
void free_board(chessboard b);
void print_board(chessboard b);
bool in_board(pos from);
bool same_column_nothing_between(pos from, pos to, chessboard b);
bool same_row_nothing_between(pos from, pos to, chessboard b);
bool sameDiagonalNothingBetween(pos from, pos to, chessboard b);
chessboard create_board_vide ();
pos recup_roi(piece piece, chessboard b);
pos recup_roi_with_color(color c, chessboard b);

#endif
