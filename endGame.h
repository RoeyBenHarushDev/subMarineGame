#ifndef ENDGAME_H
#define ENDGAME_H

void printMovments(FILE *result, FILE *moves);
void PrintBoards(Board *board1, Board *board2, char *argv[]);
int checkIfWin(Board *board, FILE *result,int playerNum);
void freeAll(Board *board1,Board *board2);
void closeAll(FILE *FILE1,FILE *FILE2,FILE *FILE3,FILE *FILE4);

#endif