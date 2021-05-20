#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subMarineBoard.h"
#include "midGame.h"
#include "endGame.h"

// MADE WITH LOVE BY(ROYEY_BEN_HARUSH->ID.315676163 && GILAD MEIR->ID.313416562);

int main(int argc, char *argv[])
{

    if(argc != 5){
        printf("Input Error...\n");
        return 1;
    }
    Board *board1 = CreateBoards();
    Board *board2 = CreateBoards();
    board1->Counter = 0;
    board2->Counter = 0;

    FILE *players1Locations = fopen(argv[1], "r");
    FILE *players2Locations = fopen(argv[2], "r");
    FILE *simulation= fopen(argv[3],"r");
    FILE *ResultFile = fopen(argv[4], "w"); 

    getDataFromFile(board1, players1Locations);
    getDataFromFile(board2, players2Locations);
    readMoves(board1, board2, simulation, ResultFile, argv);
    freeAll(board1, board2);
    closeAll(players1Locations, players2Locations, simulation, ResultFile);


    return 0;
}
