#ifndef ENDGAME_H
#define ENDGAME_H

void printMovments(FILE *result, FILE *moves);
void PrintBoards(Board *board1, Board *board2, char *argv[]);
int checkIfWin(Board *board1, Board *board2, FILE *result);

#endif