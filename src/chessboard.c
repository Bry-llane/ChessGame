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

    B->nb_joueur = 0;
    B->position = 0;
    B->manche = 1;
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


void new_board(chessboard b) {
    // Vérifier le paramètre
    if (b == NULL || b->board == NULL) {
        printf("Erreur : Paramètre invalide.\n");
        return;
    }
    
    // Réinitialiser toutes les positions du jeu
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            b->board[i][j] = NULL;
        }
    }
    
    b->nb_joueur = 0;
    b->position = 0;
    b->manche = 1;
    
    printf("Nouvelle partie initialisée.\n");
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

pos recup_roi_with_color(color c, chessboard b)
{
    pos p = { -1, -1 };

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (b->board[y][x] != NULL){
                if (b->board[y][x]->typePiece == ROI && piece_color(b->board[y][x]) == c) {
                    p.x = x;
                    p.y = y;
                    return p;
                }
           }
        }
    }
    return p;
}

void sauvegarder_plateau(chessboard b, const char* nom_fichier) {
    // Vérifier les paramètres
    if (b == NULL || b->board == NULL || nom_fichier == NULL) {
        printf("Erreur : Parametres invalides.\n");
        return;
    }
    
    // Ouvrir le fichier en mode écriture
    FILE* fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", nom_fichier);
        return;
    }
    
    // Parcourir le plateau et écrire les pièces dans le fichier
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            piece p = b->board[i][j];
            if (p != NULL) {
                char symbole_piece;
                switch (p->typePiece) {
                    case PION:
                        symbole_piece = 'p';
                        break;
                    case FOU:
                        symbole_piece = 'f';
                        break;
                    case CAVALIER:
                        symbole_piece = 'c';
                        break;
                    case TOUR:
                        symbole_piece = 't';
                        break;
                    case REINE:
                        symbole_piece = 'r';
                        break;
                    case ROI:
                        symbole_piece = 'k';
                        break;
                    default:
                        symbole_piece = ' ';
                        break;
                }
                if (p->couleur == BLANC) {
                    symbole_piece = toupper(symbole_piece);
                }
                fprintf(fichier, "%c ", symbole_piece);
            } else {
                fprintf(fichier, "n");
            }
        }
        fprintf(fichier, "\n");
    }
    
    // Écrire les autres informations dans le fichier
    fprintf(fichier, "%d\n", b->nb_joueur);
    fprintf(fichier, "%d\n", b->position);
    fprintf(fichier, "%d\n", b->manche);
    
    // Fermer le fichier
    fclose(fichier);
    printf("Le plateau a ete sauvegarde dans le fichier %s.\n", nom_fichier);
}

void charger_plateau(chessboard b, const char* nom_fichier) {
    // Vérifier les paramètres
    if (b == NULL || b->board == NULL || nom_fichier == NULL) {
        printf("Erreur : Paramètres invalides.\n");
        return;
    }
    
    // Ouvrir le fichier en mode lecture
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", nom_fichier);
        return;
    }
    
    // Réinitialiser toutes les pièces du plateau à NULL
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            b->board[i][j] = NULL;
        }
    }
    
    // Parcourir le fichier et charger les pièces sur le plateau
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char symbole_piece;
            if (fscanf(fichier, "%c ", &symbole_piece) == 1) {
                shape typePiece;
                color couleur;
                switch (tolower(symbole_piece)) {
                    case 'p':
                        typePiece = PION;
                        break;
                    case 'f':
                        typePiece = FOU;
                        break;
                    case 'c':
                        typePiece = CAVALIER;
                        break;
                    case 't':
                        typePiece = TOUR;
                        break;
                    case 'r':
                        typePiece = REINE;
                        break;
                    case 'k':
                        typePiece = ROI;
                        break;
                    default:
                        typePiece = -1;  // Valeur invalide pour une pièce
                        break;
                }
                couleur = isupper(symbole_piece) ? BLANC : NOIR;
                b->board[i][j] = create_piece(typePiece, couleur);
            } else {
                printf("Erreur : Format de fichier incorrect.\n");
                fclose(fichier);
                return;
            }
        }
        fscanf(fichier, "\n");
    }
    
    // Charger les autres informations du fichier
    if (fscanf(fichier, "%d", &(b->nb_joueur)) != 1 ||
        fscanf(fichier, "%d", &(b->position)) != 1 ||
        fscanf(fichier, "%d", &(b->manche)) != 1) {
        printf("Erreur : Format de fichier incorrect.\n");
        fclose(fichier);
        return;
    }
    
    // Fermer le fichier
    fclose(fichier);
    printf("Le plateau a été chargé depuis le fichier %s.\n", nom_fichier);
}

void remplir_plateau(chessboard b) {
    // Vérifier si le plateau est valide
    if (b == NULL || b->board == NULL) {
        printf("Erreur : Plateau invalide.\n");
        return;
    }
    
    // Placer les pièces noires sur la première rangée
    b->board[0][0] = create_piece(TOUR, NOIR);
    b->board[0][1] = create_piece(CAVALIER, NOIR);
    b->board[0][2] = create_piece(FOU, NOIR);
    b->board[0][3] = create_piece(REINE, NOIR);
    b->board[0][4] = create_piece(ROI, NOIR);
    b->board[0][5] = create_piece(FOU, NOIR);
    b->board[0][6] = create_piece(CAVALIER, NOIR);
    b->board[0][7] = create_piece(TOUR, NOIR);

    // Placer les pions noirs sur la deuxième rangée
    for (int j = 0; j < 8; j++) {
        b->board[1][j] = create_piece(PION, NOIR);
    }
    
    // Placer les pièces blanches sur la huitième rangée
    b->board[7][0] = create_piece(TOUR, BLANC);
    b->board[7][1] = create_piece(CAVALIER, BLANC);
    b->board[7][2] = create_piece(FOU, BLANC);
    b->board[7][3] = create_piece(REINE, BLANC);
    b->board[7][4] = create_piece(ROI, BLANC);
    b->board[7][5] = create_piece(FOU, BLANC);
    b->board[7][6] = create_piece(CAVALIER, BLANC);
    b->board[7][7] = create_piece(TOUR, BLANC);

    // Placer les pions blancs sur la septième rangée
    for (int j = 0; j < 8; j++) {
        b->board[6][j] = create_piece(PION, BLANC);
    }
    
    // Placer les cases vides sur les autres cases du plateau
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            b->board[i][j] = NULL;
        }
    }
}


void faire_promotion(chessboard b, int sh) {
    // Vérifier le paramètre
    if (b == NULL || b->board == NULL) {
        printf("Erreur : Parametre invalide.\n");
        return;
    }
    
    // Parcourir le plateau
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            piece p = b->board[i][j];
            if (p != NULL && p->typePiece == PION) {
                // Vérifier si le pion doit être promu
                if ((p->couleur == BLANC && i == 0) || (p->couleur == NOIR && i == 7)) {
                    switch (sh) {
                        case 1:
                            b->board[i][j] = create_piece(TOUR, p->couleur);
                            break;
                        case 2:
                            b->board[i][j] = create_piece(CAVALIER, p->couleur);
                            break;
                        case 3:
                            b->board[i][j] = create_piece(FOU, p->couleur);
                            break;
                        case 4:
                            b->board[i][j] = create_piece(REINE, p->couleur);
                            break;
                        default:
                            printf("Choix invalide. Le pion sera promu en Reine par defaut.\n");
                            b->board[i][j] = create_piece(REINE, p->couleur);
                            break;
                    }
                }
            }
        }
    }
}
