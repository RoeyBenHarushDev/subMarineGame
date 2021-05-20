#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subMarineBoard.h"
#include "midGame.h"
#include "endGame.h"
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define ORANGE "\x1b[33m"
#define BLUE "\x1b[34m"
/**************MIDGAME**********************/
void readMoves(Board *board1, Board *board2, FILE *moves, FILE *result, char *argv[])
{
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
            FILE *fp_move = fopen(argv[3], "r");
            FILE *fp_res = fopen(argv[4], "a");
            printMovments(fp_res, fp_move);
            return;
        }

        player = line[7] - 48;
        if (line[11] == '0')
            indexNum = 9;

        else
        {
            indexNum = line[10] - 49;
        }
        indexChar = line[9] - 65;
        if (player == 1)
        {
            if (attackMove(player, indexChar, indexNum, board2, result))
                if (checkRestSubmarine(board2, indexChar, indexNum, player, result) == 1)
                {
                    fprintf(result, "\t\tYou've destruct the whole submarine! WELL DONE LAD!\n\n");
                }
        }
        if (player == 2)
        {
            if (attackMove(player, indexChar, indexNum, board1, result))
                if (checkRestSubmarine(board1, indexChar, indexNum, player, result) == 1)
                {
                    fprintf(result, "\t\tYou've destruct the whole submarine! WELL DONE LAD!\n\n");
                }
        }
    }
    return;
    //return;
}

int attackMove(int player, int indexChar, int indexNum, Board *board, FILE *result)
{

    //player1 make moves on board2

    if (indexChar < 0 || indexChar > 9 || indexNum < 0 || indexNum > 9)
    {
        fprintf(result, "\n\n\t\t ERROR! %c%d IS AN IMPOSSIBLE MOVE!\n", indexChar + 65, indexNum + 1);
        printf(RED "\n\n\t\t ERROR! %c%d IS AN IMPOSSIBLE MOVE!\n" RESET, indexChar + 65, indexNum + 1);
        return 0;
    }
    if (board->Matrix[indexNum][indexChar].stat == 1)
    { //means its a hit
        board->Matrix[indexNum][indexChar].stat = 4;
        fprintf(result, "\tPlayer %d: %c%d ITS A HIT! YOU ARE ON FIRE!\n\n", player, indexChar + 65, indexNum + 1);
        printf("\tPlayer %d: %c%d  ITS A HIT! YOU ARE ON FIRE!\n\n", player, indexChar + 65, indexNum + 1);
        board->Counter++;
        return 1;
    }
    if (board->Matrix[indexNum][indexChar].stat == 0 || board->Matrix[indexNum][indexChar].stat == 2)
    { //means its a miss
        board->Matrix[indexNum][indexChar].stat = 3;
        fprintf(result, "\tPlayer %d: %c%d  YOU MISSED!\n\n", player, indexChar + 65, indexNum + 1);
        printf("\tPlayer %d: %c%d  YOU MISSED!\n\n", player, indexChar + 65, indexNum + 1);
        return 0;
    }
}
int checkRestSubmarine(Board *board, int indexChar, int indexNum, int player, FILE *result)
{
    int select = 0;
    select = board->Matrix[indexNum][indexChar].dir;
    switch (select)
    {
    case 1:
        //means its a single sub
        printf(GREEN "\n\t\tYou've destruct the whole submarine! WELL DONE LAD!\n" RESET);
        if (checkIfWin(board, result, player) == 1)
            return 2;
        return 1;

    case 2:
        //means its a row sub
        while ((--indexChar != 0) && (board->Matrix[indexNum][indexChar].stat != 2))
            ;

        while (board->Matrix[indexNum][++indexChar].stat != 2)
        {

            if (board->Matrix[indexNum][indexChar].stat == 4)
                continue;
            else
                return 0;
        }
        printf(GREEN "\t\tYou've destruct the whole submarine! WELL DONE LAD!\n\n" RESET);
        if (checkIfWin(board, result, player) == 1)
            return 2;
        return 1;

    case 3:
        //means its a col sub
        while ((--indexNum != 0) && (board->Matrix[indexNum][indexChar].stat != 2))
            ;

        while (board->Matrix[++indexNum][indexChar].stat != 2)
        {

            if (board->Matrix[indexNum][indexChar].stat == 4)
                continue;
            else
                return 0;
        }
        printf(GREEN "\t\tYou've destruct the whole submarine! WELL DONE LAD!\n\n" RESET);
        if (checkIfWin(board, result, player) == 1)
            return 2;
        return 1;
    }
}