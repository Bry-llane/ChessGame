NOM=ChessGame

# La liste des dependances 
$(NOM) : ./src/main.c ./src/piece.c ./src/chessboard.c ./src/move.c ./src/interface.c
	gcc -Wall -Wextra -pedantic -std=c99 -o $(NOM) $^ $(shell sdl2-config --cflags --libs) -lSDL2_ttf

# Les ordres speciaux
clean :
	rm $(NOM)

# Le all pour savoir ce que je dois faire au final 
all : $(NOM)
