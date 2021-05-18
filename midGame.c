#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subMarineBoard.h"
#include "midGame.h"
#include "endGame.h"
#define RESET = "\x1b[0m"
#define RED = "\x1b[31m"
#define BLUE = "\x1b[34m"
#define YELLOW = "\x1b[33m"
/**************MIDGAME**********************/
void readMoves(Board *board1, Board *board2, FILE *moves, FILE *result, char *argv[])
{
    //FIX WHEN HIT NUM 10 AND WHEN MARK WITH NO REASON ON BOARD
    char line[12];
    int player, indexNum, indexChar;
    for (int i = 0; i < 12; i++)
    {
        line[i] = '\0';
    }
    while (1)
    {
        fscanf(moves, "%[^\n]\n", line);
        if (strcmp(line, "PRINT_BOARD") == 0)
        {
            fclose(result);
            PrintBoards(board1, board2, argv);
        }
        if (strcmp(line, "PRINT_ MOVEMENTS") == 0)
        {
            fclose(moves);
            // FILE *fp_move = fopen("Simulation.txt", "r");
            FILE *fp_move = fopen(argv[3], "r");
            // FILE *fp_res = fopen("Result.txt", "a");
            FILE *fp_res = fopen(argv[4], "a");
            printMovments(fp_res, fp_move);
            // freeData();
        }

        player = line[7] - 48;
        switch (player)
        {
        case 1:
            //player1 make moves on board2
            indexChar = line[9] - 65;
            if (line[11] == '0')
                indexNum = 9;
            else
                indexNum = line[10] - 49;
            if (indexChar < 0 || indexChar > 9 || indexNum < 0 || indexNum > 9)
            {
                fprintf(result, "\n\n\t\t ERROR! %c%d IS AN IMPOSSIBLE MOVE!\n", indexChar + 65, indexNum + 1);
                printf("\n\n\t\t ERROR! %c%d IS AN IMPOSSIBLE MOVE!\n", indexChar + 65, indexNum + 1);
                return;
            }
            if (board2->Matrix[indexNum][indexChar].stat == 1)
            { //means its a hit
                board2->Matrix[indexNum][indexChar].stat = 4;
                fprintf(result, "\tPlayer %d: %c%d ITS A HIT! YOU ARE ON FIRE!\n\n", player, indexChar + 65, indexNum + 1);
                printf("\tPlayer %d: %c%d  ITS A HIT! YOU ARE ON FIRE!\n\n", player, indexChar + 65, indexNum + 1);
                board2->Counter++;
                checkIfWin(board1, board2, result);
            }
            if (board2->Matrix[indexNum][indexChar].stat == 0 || board2->Matrix[indexNum][indexChar].stat == 2)
            { //means its a miss
                board2->Matrix[indexNum][indexChar].stat = 3;
                fprintf(result, "\tPlayer %d: %c%d  YOU MISSED!\n\n", player, indexChar + 65, indexNum + 1);
                printf("\tPlayer %d: %c%d  YOU MISSED!\n\n", player, indexChar + 65, indexNum + 1);
            }
            break;
        case 2:
            //player2 make moves on board1
            indexChar = line[9] - 65;
            if (line[11] == '0')
                indexNum = 9;
            else
                indexNum = line[10] - 49;
            if (indexChar < 0 || indexChar > 9 || indexNum < 0 || indexNum > 9)
            {
                fprintf(result, "\n\t ERROR! %c%d IS AN IMPOSSIBLE MOVE!\n", indexChar + 65, indexNum + 1);
                printf("\n\t ERROR! %c%d IS AN IMPOSSIBLE MOVE!\n", indexChar + 65, indexNum + 1);
                return;
            }
            if (board1->Matrix[indexNum][indexChar].stat == 1)
            { //means its a hit
                board1->Matrix[indexNum][indexChar].stat = 4;
                fprintf(result, "\tPlayer %d: %c%d  ITS A HIT! YOU ARE ON FIRE!\n\n", player, indexChar + 65, indexNum + 1);
                printf("\tPlayer %d: %c%d ITS A HIT! YOU ARE ON FIRE!\n\n", player, indexChar + 65, indexNum + 1);
                board1->Counter++;
                checkIfWin(board1, board2, result);
            }
            if (board1->Matrix[indexNum][indexChar].stat == 0 || board1->Matrix[indexNum][indexChar].stat == 2)
            { //means its a miss
                board1->Matrix[indexNum][indexChar].stat = 3;
                fprintf(result, "\tPlayer %d: %c%d  YOU MISSED!\n\n", player, indexChar + 65, indexNum + 1);
                printf("\tPlayer %d: %c%d  YOU MISSED!\n\n", player, indexChar + 65, indexNum + 1);
            }
            break;
        }
    }
}