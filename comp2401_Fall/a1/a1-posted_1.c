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

#define TIMMY 'T'
#define HAROLD 'H'
#define BIRD 'v'
#define SPACE ' '
#define DEAD '+'
#define TRUE 'T'
#define FALSE 'F'


int  randomInt(int);//
void initHollow(char[MAX_ROW][MAX_COL]);//
void printHollow(char[MAX_ROW][MAX_COL]);//
int  moveHero(char, int, char[MAX_ROW][MAX_COL]);//
void moveBird(int, int[MAX_BIRDS], int[MAX_BIRDS], char[MAX_ROW][MAX_COL]);//
void moveInHollow(char, int, int, int, int, char[MAX_ROW][MAX_COL]);//
char isDone(char, int);
char escapeOver(char, char, int, int);//
void printResult(char, char, int, int);

int newBird(int[MAX_BIRDS], int[MAX_BIRDS], int);

int main()
{
  srand( (unsigned)time(NULL));

  char  Hollow[MAX_ROW][MAX_COL];
  int birdsRow[MAX_BIRDS], birdsCol[MAX_BIRDS];
  int no_of_birds = 0;
  int Tcol = 0;// Timmy column location
  int Hcol = 0;// Harold column location

  initHollow(Hollow);
  printHollow(Hollow);


  while(Hollow[MAX_ROW-1][Tcol] != DEAD || Hollow[MAX_ROW-1][Hcol] != DEAD){
    printHollow(Hollow);
    // if Harold is alive
    // printf("h");
    if(Hollow[MAX_ROW-1][Hcol] != DEAD && Hcol < MAX_COL){
      Hcol = moveHero(HAROLD, Hcol, Hollow);
      if(Hcol == MAX_COL - 1){
        Hcol = MAX_COL;
      }
    }
    //if Timmy is alive
    if(Hollow[MAX_ROW-1][Tcol] != DEAD && Tcol < MAX_COL){
      Tcol = moveHero(TIMMY, Tcol, Hollow);
      if(Tcol == MAX_COL-1){
        Tcol = MAX_COL;
      }
    }
    // creation of new bird
    if(no_of_birds+1 < MAX_BIRDS){
      no_of_birds += newBird(birdsRow, birdsCol, no_of_birds);
      moveInHollow(BIRD, 0,birdsCol[no_of_birds-1],0,birdsCol[no_of_birds-1],Hollow);
    }
    for(int i = 0;i<no_of_birds;i++){
      moveBird(i, birdsRow, birdsCol, Hollow);
      if(birdsRow[i]==MAX_ROW-1){
        if(birdsCol[i] == Hcol){
          Hollow[MAX_ROW-1][birdsCol[i]] = DEAD;
        }
        if(birdsCol[i] == Tcol){
          Hollow[MAX_ROW-1][birdsCol[i]] = DEAD;
        }
      }
    }

  }

  printf("%d", randomInt(10));
  return 0;
}



/*
  Function:  randomInt
  Purpose:   returns a random number in the range [0,max)
  Parameters:
    in:      maximum of range
    return:  randomly generated number
*/

int randomInt(int max){
  return(rand() % max);
}


void initHollow(char hollow[MAX_ROW][MAX_COL]){
  for (int i = 0;i<MAX_ROW;i++){
    for (int j = 0;j<MAX_COL;j++){
      hollow[i][j] = SPACE;
    }
  }
}

void printHollow(char hollow[MAX_ROW][MAX_COL]){
  printf("--------------------------------------------------------------------------------\n");
  for (int i = 0;i<MAX_ROW;i++){
    for (int j = 0;j<MAX_COL;j++){
      printf("%c",hollow[i][j]);
    }
    printf("\n");
  }
  printf("--------------------------------------------------------------------------------\n");
}

void moveInHollow(char avatar, int oldRow, int oldCol, int newRow, int newCol, char hollow[MAX_ROW][MAX_COL]){
  // checking if it in hollow and if not we are making it  into hollow
  if(oldRow > MAX_ROW || oldCol > MAX_COL || oldCol<0 || oldRow < 0){
    return;
  }
  if(newRow < 0){
    newRow = 0;
  }
  if(newCol < 0 ){
    newCol = 0;
  }
  if(newRow > MAX_ROW){
    newRow = MAX_ROW-1;
  }
  if(newCol > MAX_COL){
    newCol = MAX_COL-1;
  }
  hollow[oldRow][oldCol] = SPACE;
  hollow[newRow][newCol] = avatar;

}


int  moveHero(char avatar, int col, char hollow[MAX_ROW][MAX_COL]){
    int oldCol = col;
    if(avatar == TIMMY){
      /*
          Fast walk     50%       move 3 columns right
          Slide         20%       move 2 columns left
          Slow walk     30%       move 1 column right
      */
      float Fast_Walk = 0.5*randomInt(10);
      float Slide = 0.2*randomInt(10);
      float Slow_Walk = 0.3*randomInt(10);
      // if  Fast Walk is chosen
      if(Fast_Walk >= Slide && Fast_Walk >= Slow_Walk){
        col += 3;
      }
      // if Slide is chosen
      else if(Slide >= Fast_Walk && Slide >= Slow_Walk){
        col -= 2;
      }
      // if slow Walk is chosen
      else if(Slow_Walk >= Fast_Walk && Slow_Walk >= Fast_Walk){
        col += 1;
      }
    }
    if(avatar == HAROLD){
      /*
        Sleep         20%     no move
        Big hop       10%     move 6 columns right
        Big slide     10%     move 4 columns left
        Small hop     40%     move 4 columns right
        Small slide   20%     move 2 columns left
      */
      float Sleep = 0.2*randomInt(10);
      float Big_hop = 0.1*randomInt(10);
      float Big_slide = 0.1*randomInt(10);
      float Small_hop = 0.4*randomInt(10);
      float Small_slide = 0.2*randomInt(10);

      // if Sleep is chosen
      if(Sleep >= Big_hop && Sleep >= Big_slide && Sleep >= Small_hop && Sleep >= Small_slide){
        col = col;
      }
      // if Big hop is chosen
      if(Big_hop >= Sleep && Big_hop >= Big_slide && Big_hop >= Small_hop && Big_hop >= Small_slide){
        col += 6;
      }
      // if Big slide is chosen
      if(Big_slide >= Sleep && Big_slide >= Big_hop && Big_slide >= Small_hop && Big_slide >= Small_slide){
        col -= 4;
      }
      // if Small hop is chosen
      if(Small_hop >= Sleep && Small_hop >= Big_hop && Small_hop >= Big_slide && Small_hop >= Small_slide){
        col += 4;
      }
      // if Small slide is chosen
      if(Small_slide >= Sleep && Small_slide >= Big_hop && Small_slide >= Big_slide && Small_slide >= Small_hop){
        col -= 2;
      }
    }
    if(col > MAX_COL){
      col = MAX_COL - 1;
    }
    if(col < 0){
      col = 0;
    }
    moveInHollow(avatar, MAX_ROW-1,oldCol, MAX_ROW-1, col, hollow);
    return col;
}

void moveBird(int index, int birdsRow[MAX_BIRDS], int birdsCol[MAX_BIRDS], char hollow[MAX_ROW][MAX_COL]){
  int r = birdsRow[index];
  int c = birdsCol[index];
  // the bird moves in a downward direction from its current row in the Hollow by a randomly determined one or two rows
  r += randomInt(2)+1;
  if(r > MAX_ROW){
    r = MAX_ROW;
  }
  // the bird moves from its current column by a randomly determined one column to the left, or one column to the right, or stays in the same column
  c += randomInt(3)-1;
  if(c > MAX_COL){
    c = MAX_COL;
  }
  moveInHollow(BIRD, birdsRow[index], birdsCol[index], r,c ,hollow);
  birdsRow[index] = r;
  birdsCol[index] = c;
}

int newBird(int birdsRow[MAX_BIRDS], int birdsCol[MAX_BIRDS],int no_of_birds){
  float yes = 0.9*randomInt(10);
  float no = 0.1*randomInt(10);
  if(yes >= no){
    birdsRow[no_of_birds+1] = 0;
    birdsCol[no_of_birds+1] = randomInt(MAX_COL);
    return 1;
  }else{
    return 0;
  }
}