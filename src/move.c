#include "move.h"

pos* deplacement_valide_pion(piece p, pos from, chessboard b, int* nb_deplacements)
{
    pos* deplacements = malloc(4 * sizeof(pos)); // Un pion a au plus 4 déplacements possibles

    *nb_deplacements = 0; // Réinitialiser le nombre de déplacements

    int direction = (piece_color(p) == BLANC) ? -1 : 1; // Déterminer la direction de déplacement du pion en fonction de sa couleur

    // Vérifier le déplacement d'une case vers l'avant
    pos forward_pos = {from.x, from.y + direction};
    if (in_board(forward_pos) && empty_piece(b->board[forward_pos.y][forward_pos.x])) {
        deplacements[(*nb_deplacements)++] = forward_pos;

        // Vérifier le déplacement de deux cases vers l'avant si le pion n'a pas encore bougé
        if (((piece_color(p) == BLANC && from.y == 6) || (piece_color(p) == NOIR && from.y == 1)) &&
            empty_piece(b->board[forward_pos.y + direction][forward_pos.x])) {
            pos double_forward_pos = {forward_pos.x, forward_pos.y + direction};
            if (in_board(double_forward_pos)) {
                deplacements[(*nb_deplacements)++] = double_forward_pos;
            }
        }
    }

    // Vérifier les déplacements diagonaux pour la prise en passant
    pos left_diagonal_pos = {from.x - 1, from.y + direction};
    pos right_diagonal_pos = {from.x + 1, from.y + direction};

    if (in_board(left_diagonal_pos) && !empty_piece(b->board[left_diagonal_pos.y][left_diagonal_pos.x])) {
        if (piece_color(b->board[left_diagonal_pos.y][left_diagonal_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = left_diagonal_pos;
        }
    }

    if (in_board(right_diagonal_pos) && !empty_piece(b->board[right_diagonal_pos.y][right_diagonal_pos.x])) {
        if (piece_color(b->board[right_diagonal_pos.y][right_diagonal_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = right_diagonal_pos;
        }
    }

    return realloc(deplacements, (*nb_deplacements) * sizeof(pos)); // Réallouer le tableau à la taille exacte
}

pos* deplacement_valide_roi(piece p, pos from, chessboard b, int *nb_deplacements)
{
    pos *deplacements = malloc(8 * sizeof(pos)); // Le roi a au plus 8 déplacements valides (déplacements dans toutes les directions)
    *nb_deplacements = 0; // Réinitialiser le nombre de déplacements

    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        pos new_pos = (pos){from.x + dx[i], from.y + dy[i]};
        if (in_board(new_pos)) {
            piece destination = b->board[new_pos.y][new_pos.x];

            if (destination == NULL || piece_color(destination) != piece_color(p)) {
                deplacements[(*nb_deplacements)++] = new_pos;
            }
        }
    }

    return realloc(deplacements, (*nb_deplacements) * sizeof(pos)); // Réallouer le tableau à la taille exacte
}

pos* deplacement_valide_tour(piece p, pos from, chessboard b, int *nb_deplacements)
{
    pos *deplacements = malloc(14 * sizeof(pos)); // Une tour a au plus 14 déplacements possibles (7 déplacements sur la même colonne et 7 déplacements sur la même ligne)

    *nb_deplacements = 0; // Réinitialiser le nombre de déplacements

    // Parcourir les positions sur la même colonne
    for (int y = from.y + 1; y < 8; y++) {
        pos new_pos = {from.x, y};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de couleur différente est présente)
        } else {
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de la même couleur est présente)
        }
    }

    for (int y = from.y - 1; y >= 0; y--) {
        pos new_pos = {from.x, y};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de couleur différente est présente)
        } else {
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de la même couleur est présente)
        }
    }

    // Parcourir les positions sur la même ligne
    for (int x = from.x + 1; x < 8; x++) {
        pos new_pos = {x, from.y};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de couleur différente est présente)
        } else {
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de la même couleur est présente)
        }
    }

    for (int x = from.x - 1; x >= 0; x--) {
        pos new_pos = {x, from.y};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de couleur différente est présente)
        } else {
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de la même couleur est présente)
        }
    }

    return realloc(deplacements, (*nb_deplacements) * sizeof(pos)); // Réallouer le tableau à la taille exacte
}

pos* deplacement_valide_fou(piece p, pos from, chessboard b, int *nb_deplacements)
{
    pos *deplacements = malloc(28 * sizeof(pos)); // Un fou a au plus 28 déplacements possibles (7 déplacements sur chaque diagonale)

    *nb_deplacements = 0; // Réinitialiser le nombre de déplacements

    // Parcourir les positions sur la diagonale supérieure droite
    for (int i = 1; from.x + i < 8 && from.y + i < 8; i++) {
        pos new_pos = {from.x + i, from.y + i};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de couleur différente est présente)
        } else {
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de la même couleur est présente)
        }
    }

    // Parcourir les positions sur la diagonale inférieure droite
    for (int i = 1; from.x + i < 8 && from.y - i >= 0; i++) {
        pos new_pos = {from.x + i, from.y - i};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de couleur différente est présente)
        } else {
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de la même couleur est présente)
        }
    }

    // Parcourir les positions sur la diagonale supérieure gauche
    for (int i = 1; from.x - i >= 0 && from.y + i < 8; i++) {
        pos new_pos = {from.x - i, from.y + i};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de couleur différente est présente)
        } else {
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de la même couleur est présente)
        }
    }

    // Parcourir les positions sur la diagonale inférieure gauche
    for (int i = 1; from.x - i >= 0 && from.y - i >= 0; i++) {
        pos new_pos = {from.x - i, from.y - i};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de couleur différente est présente)
        } else {
            break; // Arrêter la boucle si un obstacle est rencontré (une pièce de la même couleur est présente)
        }
    }

    return realloc(deplacements, (*nb_deplacements) * sizeof(pos)); // Réallouer le tableau à la taille exacte
}

pos* deplacement_valide_cavalier(piece p, pos from, chessboard b, int* nb_deplacements)
{
    pos* deplacements = malloc(8 * sizeof(pos)); // Un cavalier a au plus 8 déplacements possibles

    *nb_deplacements = 0; // Réinitialiser le nombre de déplacements

    int dx[8] = { 1, 1, -1, -1, 2, 2, -2, -2 };
    int dy[8] = { 2, -2, 2, -2, 1, -1, 1, -1 };

    for (int i = 0; i < 8; i++) {
        int x = from.x + dx[i];
        int y = from.y + dy[i];
        pos new_pos = { x, y };
        if (in_board(new_pos) && (empty_piece(b->board[new_pos.y][new_pos.x]) || piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p))) {
            deplacements[(*nb_deplacements)++] = new_pos;
        }
    }

    return realloc(deplacements, (*nb_deplacements) * sizeof(pos)); // Réallouer le tableau à la taille exacte
}

pos* deplacement_valide_reine(piece p, pos from, chessboard b, int* nb_deplacements)
{
    pos* deplacements_tour = deplacement_valide_tour(p, from, b, nb_deplacements);
    int nb_deplacements_tour = *nb_deplacements;
    pos* deplacements_fou = deplacement_valide_fou(p, from, b, nb_deplacements);
    int nb_deplacements_fou = *nb_deplacements;

    pos* deplacements_reine = malloc((nb_deplacements_tour + nb_deplacements_fou) * sizeof(pos));
    *nb_deplacements = 0; // Réinitialiser le nombre de déplacements

    // Copier les déplacements de la tour dans les déplacements de la reine
    for (int i = 0; i < nb_deplacements_tour; i++) {
        deplacements_reine[(*nb_deplacements)++] = deplacements_tour[i];
    }

    // Copier les déplacements du fou dans les déplacements de la reine
    for (int i = 0; i < nb_deplacements_fou; i++) {
        deplacements_reine[(*nb_deplacements)++] = deplacements_fou[i];
    }

    // Libérer la mémoire des tableaux de déplacements de la tour et du fou
    free(deplacements_tour);
    free(deplacements_fou);

    return deplacements_reine; // Réallouer le tableau à la taille exacte
}

pos* deplacement_valide(piece p, pos from, chessboard b, int* nb_deplacements)
{
    pos* deplacements;

    switch (p->typePiece) {
        case PION:
            deplacements = deplacement_valide_pion(p, from, b, nb_deplacements);
            break;
        case TOUR:
            deplacements = deplacement_valide_tour(p, from, b, nb_deplacements);
            break;
        case FOU:
            deplacements = deplacement_valide_fou(p, from, b, nb_deplacements);
            break;
        case CAVALIER:
            deplacements = deplacement_valide_cavalier(p, from, b, nb_deplacements);
            break;
        case REINE:
            deplacements = deplacement_valide_reine(p, from, b, nb_deplacements);
            break;
        case ROI:
            deplacements = deplacement_valide_roi(p, from, b, nb_deplacements);
            break;
        default: // Type de pièce invalide
            *nb_deplacements = 0;
            deplacements = NULL;
            break;
    }

    return deplacements;
}

void annuler_deplacement(chessboard b, pos from, pos to, piece captured_piece)
{
    // Remettre la pièce déplacée à sa position d'origine
    b->board[from.y][from.x] = b->board[to.y][to.x];

    // Remettre la pièce capturée à sa position d'origine (si une pièce a été capturée)
    if (captured_piece != NULL)
        b->board[to.y][to.x] = captured_piece;
    else
        b->board[to.y][to.x] = NULL;
}

bool est_en_echec(piece roi, pos position_roi, chessboard b)
{
    // Vérification des menaces provenant des pièces adverses

    // Parcours du plateau pour trouver les pièces adverses
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            piece p = b->board[y][x];

            if(p != NULL){
            // Vérification si la pièce est de couleur adverse
                if (piece_color(p) != piece_color(roi)) {

                    // Vérification des déplacements valides de la pièce adverse
                    int nb_deplacements;
                    pos* deplacements = deplacement_valide(p, (pos) {x, y}, b, &nb_deplacements);

                    // Parcours des déplacements valides de la pièce adverse
                    for (int i = 0; i < nb_deplacements; i++) {
                        pos deplacement = deplacements[i];

                        // Vérification si le roi est menacé par la pièce adverse
                        if (deplacement.x == position_roi.x && deplacement.y == position_roi.y) {
                            free(deplacements); // Libération de la mémoire
                            return true; // Le roi est en échec
                        }
                    }

                    free(deplacements); // Libération de la mémoire
                }
            }
        }
    }

    return false; // Le roi n'est pas en échec
}

bool est_en_echec_et_mat(piece roi, pos position_roi, chessboard b)
{
    if (est_en_echec(roi, position_roi, b)) {
        int nb_deplacements;
        pos* deplacements = deplacement_valide_roi(roi, position_roi, b, &nb_deplacements);

        for(int i = 0; i < nb_deplacements; i++){
            pos temp_pos_roi = {deplacements[i].x, deplacements[i].y};

            piece temp_piece = b->board[temp_pos_roi.y][temp_pos_roi.x];
            b->board[temp_pos_roi.y][temp_pos_roi.x] = roi;
            b->board[position_roi.y][position_roi.x] = NULL;

            // Vérifier si le roi est toujours en échec après le déplacement
            if (!est_en_echec(roi, (pos) {temp_pos_roi.x, temp_pos_roi.y}, b)) {
                // Le roi a trouvé une échappatoire, il n'est pas en échec et mat
                b->board[position_roi.y][position_roi.x] = roi;
                b->board[temp_pos_roi.y][temp_pos_roi.x] = temp_piece;
                return false;
            }

            // Annuler le déplacement simulé
            b->board[position_roi.y][position_roi.x] = roi;
            b->board[temp_pos_roi.y][temp_pos_roi.x] = temp_piece;
        }
        return true;
    }
    return false;
}

bool verifier_mouvement(pos from, pos to, chessboard b)
{
    // Effectuer temporairement le déplacement
    piece captured_piece = b->board[to.y][to.x];
    b->board[to.y][to.x] = b->board[from.y][from.x];
    b->board[from.y][from.x] = NULL;

    // Vérifier si le roi est en échec après le déplacement
    pos position_roi = recup_roi(b->board[to.y][to.x], b);
    bool est_echec = est_en_echec(b->board[position_roi.y][position_roi.x], position_roi, b);

    // Annuler le déplacement
    annuler_deplacement(b, from, to, captured_piece);

    // Retourner 0 si le roi est en échec, sinon 1
    return !est_echec;
}

bool deplacement(pos from, pos to, chessboard b)
{
    // Effectuer le déplacement
    b->board[to.y][to.x] = b->board[from.y][from.x];
    b->board[from.y][from.x] = NULL;
}


/*
bool verifier_mouvement(piece piece, pos from, pos to, chessboard b) {
    // Copier le plateau d'échecs pour effectuer une simulation de mouvement
    chessboard temp_board = create_board_vide();
    memcpy(temp_board, b, sizeof(struct chessboard));

    // Effectuer le mouvement sur le plateau temporaire
    piece captured_piece = temp_board->board[to.y][to.x];
    temp_board->board[to.y][to.x] = temp_board->board[from.y][from.x];
    temp_board->board[from.y][from.x] = NULL;

    // Obtenir la position du roi du joueur courant
    pos position_roi;
    //piece roi = piece_color(piece) == BLANC ? ROI_BLANC : ROI_NOIR;

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (temp_board->board[y][x]->typePiece == ROI && piece_color(temp_board->board[y][x]) == piece_color(piece)) {
                position_roi.x = x;
                position_roi.y = y;
                break;
            }
        }
    }
    piece roi = temp_board->board[position_roi.y][position_roi.x];

    // Vérifier si le roi est en échec après le mouvement
    bool est_en_echec_apres_mouvement = est_en_echec(roi, position_roi, temp_board);

    // Vérifier si le roi est en échec et mat après le mouvement
    bool est_en_echec_et_mat_apres_mouvement = est_en_echec_et_mat(roi, position_roi, temp_board);

    // Annuler le mouvement simulé
    annuler_deplacement(temp_board, from, to, captured_piece);

    // Si le roi est en échec après le mouvement, le mouvement est invalide
    if (est_en_echec_apres_mouvement) {
        free(temp_board);
        return false;
    }

    // Si le roi est en échec et mat après le mouvement, le mouvement est invalide
    if (est_en_echec_et_mat_apres_mouvement) {
        free(temp_board);
        return false;
    }

    // Le mouvement est valide
    free(temp_board);
    return true;
}
*/


