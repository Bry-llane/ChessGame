#include "chessboard.h"

//creation du plateau de jeu
chessboard create_board ()
{
    chessboard B = (chessboard)malloc(sizeof(struct chessboard));

    piece **b = (piece **)malloc(8*sizeof(piece*));
    for (int i=0; i<8; i++){
        b[i] = (piece*)malloc(8*sizeof(piece));
    }

    //cases vides
    for(int i = 2; i < 6; i++){
        for(int j = 0; j < 8; j++){
            b[i][j] = NULL;
        }
    }

    //cases pions
    for(int i = 0; i < 8; i++){
        b[1][i] = create_piece(PION, NOIR);
    }
    for(int i = 0; i < 8; i++){
        b[6][i] = create_piece(PION, BLANC);
    }

    //cases tours
    for(int i = 0; i < 8; i+=7){
        b[0][i] = create_piece(TOUR, NOIR);
    }
    for(int i = 0; i < 8; i+=7){
        b[7][i] = create_piece(TOUR, BLANC);
    }

    //cases cavaliers
    for(int i = 1; i < 7; i+=5){
        b[0][i] = create_piece(CAVALIER, NOIR);
    }
    for(int i = 1; i < 7; i+=5){
        b[7][i] = create_piece(CAVALIER, BLANC);
    }

    //cases fous
    for(int i = 2; i < 6; i+=3){
        b[0][i] = create_piece(FOU, NOIR);
    }
    for(int i = 2; i < 6; i+=3){
        b[7][i] = create_piece(FOU, BLANC);
    }

    //cases reines
    b[0][3] = create_piece(REINE, NOIR);
    b[7][3] = create_piece(REINE, BLANC);

    //cases rois
    b[0][4] = create_piece(ROI, NOIR);
    b[7][4] = create_piece(ROI, BLANC);

    B->nb_joueur = 2;
    B->position = 0;
    B->manche = BLANC;
    B->board = b;
    return B;
}

//liberer le tableau de jeu
void free_board(chessboard b)
{
    if (b != NULL) {
        if (b->board != NULL) {
            for (int i = 0; i < 8; i++) {
                free(b->board[i]);
            }
            free(b->board);
        }
        free(b);
    }
    b = NULL;
}

//Afficher le plateau de jeu
void print_board(chessboard b)
{
    int num = 8;
    printf("  +");
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 3; j++){
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    for(int i = 0; i < 8; i++){
        printf("%d ", num);
        num--;
        for(int j = 0; j < 8; j++){
            printf("| %c ", piece_caractere(b->board[i][j]));
        }
        printf("|\n");

        printf("  +");
        for(int y = 0; y < 8; y++){
            for(int x = 0; x < 3; x++){
                printf("-");
            }
            printf("+");
        }
        printf("\n");
    }

    printf("    ");
    int alphabet = 65;
    for(int j = 0; j < 8; j++){
        printf("%c   ", alphabet);
        alphabet++;
    }
    printf("\n");

}

bool in_board(pos from)
{
    return (from.x >= 0 && from.x < 8 && from.y >= 0 && from.y < 8);
}

bool same_column_nothing_between(pos from, pos to, chessboard b)
{
    // Vérifier si les positions sont sur la même colonne
    if (from.x != to.x) {
        return false;
    }

    // Vérifier s'il y a des pièces entre les positions
    int start_y = (from.y < to.y) ? from.y + 1 : to.y + 1;
    int end_y = (from.y < to.y) ? to.y - 1 : from.y - 1;

    for (int y = start_y; y <= end_y; y++) {
        if (b->board[y][from.x] != NULL) {
            return false; // Il y a une pièce entre les positions
        }
    }

    return true; // Aucune pièce entre les positions sur la même colonne
}

bool same_row_nothing_between(pos from, pos to, chessboard b)
{
    // Vérifier si les positions sont sur la même ligne
    if (from.y != to.y) {
        return false;
    }

    int start_x = (from.x < to.x) ? from.x + 1 : to.x + 1;
    int end_x = (from.x < to.x) ? to.x : from.x;

    for (int x = start_x; x < end_x; x++) {
        if (b->board[from.y][x] != NULL) {
            return false;
        }
    }

    return true;
}

bool sameDiagonalNothingBetween(pos from, pos to, chessboard b)
{
    int delta_x = (from.x < to.x) ? 1 : -1;
    int delta_y = (from.y < to.y) ? 1 : -1;

    int x = from.x + delta_x;
    int y = from.y + delta_y;

    while (x != to.x && y != to.y) {
        if (b->board[y][x] != NULL) {
            return false;
        }
        x += delta_x;
        y += delta_y;
    }

    return true;
}

chessboard create_board_vide ()
{
    chessboard B = (chessboard)malloc(sizeof(struct chessboard));

    piece **b = (piece **)malloc(8*sizeof(piece*));
    for (int i=0; i<8; i++){
        b[i] = (piece*)malloc(8*sizeof(piece));
    }

    //cases vides
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            b[i][j] = NULL;
        }
    }

    B->board = b;
    return B;
}

pos recup_roi(piece piece, chessboard b)
{
    pos p = { -1, -1 };

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (b->board[y][x] != NULL){
                if (b->board[y][x]->typePiece == ROI && piece_color(b->board[y][x]) == piece_color(piece)) {
                    p.x = x;
                    p.y = y;
                    return p;
                }
           }
        }
    }
    return p;
}
