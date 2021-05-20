#include <stdio.h>
#include <stdlib.h>
#include "subMarineBoard.h"
#include "midGame.h"
#include "endGame.h"
#define BUFFER 1000

/***********INITILIZE*****************/

Board *CreateBoards()
{
    Board *players = (Board *)malloc(sizeof(Board));
    int player;
    int numIndex;
    char letterIndex;
    char insertPlayerMovmentFromFile[1000];
    ResetBoards(players);
    return players;
}

void getDataFromFile(Board *board, FILE *playerLocation)
{
    int player;
    char line[1000] = {'\0'};
    char zevel;
    Quar temp;
    while (1)
    {

        for (int i = 0; i < 8; i++)
        {
            line[i] = fgetc(playerLocation);
            if (line[i] == '\n')
            {
                converteLine2Quar(board, line);
                i = -1;
                for (int i = 0; i < 20; i++)
                    line[i] = '\0';
                continue;
            }

            if (line[0] == '#')
            {
                line[0] = '\0';
                while (1)
                {
                    zevel = fgetc(playerLocation);
                    if (zevel == '\n')
                        break;
                }
                i = -1;
                continue;
            }

            if (line[i] == EOF)
            {
                line[i] = '\n';
                converteLine2Quar(board, line);
                return;
            }
        }
    }
}
// convretes Data to Quardinates

void converteLine2Quar(Board *board, char *location)
{
    Quar temp1, temp2;
    if (location[0] > 64)        // mean its a letter
        temp1.col = location[0]; // temp1.col = first letter
    if (location[2] == '-')
    {                                 // mean its a single number
        temp1.row = location[1] - 49; // converte from char number to integer
        temp2.col = location[3];      //next letter
        if (location[5] == '\n')      // mean that is a single num
            temp2.row = location[4] - 49;
        else
            (temp2.row = 9);
    }
    else // i + 2  = number
    {
        temp1.row = 9;
        temp2.col = location[4];

        if (location[7] == '\n')
            temp2.row = 9;

        else //means its a single num
            (temp2.row = location[5]);
    }
    initSubMarine(board, temp1, temp2);
}
int checkError(Board *board, Quar location1, Quar location2)
{
    int col1 = location1.col - 65;
    int col2 = location2.col - 65;
    if ((col1 == col2) && (location1.row == location2.row))
    { //mean its a single subMarine
        if ((board->Matrix[location1.row][col1].stat == 2) || (board->Matrix[location1.row][col1].stat == 1))
        {
            return 0;
        }
        return 1;
    }
    if (col1 == col2)
    {
        // mean its a col of submarin
        while (location1.row <= location2.row)
        {
            if ((board->Matrix[location1.row][col1].stat == 2) || (board->Matrix[location1.row][col1].stat == 1))
            {
                return 0;
            }
            location1.row++;
        }
        return 1;
    }
    if (location1.row == location2.row)
    { // mean its a line subMarine
        while (col1 <= col2)
        {
            if ((board->Matrix[location1.row][col1].stat == 2) || (board->Matrix[location1.row][col1].stat == 1))
            {
                return 0;
            }
            col1++;
        }
        return 1;
    }
}
void initSubMarine(Board *board, Quar location1, Quar location2)
{
    int col1 = location1.col - 65;
    int col2 = location2.col - 65;
    if (col1 != col2 && location1.row != location2.row)
    {
        printf("\nERROR! Submarine %c%d-%c%d is slant!\n", location1.col, location1.row + 1, location2.col, location2.row + 1);
        return;
    }
    if (checkError(board, location1, location2) == 0)
    {
        printf("\nWrong location of submarine located in %c%d-%c%d", location1.col, location1.row + 1, location2.col, location2.row + 1);
        return;
    }
    if ((col1 == col2) && (location1.row == location2.row))
    { //mean its a single subMarine.
        board->Matrix[location1.row][col1].stat = 1;
        board->Matrix[location1.row][col1].dir = 1;

        if (col1 > 0 && col1 < 9)
        {
            //means its not on sides
            board->Matrix[location1.row][col1 + 1].stat = 2;
            board->Matrix[location1.row][col1 - 1].stat = 2;
            if (location1.row != 0)
            {
                board->Matrix[location1.row - 1][col1 + 1].stat = 2;
                board->Matrix[location1.row - 1][col1 - 1].stat = 2;
            }
            if (location1.row != 9)
            {
                board->Matrix[location1.row + 1][col1 + 1].stat = 2;
                board->Matrix[location1.row + 1][col1 - 1].stat = 2;
            }
        }
        else if (col1 == 0)
        {
            board->Matrix[location1.row][col1 + 1].stat = 2;
            if (location1.row != 0)
            {
                board->Matrix[location1.row - 1][col1 + 1].stat = 2;
            }
            if (location1.row != 9)
            {
                board->Matrix[location1.row + 1][col1 + 1].stat = 2;
            }
        }
        else if (col1 == 9)
            board->Matrix[location1.row][col1 + 1].stat = 2;
        if (location1.row != 0)
        {
            board->Matrix[location1.row - 1][col1 - 1].stat = 2;
        }
        if (location1.row != 9)
        {
            board->Matrix[location1.row + 1][col1 - 1].stat = 2;
        }

        if (location1.row > 0 && location1.row < 9)
        {
            //means its not in bottom or top
            board->Matrix[location1.row + 1][col1].stat = 2;
            board->Matrix[location1.row - 1][col1].stat = 2;
        }
        else if (location1.row == 0)
            board->Matrix[location1.row + 1][col1].stat = 2;
        else if (location1.row == 9)
            board->Matrix[location1.row - 1][col1].stat = 2;

        return;
    }
    if (col1 == col2)
    {
        // mean its a col of submarin
        if (col1 > 0 && col2 < 9)
        { //means it in middle of board

            if (location1.row != 0)
            { //means its not on top
                board->Matrix[location1.row - 1][col1].stat = 2;
                board->Matrix[location1.row - 1][col1 + 1].stat = 2;
                board->Matrix[location1.row - 1][col1 - 1].stat = 2;
            }
            while (location1.row <= location2.row)
            {
                board->Matrix[location1.row][col1].stat = 1;
                board->Matrix[location1.row][col1].dir = 3;
                board->Matrix[location1.row][col1 - 1].stat = 2;
                board->Matrix[location1.row++][col1 + 1].stat = 2;
            }
            if (location1.row != 9)
            { //means it not on bottom

                board->Matrix[location1.row][col1].stat = 2;
                board->Matrix[location1.row][col1 + 1].stat = 2;
                board->Matrix[location1.row][col1 - 1].stat = 2;
            }

            return;
        }
        else if (col1 == 0)
        {
            //means it on left

            if (location1.row != 0)
            { //means its not on top
                board->Matrix[location1.row - 1][col1].stat = 2;
                board->Matrix[location1.row - 1][col1 + 1].stat = 2;
            }
            while (location1.row <= location2.row)
            {
                board->Matrix[location1.row][col1].stat = 1;
                board->Matrix[location1.row][col1].dir = 3;
                board->Matrix[location1.row++][col1 + 1].stat = 2;
            }
            if (location1.row != 9)
            { //means it not on bottom

                board->Matrix[location1.row][col1].stat = 2;
                board->Matrix[location1.row][col1 + 1].stat = 2;
            }

            return;
        }
        else if (col2 == 9)
        {
            //means it on right

            if (location1.row != 0)
            { //means its not on top
                board->Matrix[location1.row - 1][col1].stat = 2;
                board->Matrix[location1.row - 1][col1 - 1].stat = 2;
            }
            while (location1.row <= location2.row)
            {
                board->Matrix[location1.row][col1].stat = 1;
                board->Matrix[location1.row][col1].dir = 3;
                board->Matrix[location1.row++][col1 - 1].stat = 2;
            }
            if (location1.row != 9)
            { //means it not on bottom

                board->Matrix[location1.row][col1].stat = 2;
                board->Matrix[location1.row][col1 - 1].stat = 2;
            }

            return;
        }
    }
    if (location1.row == location2.row)
    { // mean its a line subMarine.
        if (location1.row != 0 && location2.row != 9)
        {
            if (col1 != 0)
            {
                board->Matrix[location1.row][col1 - 1].stat = 2;
                board->Matrix[location1.row - 1][col1].stat = 2;
                board->Matrix[location1.row - 1][col1 - 1].stat = 2;
                board->Matrix[location1.row + 1][col1].stat = 2;
                board->Matrix[location1.row + 1][col1 - 1].stat = 2;
            }
            else if (col1 == 0)
            {
                board->Matrix[location1.row - 1][col1].stat = 2;
                board->Matrix[location1.row + 1][col1].stat = 2;
            }
            while (col1 <= col2)
            {
                board->Matrix[location1.row - 1][col1].stat = 2;
                board->Matrix[location1.row + 1][col1].stat = 2;
                board->Matrix[location1.row][col1++].stat = 1;
                board->Matrix[location1.row][col1].dir=2;
            }
            if (col2 != 9)
            {
                board->Matrix[location1.row][col2 + 1].stat = 2;
                board->Matrix[location1.row - 1][col1].stat = 2;
                board->Matrix[location1.row - 1][col2 + 1].stat = 2;
                board->Matrix[location1.row + 1][col1].stat = 2;
                board->Matrix[location1.row + 1][col2 + 1].stat = 2;
            }
            else if (col2 == 9)
            {
                board->Matrix[location1.row - 1][col1].stat = 2;
                board->Matrix[location1.row + 1][col1].stat = 2;
            }

            return;
        }
        else if (location1.row == 0)
        {
            if (col1 != 0)
            {
                board->Matrix[location1.row][col1 - 1].stat = 2;
                board->Matrix[location1.row + 1][col1].stat = 2;
                board->Matrix[location1.row + 1][col1 - 1].stat = 2;
            }
            else if (col1 == 0)
            {
                board->Matrix[location1.row + 1][col1].stat = 2;
            }
            while (col1 <= col2)
            {
                board->Matrix[location1.row + 1][col1].stat = 2;
                board->Matrix[location1.row][col1++].stat = 1;
                board->Matrix[location1.row][col1].dir=2;
            }
            if (col2 != 9)
            {
                board->Matrix[location1.row][col2 + 1].stat = 2;
                board->Matrix[location1.row + 1][col1].stat = 2;
                board->Matrix[location1.row + 1][col2 + 1].stat = 2;
            }
            else if (col2 == 9)
            {
                board->Matrix[location1.row + 1][col1].stat = 2;
            }

            return;
        }
        else if (location2.row == 9)
        {
            if (col1 != 0)
            {
                board->Matrix[location1.row][col1 - 1].stat = 2;
                board->Matrix[location1.row - 1][col1].stat = 2;
                board->Matrix[location1.row - 1][col1 - 1].stat = 2;
            }
            else if (col1 == 0)
            {
                board->Matrix[location1.row - 1][col1].stat = 2;
            }
            while (col1 <= col2)
            {
                board->Matrix[location1.row - 1][col1].stat = 2;
                board->Matrix[location1.row][col1++].stat = 1;
                board->Matrix[location1.row][col1].dir=2;
            }
            if (col2 != 9)
            {
                board->Matrix[location1.row][col2 + 1].stat = 2;
                board->Matrix[location1.row - 1][col1].stat = 2;
                board->Matrix[location1.row - 1][col2 + 1].stat = 2;
            }
            else if (col2 == 9)
            {
                board->Matrix[location1.row - 1][col1].stat = 2;
            }

            return;
        }
    }
}

void ResetBoards(Board *board)
{
    int col, row;
    for (row = 0; row < 10; row++)
    {
        for (col = 0; col < 10; col++)
            board->Matrix[col][row].stat = 0;
    }
}
