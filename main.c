#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subMarineBoard.h"
#include "midGame.h"



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

    // FILE *players1Locations = fopen("initBoard_p1.txt", "r"); //FOR DEBUG ONLY
    // FILE *players2Locations = fopen("initBoard_p2.txt", "r"); //FOR DEBUG ONLY
    // FILE *simulation = fopen("Simulation.txt", "r");          //FOR DEBUG ONLY
    // FILE *ResultFile = fopen("Result.txt", "w");              //FOR DEBUG ONLY
    FILE *players1Locations = fopen(argv[1], "r");
    FILE *players2Locations = fopen(argv[2], "r");
    FILE *simulation= fopen(argv[3],"r");
    FILE *ResultFile = fopen(argv[4], "w"); 

    getDataFromFile(board1, players1Locations);
    getDataFromFile(board2, players2Locations);
    // PrintBoards(board1, board2); //FOR DEBUG
    readMoves(board1, board2, simulation, ResultFile, argv);
    // PrintBoards(board1, board2); //FOR DEBUG

    // if(boards == NULL || playersMovment == NULL || resultFile == NULL){
    //     printf("Unable to open file...\n");
    //     return 1;
    // }

    return 0;
}
