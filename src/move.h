#ifndef MOVE_H
#define MOVE_H

#include "chessboard.h"
#include "piece.h"

pos* deplacement_valide_pion(piece p, pos from, chessboard b, int* nb_deplacements);
pos* deplacement_valide_roi(piece p, pos from, chessboard b, int *nb_deplacements);
pos* deplacement_valide_tour(piece p, pos from, chessboard b, int *nb_deplacements);
pos* deplacement_valide_fou(piece p, pos from, chessboard b, int *nb_deplacements);
pos* deplacement_valide_cavalier(piece p, pos from, chessboard b, int* nb_deplacements);
pos* deplacement_valide_reine(piece p, pos from, chessboard b, int* nb_deplacements);
pos* deplacement_valide(piece p, pos from, chessboard b, int* nb_deplacements);
void annuler_deplacement(chessboard b, pos from, pos to, piece captured_piece);
bool est_en_echec(piece roi, pos position_roi, chessboard b);
bool est_en_echec_et_mat(piece roi, pos position_roi, chessboard b);
bool verifier_mouvement(pos from, pos to, chessboard b);
void deplacement(pos from, pos to, chessboard b);
pos trouver_piece_aleatoire(chessboard b, color couleur);
pos* IA(chessboard b, color c) ;

#endif
