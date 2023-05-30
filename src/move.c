#include "move.h"
#include <stdlib.h>

pos* deplacement_valide_pion(piece p, pos from, chessboard b, int* nb_deplacements)
{
    pos* deplacements = malloc(4 * sizeof(pos)); // Un pion a au plus 4 d�placements possibles

    *nb_deplacements = 0; // R�initialiser le nombre de d�placements

    int direction = (piece_color(p) == BLANC) ? -1 : 1; // D�terminer la direction de d�placement du pion en fonction de sa couleur

    // V�rifier le d�placement d'une case vers l'avant
    pos forward_pos = {from.x, from.y + direction};
    if (in_board(forward_pos) && empty_piece(b->board[forward_pos.y][forward_pos.x])) {
        deplacements[(*nb_deplacements)++] = forward_pos;

        // V�rifier le d�placement de deux cases vers l'avant si le pion n'a pas encore boug�
        if (((piece_color(p) == BLANC && from.y == 6) || (piece_color(p) == NOIR && from.y == 1)) &&
            empty_piece(b->board[forward_pos.y + direction][forward_pos.x])) {
            pos double_forward_pos = {forward_pos.x, forward_pos.y + direction};
            if (in_board(double_forward_pos)) {
                deplacements[(*nb_deplacements)++] = double_forward_pos;
            }
        }
    }

    // V�rifier les d�placements diagonaux pour la prise en passant
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

    return realloc(deplacements, (*nb_deplacements) * sizeof(pos)); // R�allouer le tableau � la taille exacte
}

pos* deplacement_valide_roi(piece p, pos from, chessboard b, int *nb_deplacements)
{
    pos *deplacements = malloc(8 * sizeof(pos)); // Le roi a au plus 8 d�placements valides (d�placements dans toutes les directions)
    *nb_deplacements = 0; // R�initialiser le nombre de d�placements

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

    return realloc(deplacements, (*nb_deplacements) * sizeof(pos)); // R�allouer le tableau � la taille exacte
}

pos* deplacement_valide_tour(piece p, pos from, chessboard b, int *nb_deplacements)
{
    pos *deplacements = malloc(14 * sizeof(pos)); // Une tour a au plus 14 d�placements possibles (7 d�placements sur la m�me colonne et 7 d�placements sur la m�me ligne)

    *nb_deplacements = 0; // R�initialiser le nombre de d�placements

    // Parcourir les positions sur la m�me colonne
    for (int y = from.y + 1; y < 8; y++) {
        pos new_pos = {from.x, y};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de couleur diff�rente est pr�sente)
        } else {
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de la m�me couleur est pr�sente)
        }
    }

    for (int y = from.y - 1; y >= 0; y--) {
        pos new_pos = {from.x, y};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de couleur diff�rente est pr�sente)
        } else {
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de la m�me couleur est pr�sente)
        }
    }

    // Parcourir les positions sur la m�me ligne
    for (int x = from.x + 1; x < 8; x++) {
        pos new_pos = {x, from.y};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de couleur diff�rente est pr�sente)
        } else {
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de la m�me couleur est pr�sente)
        }
    }

    for (int x = from.x - 1; x >= 0; x--) {
        pos new_pos = {x, from.y};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de couleur diff�rente est pr�sente)
        } else {
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de la m�me couleur est pr�sente)
        }
    }

    return realloc(deplacements, (*nb_deplacements) * sizeof(pos)); // R�allouer le tableau � la taille exacte
}

pos* deplacement_valide_fou(piece p, pos from, chessboard b, int *nb_deplacements)
{
    pos *deplacements = malloc(28 * sizeof(pos)); // Un fou a au plus 28 d�placements possibles (7 d�placements sur chaque diagonale)

    *nb_deplacements = 0; // R�initialiser le nombre de d�placements

    // Parcourir les positions sur la diagonale sup�rieure droite
    for (int i = 1; from.x + i < 8 && from.y + i < 8; i++) {
        pos new_pos = {from.x + i, from.y + i};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de couleur diff�rente est pr�sente)
        } else {
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de la m�me couleur est pr�sente)
        }
    }

    // Parcourir les positions sur la diagonale inf�rieure droite
    for (int i = 1; from.x + i < 8 && from.y - i >= 0; i++) {
        pos new_pos = {from.x + i, from.y - i};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de couleur diff�rente est pr�sente)
        } else {
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de la m�me couleur est pr�sente)
        }
    }

    // Parcourir les positions sur la diagonale sup�rieure gauche
    for (int i = 1; from.x - i >= 0 && from.y + i < 8; i++) {
        pos new_pos = {from.x - i, from.y + i};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de couleur diff�rente est pr�sente)
        } else {
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de la m�me couleur est pr�sente)
        }
    }

    // Parcourir les positions sur la diagonale inf�rieure gauche
    for (int i = 1; from.x - i >= 0 && from.y - i >= 0; i++) {
        pos new_pos = {from.x - i, from.y - i};
        if (empty_piece(b->board[new_pos.y][new_pos.x])) {
            deplacements[(*nb_deplacements)++] = new_pos;
        } else if (piece_color(b->board[new_pos.y][new_pos.x]) != piece_color(p)) {
            deplacements[(*nb_deplacements)++] = new_pos;
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de couleur diff�rente est pr�sente)
        } else {
            break; // Arr�ter la boucle si un obstacle est rencontr� (une pi�ce de la m�me couleur est pr�sente)
        }
    }

    return realloc(deplacements, (*nb_deplacements) * sizeof(pos)); // R�allouer le tableau � la taille exacte
}

pos* deplacement_valide_cavalier(piece p, pos from, chessboard b, int* nb_deplacements)
{
    pos* deplacements = malloc(8 * sizeof(pos)); // Un cavalier a au plus 8 d�placements possibles

    *nb_deplacements = 0; // R�initialiser le nombre de d�placements

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

    return realloc(deplacements, (*nb_deplacements) * sizeof(pos)); // R�allouer le tableau � la taille exacte
}

pos* deplacement_valide_reine(piece p, pos from, chessboard b, int* nb_deplacements)
{
    pos* deplacements_tour = deplacement_valide_tour(p, from, b, nb_deplacements);
    int nb_deplacements_tour = *nb_deplacements;
    pos* deplacements_fou = deplacement_valide_fou(p, from, b, nb_deplacements);
    int nb_deplacements_fou = *nb_deplacements;

    pos* deplacements_reine = malloc((nb_deplacements_tour + nb_deplacements_fou) * sizeof(pos));
    *nb_deplacements = 0; // R�initialiser le nombre de d�placements

    // Copier les d�placements de la tour dans les d�placements de la reine
    for (int i = 0; i < nb_deplacements_tour; i++) {
        deplacements_reine[(*nb_deplacements)++] = deplacements_tour[i];
    }

    // Copier les d�placements du fou dans les d�placements de la reine
    for (int i = 0; i < nb_deplacements_fou; i++) {
        deplacements_reine[(*nb_deplacements)++] = deplacements_fou[i];
    }

    // Lib�rer la m�moire des tableaux de d�placements de la tour et du fou
    free(deplacements_tour);
    free(deplacements_fou);

    return deplacements_reine; // R�allouer le tableau � la taille exacte
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
        default: // Type de pi�ce invalide
            *nb_deplacements = 0;
            deplacements = NULL;
            break;
    }

    return deplacements;
}

void annuler_deplacement(chessboard b, pos from, pos to, piece captured_piece)
{
    // Remettre la pi�ce d�plac�e � sa position d'origine
    b->board[from.y][from.x] = b->board[to.y][to.x];

    // Remettre la pi�ce captur�e � sa position d'origine (si une pi�ce a �t� captur�e)
    if (captured_piece != NULL)
        b->board[to.y][to.x] = captured_piece;
    else
        b->board[to.y][to.x] = NULL;
}

bool est_en_echec(piece roi, pos position_roi, chessboard b)
{
    // V�rification des menaces provenant des pi�ces adverses

    // Parcours du plateau pour trouver les pi�ces adverses
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            piece p = b->board[y][x];

            if(p != NULL){
            // V�rification si la pi�ce est de couleur adverse
                if (piece_color(p) != piece_color(roi)) {

                    // V�rification des d�placements valides de la pi�ce adverse
                    int nb_deplacements;
                    pos* deplacements = deplacement_valide(p, (pos) {x, y}, b, &nb_deplacements);

                    // Parcours des d�placements valides de la pi�ce adverse
                    for (int i = 0; i < nb_deplacements; i++) {
                        pos deplacement = deplacements[i];

                        // V�rification si le roi est menac� par la pi�ce adverse
                        if (deplacement.x == position_roi.x && deplacement.y == position_roi.y) {
                            free(deplacements); // Lib�ration de la m�moire
                            return true; // Le roi est en �chec
                        }
                    }

                    free(deplacements); // Lib�ration de la m�moire
                }
            }
        }
    }

    return false; // Le roi n'est pas en �chec
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

            // V�rifier si le roi est toujours en �chec apr�s le d�placement
            if (!est_en_echec(roi, (pos) {temp_pos_roi.x, temp_pos_roi.y}, b)) {
                // Le roi a trouv� une �chappatoire, il n'est pas en �chec et mat
                b->board[position_roi.y][position_roi.x] = roi;
                b->board[temp_pos_roi.y][temp_pos_roi.x] = temp_piece;
                return false;
            }

            // Annuler le d�placement simul�
            b->board[position_roi.y][position_roi.x] = roi;
            b->board[temp_pos_roi.y][temp_pos_roi.x] = temp_piece;
        }
        return true;
    }
    return false;
}

bool verifier_mouvement(pos from, pos to, chessboard b)
{
    // Effectuer temporairement le d�placement
    piece captured_piece = b->board[to.y][to.x];
    b->board[to.y][to.x] = b->board[from.y][from.x];
    b->board[from.y][from.x] = NULL;

    // V�rifier si le roi est en �chec apr�s le d�placement
    pos position_roi = recup_roi(b->board[to.y][to.x], b);
    bool est_echec = est_en_echec(b->board[position_roi.y][position_roi.x], position_roi, b);

    // Annuler le d�placement
    annuler_deplacement(b, from, to, captured_piece);

    // Retourner 0 si le roi est en �chec, sinon 1
    return !est_echec;
}

bool deplacement(pos from, pos to, chessboard b)
{
    // Effectuer le d�placement
    b->board[to.y][to.x] = b->board[from.y][from.x];
    b->board[from.y][from.x] = NULL;
}


pos trouver_piece_aleatoire(chessboard b, color couleur) {
    // V�rifier si le plateau est valide
    if (b == NULL || b->board == NULL) {
        printf("Erreur : Plateau invalide.\n");
        return (pos) { -1, -1 }; // Retourner une position invalide
    }
    
    // G�n�rer une liste de positions valides pour les pi�ces de la couleur donn�e
    pos positions_valides[64]; // Tableau de positions valides (max 64 cases)
    int nb_positions_valides = 0; // Nombre de positions valides trouv�es
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            piece p = b->board[i][j];
            if (p != NULL && p->couleur == couleur) {
                positions_valides[nb_positions_valides++] = (pos) { i, j };
            }
        }
    }
    
    // V�rifier si des positions valides ont �t� trouv�es
    if (nb_positions_valides == 0) {
        printf("Aucune pi�ce de couleur donn�e sur le plateau.\n");
        return (pos) { -1, -1 }; // Retourner une position invalide
    }
    
    // S�lectionner une position al�atoire parmi les positions valides
    int indice_aleatoire = rand() % nb_positions_valides;
    return positions_valides[indice_aleatoire];
}

pos* IA(chessboard b, color c) {
    bool choix = false;
    pos* deplacement_possible;
    int nb_deplacement_possible;
    pos* move = malloc(2 * sizeof(pos)); // Allouer de l'espace pour les positions "from" et "to"
    
    while (!choix) {
        pos from = trouver_piece_aleatoire(b, c);
        
        deplacement_possible = deplacement_valide(b->board[from.y][from.x], from, b, &nb_deplacement_possible);
        if (nb_deplacement_possible > 0) {
            int indice_aleatoire = rand() % nb_deplacement_possible;
            pos to = deplacement_possible[indice_aleatoire];
            
            if (verifier_mouvement(from, to, b)) {
                move[0] = from;
                move[1] = to;
                choix = true;
            }
        }
    }
    
    return move;
}
