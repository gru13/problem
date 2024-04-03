#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_ROW       15
#define MAX_COL       60
#define MAX_BIRDS    128
#define BIRD_FREQ     90

#define C_TRUE         1
#define C_FALSE        0

void initHollow(char[MAX_ROW][MAX_COL]);
void printHollow(char[MAX_ROW][MAX_COL]);
char escapeOver(char, char, int, int);
char isDone(char, int);
int  moveHero(char, int, char[MAX_ROW][MAX_COL]);
void moveBird(int, int[MAX_BIRDS], int[MAX_BIRDS], char[MAX_ROW][MAX_COL]);
void moveInHollow(char, int, int, int, int, char[MAX_ROW][MAX_COL]);
void printResult(char, char, int, int);
int  randomInt(int);

int main()
{
  srand(time(NULL));

  return 0;
}



/*
  Function:  randomInt
  Purpose:   returns a random number in the range [0,max)
  Parameters:
    in:      maximum of range
    return:  randomly generated number
*/

int randomInt(int max)
{
  return(rand() % max);
}

