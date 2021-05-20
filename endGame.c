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
    return;
}

void PrintBoards(Board *board1, Board *board2, char *argv[])
{
    int player, col, row, numIndex = 1, charIndex = 65;
    Board *board;
    FILE *resultFile = fopen(argv[4], "a");
    for (player = 0; player < 2; player++)
    {
        numIndex = 1;
        if (player == 0)
            board = board1;
        else
            board = board2;
        fprintf(resultFile, "Player Number %d board: \n", player + 1);
        printf("Player Number %d board: \n", player + 1);
        fprintf(resultFile,"\n      ");
        printf("\n     ");
        for (int i = 65; i < 75; i++)
        {
            fprintf(resultFile,"%c   ", i);
            printf("%c   ", i);
        }
        for (row = 0; row < 10; row++)
        {

            fprintf(resultFile, "\n%0.2d  |", numIndex);
            printf("\n%0.2d |", numIndex++);
            for (col = 0; col < 10; col++)
            {
                if (board->Matrix[row][col].stat == 0)
                {
                    fprintf(resultFile, " ~ |");
                    printf(BLUE " %c " RESET "|", 219);
                }
                if (board->Matrix[row][col].stat == 1)
                {
                    fprintf(resultFile, " ♦ |");
                    printf(GREEN " %c " RESET "|", 219);
                }
                if (board->Matrix[row][col].stat == 2)
                {
                    fprintf(resultFile, " ~ |");
                    printf(BLUE " %c " RESET "|", 219);
                }
                if (board->Matrix[row][col].stat == 3)
                {
                    fprintf(resultFile, " ♣ |");
                    printf(ORANGE " %c " RESET "|", 219);
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
        fprintf(resultFile, "'~' -> The Pacific Ocean\n'♦' -> Unhited Submarine Spot\n'♠' -> Hit\n'♣' -> Miss\n\n");
        printf(BLUE "%c " RESET "-> The Pacific Ocean\n" GREEN "%c " RESET "-> Unhited Submarine Spot\n" RED "%c" RESET " -> Hit\n" ORANGE "%c" RESET " -> Miss\n\n", 219, 219, 219, 219);
    }
    fclose(resultFile);
}

int checkIfWin(Board *board, FILE *result, int playerNum)
{
    if (board->Counter == 20)
    {
        fprintf(result, "\t\t\nPlayer %d is the WINNER!\n\n", playerNum);
        printf("\t\t\nPlayer %d is the " GREEN "W" RED "I" ORANGE "N" BLUE "N" ORANGE "E" RED "R" GREEN "!" RESET "\n\n", playerNum);
        return 1;
    }
    return 0;
}
void freeAll(Board *board1, Board *board2)
{
    free(board1);
    free(board2);
}
void closeAll(FILE *FILE1, FILE *FILE2, FILE *FILE3, FILE *FILE4)
{
    fclose(FILE1);
    fclose(FILE2);
    fclose(FILE3);
    fclose(FILE4);
}