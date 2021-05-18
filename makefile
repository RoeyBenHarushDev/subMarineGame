prog: main.o InitSubmarine.o midGame.o endGame.o
	gcc main.o InitSubmarine.o midGame.o endGame.o -o Game.exe
main.o: main.c subMarineBoard.h
	gcc -c main.c
InitSubmarine.o: InitSubmarine.c subMarineBoard.h
	gcc -c InitSubmarine.c
midGame.o: midGame.c midGame.h
	gcc -c midGame.c
endGame.o: endGame.c endGame.h
	gcc -c endGame.c
	