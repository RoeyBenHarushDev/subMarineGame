#ifndef MIDGAME_H
#define MIDGAME_H
#include <stdio.h>
void readMoves(Board *board1, Board *board2, FILE *moves,FILE *result, char *argv[]);
int checkIfWin(Board *board1, Board *board2,FILE *result);

#endif