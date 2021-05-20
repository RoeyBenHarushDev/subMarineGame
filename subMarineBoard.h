#ifndef BOARDGAME_H
#define BOARDGAME_H
#include <stdio.h>

typedef enum letterToNumber{a = 1,b,c,d,e,f,g,h,i} Letter;
typedef enum stat {Empty = 0, Full, Error, Miss, Hit} stat;
typedef enum diraction {single=1,row,col} dir;

typedef struct  SubmarineQuardinate{
    Letter col;
    int row;
}Quar;

typedef struct Square{
    Quar index;
    stat stat;
    dir dir;
}Square;

typedef struct Board{
    Square Matrix[10][10];
    int Counter; // if counter = 20 -> win.
}Board;
/*  Gets the files and with them creates the 2 game boards and reset boards  */
Board *CreateBoards();
void ResetBoards(Board *board);
void getDataFromFile(Board*, FILE *Location);
void converteLine2Quar(Board *board, char *location);
void initSubMarine(Board *board, Quar location1, Quar location2);
int checkError(Board *board, Quar location1, Quar location2);
#endif