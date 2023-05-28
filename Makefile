NOM=ChessGame

# La liste des dependances 
$(NOM) : gcc -Wall -Wextra -pedantic -std=c99 -o ChessGame ./src/main.c ./src/piece.c ./src/chessboard.c ./src/move.c ./src/interface.c $(sdl2-config --cflags --libs) -lSDL2_ttf

# Les ordres speciaux
clean : 
	rm ChessGame

# Le all pour savoir ce que je dois faire au final 

all : $(NOM)

