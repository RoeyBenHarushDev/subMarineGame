#ifndef MIDGAME_H
#define MIDGAME_H
#include <stdio.h>
void readMoves(Board *board1, Board *board2, FILE *moves,FILE *result, char *argv[]);
int attackMove(int player, int indexChar, int indexNum, Board *board, FILE *result);
int checkRestSubmarine(Board *board, int indexChar, int indexNum, int player, FILE *result);

#endif