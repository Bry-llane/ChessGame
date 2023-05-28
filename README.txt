Le projet est à executer sur linux
Pour lancer ce projet il faut avoir la biblotheque sdl et sdl_tff d'installer ou l'installer avec :

sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-ttf-dev

Creer l'executable avec :

gcc -Wall -Wextra -pedantic -std=c99 -o ChessGame ./src/main.c ./src/piece.c ./src/chessboard.c ./src/move.c ./src/interface.c $(sdl2-config --cflags --libs) -lSDL2_ttf


Et enfin pour lancer le jeu :

./ChessGame
