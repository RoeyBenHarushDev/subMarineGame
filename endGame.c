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



/********************EndGame**************/
void printMovments(FILE *result, FILE *moves)
{
    char line[12] = {'\0'};
    fprintf(result, "\nMOVES:\n");
    printf("\nMOVES:\n");
    while (fscanf(moves, "%[^\n]\n", line))
    {
        fprintf(result, "\n");
        printf("\n");
        if (strcmp(line, "PRINT_BOARD") != 0)
        {
            printf("%s", line);
            fprintf(result, "%s", line);
        }
        else
            break;
    }
    fclose(result);
    fclose(moves);
    exit(1);
}

void PrintBoards(Board *board1, Board *board2, char *argv[])
{
    int player, col, row;
    Board *board;
    // FILE *resultFile = fopen("Result.txt", "a");
    FILE *resultFile = fopen(argv[4], "a");
    for (player = 0; player < 2; player++)
    {
        if (player == 0)
            board = board1;
        else
            board = board2;
        fprintf(resultFile, "Player Number %d board: \n", player + 1);
        printf("Player Number %d board: \n", player + 1);
        for (row = 0; row < 10; row++)
        {
            fprintf(resultFile, "\n|");
            printf("\n|");
            for (col = 0; col < 10; col++)
            {
                if (board->Matrix[row][col].stat == 0)
                { 
                    fprintf(resultFile, "   |");
                    printf(BLUE " %c " RESET "|", 219);// 223 or 219
                }
                if (board->Matrix[row][col].stat == 1)
                {
                    fprintf(resultFile, " ♦ |");
                    printf(GREEN " %c " RESET "|", 219);                    
                }
                if (board->Matrix[row][col].stat == 2)
                {
                    fprintf(resultFile, "   |");
                    printf(BLUE " %c " RESET "|", 219);
                }
                if (board->Matrix[row][col].stat == 3)
                {
                    fprintf(resultFile, " ♣ |");
                    printf(ORANGE " %c "RESET "|", 219);
                }
                if (board->Matrix[row][col].stat == 4)
                {
                    fprintf(resultFile, " ♠ |");
                    printf(RED " %c " RESET "|", 219);
                }
            }
                printf("\n");
        }
        fprintf(resultFile, "\n");
        printf("\n");
        fprintf(resultFile, "-----------------------\n");
        printf("-----------------------\n");
        fprintf(resultFile, "'♦' -> Unhited Submarine Spot\n'♣' -> Hit\n'♠' -> Miss\n\n");
        printf(GREEN "%c "RESET"->  Unhited Submarine Spot\n"RED"%c" RESET" -> Hit\n"ORANGE"%c"RESET" -> Miss\n\n", 223, 223, 223);
    }
     fclose(resultFile);
}
int checkIfWin(Board *board1, Board *board2, FILE *result)
{
    int num = 0;
    if (board1->Counter == 20)
        num = 1;
    if (board2->Counter == 20)
        num = 2;
    switch (num)
    {
    case 0:
        return 0;
    case 1:
        fprintf(result, "\t\t\nPlayer 2 is the WINNER!\n\n");
        printf("\t\t\nPlayer 2 is the WINNER!\n\n");

        // freeBoards(board1,board2);
        break;
    case 2:
        fprintf(result, "\t\t\nPlayer 1 is the WINNER!\n\n");
        printf("\t\t\nPlayer 1 is the WINNER!\n\n");
        // freeBoards(board1,board2);

    default:
        break;
    }
}
