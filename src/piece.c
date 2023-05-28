#include "piece.h"

//creer une piece
piece create_piece(shape type, color couleur)
{
    piece p = (piece)malloc(sizeof(struct piece));
    p->couleur = couleur;
    p->typePiece = type;

    return p;
}

//couleur d'une piece
color piece_color(piece p)
{
    return p->couleur;
}

//piece est vide
bool empty_piece(piece p)
{
    return p == NULL;
}

//liberer lespace ocupe par une piece
void free_piece(piece *p)
{
    if (*p != NULL) {
        free(*p);
        *p = NULL;
    }
}

// promotion de pièce
void piece_promotion(shape newShape, piece *p)
{
    if (*p != NULL && newShape != ROI && newShape != PION) {
        (*p)->typePiece = newShape;
    }
}

//caractere d'une piece
char piece_caractere(piece p)
{
    if(p == NULL) return ' '; //espace pour null

    if(p->couleur == NOIR){
        if(p->typePiece == PION){
            return 'p';
        } else if(p->typePiece == FOU){
            return 'f';
        } else if(p->typePiece == CAVALIER){
            return 'c';
        } else if(p->typePiece == TOUR){
            return 't';
        } else if(p->typePiece == REINE){
            return 'r';
        } else if(p->typePiece == ROI){
            return 'k';
        }
    } else if(p->couleur == BLANC){
        if(p->typePiece == PION){
            return 'P';
        } else if(p->typePiece == FOU){
            return 'F';
        } else if(p->typePiece == CAVALIER){
            return 'C';
        } else if(p->typePiece == TOUR){
            return 'T';
        } else if(p->typePiece == REINE){
            return 'R';
        } else if(p->typePiece == ROI){
            return 'K';
        }
    } else {
        return 'x'; //x comme caractere d'erreur
    }
}

//afficher le caractere d'une piece
void print_piece_caractere(piece p)
{
    printf("%c", piece_caractere(p));
}
