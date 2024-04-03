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
#define DONE 'D'
#define WAIT_TIME 10 // in millisecond


void initHollow(char[MAX_ROW][MAX_COL]);//
void printHollow(char[MAX_ROW][MAX_COL]);//
char escapeOver(char, char, int, int);//
char isDone(char, int);//
int  moveHero(char, int, char[MAX_ROW][MAX_COL]);
void moveBird(int, int[MAX_BIRDS], int[MAX_BIRDS], char[MAX_ROW][MAX_COL]);
void moveInHollow(char, int, int, int, int, char[MAX_ROW][MAX_COL]);
void printResult(char, char, int, int);//
int  randomInt(int);//

void new_Bird(int[MAX_BIRDS], int[MAX_BIRDS], char[MAX_ROW][MAX_COL]);
void initBirds(int[MAX_BIRDS], int[MAX_BIRDS]);

int main()
{
  srand(time(NULL));

  int Bird_Row[MAX_BIRDS];
  int Bird_Col[MAX_BIRDS];
  char Hollow[MAX_ROW][MAX_COL];
  int Tcol = 0;//Timmy column Location
  int Hcol = 0;//Harold column location
  int temp = 0;
  int H_Col_Dead = -1;
  int T_Col_Dead = -1;
  initHollow(Hollow);
  initBirds(Bird_Row, Bird_Col);

  while(escapeOver(HAROLD,TIMMY,Hcol,Tcol) != DONE){
    printHollow(Hollow);
    usleep(WAIT_TIME*100000);
    system("cls");
    if(isDone(HAROLD, Hcol) != DONE ){
      temp = moveHero(HAROLD,Hcol,Hollow);
      if(temp > 0 && temp < MAX_COL){
        if(Hollow[MAX_ROW-1][temp] != DEAD){
          moveInHollow(HAROLD, MAX_ROW-1,Hcol, MAX_ROW-1, temp, Hollow);//still in hollow
        }
      }else{
        Hollow[MAX_ROW-1][Hcol] = SPACE;// escaped
      }
      Hcol = temp;
    }
    if(isDone(TIMMY, Tcol) != DONE){
      temp = moveHero(TIMMY,Tcol,Hollow);
      if(temp > 0 && temp < MAX_COL){
        if(Hollow[MAX_ROW-1][temp] != DEAD){
          moveInHollow(TIMMY, MAX_ROW-1,Tcol, MAX_ROW-1, temp, Hollow);//still in hollow
        }

      }else{
        Hollow[MAX_ROW-1][Tcol] = SPACE;// escaped
      }
      Tcol = temp;
    }
    new_Bird(Bird_Row, Bird_Col, Hollow);
    for(int i = 0;i<MAX_BIRDS;i++){
      if(Bird_Row[i] < MAX_BIRDS && Bird_Col[i] < MAX_BIRDS){
        moveBird(i, Bird_Row, Bird_Col,Hollow);
        if(Bird_Row[i] == MAX_ROW-1){
          if(Bird_Col[i] == Hcol){
            Hollow[MAX_ROW-1][Hcol]=DEAD;
            T_Col_Dead = Hcol;
            Hcol = -1;
          }
          if(Bird_Col[i] == Tcol){
            Hollow[MAX_ROW-1][Tcol]=DEAD;
            T_Col_Dead = Tcol;
            Tcol = -1;
          }
        }
      }
      else{
        Bird_Row[i] = MAX_BIRDS;
        Bird_Col[i] = MAX_BIRDS;
      }
      if(H_Col_Dead >= 0){
        Hollow[MAX_ROW-1][H_Col_Dead] = DEAD;
      }
      if(T_Col_Dead >= 0){
        Hollow[MAX_ROW-1][T_Col_Dead] = DEAD;
      }
    }
  }
  printHollow(Hollow);
  printResult(HAROLD,TIMMY,Hcol,Tcol);
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

void initHollow(char hollow[MAX_ROW][MAX_COL]){
  for(int i =0;i<MAX_ROW;i++){
    for(int j = 0;j<MAX_COL;j++){
      hollow[i][j] = SPACE;
    }
  }
}

void printHollow(char hollow[MAX_ROW][MAX_COL]){
  printf("------------------------------------------------------------\n");
  for(int i = 0;i<MAX_ROW;i++){
    printf("|");
    for(int j = 0;j<MAX_COL;j++){
      printf("%c", hollow[i][j]);
    }
    printf("|\n");
  }
  printf("------------------------------------------------------------\n");
}

char isDone(char avatar, int col){
  // col < 0 -> dead
  // col >= MAX_COL -> escaped
  if(col < 0 || col >= MAX_COL){
    return DONE;
  }
  else{
    return !DONE;
  }
}

char escapeOver(char H, char T, int Hcol, int Tcol){
  if(isDone(H, Hcol) == DONE && isDone(T, Tcol) == DONE){
    return DONE;
  }
  else{
    return !DONE;
  }
}


void printResult(char H, char T, int Hcol, int Tcol){
  if(Hcol < 0){
    printf("\nHAROLD is DEAD");
  }else if(Hcol >= MAX_COL){
    printf("\nHAROLd Escaped");
  }
  if(Tcol < 0){
    printf("\nTimmy is DEAD");
  }else if(Tcol >= MAX_COL){
    printf("\nTimmy Escaped");
  }
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
    if(col < 0){
      col = 0;
    }
    return col;
}

void new_Bird(int Row[MAX_BIRDS], int Col[MAX_BIRDS],char hollow[MAX_ROW][MAX_COL]){
  float yes = BIRD_FREQ*randomInt(10);
  float no = 10*randomInt(10);
  if(yes >= no){
    for(int i = 0;i<MAX_BIRDS;i++){
      if(Row[i] == MAX_BIRDS && Col[i] == MAX_BIRDS){
        Row[i] = 0;
        Col[i] = randomInt(MAX_COL);
        hollow[Row[i]][Col[i]] = BIRD;
      }
    }
  }
}

void initBirds(int ROw[MAX_BIRDS],int COl[MAX_BIRDS]){
  for(int i = 0;i<MAX_BIRDS;i++){
    ROw[i]= MAX_BIRDS;
    COl[i]= MAX_BIRDS;
  }
}

void moveBird(int index, int row[MAX_BIRDS], int col[MAX_BIRDS], char hollow[MAX_ROW][MAX_COL]){
  if(row[index] >= MAX_ROW && col[index] >= MAX_COL){
    return;
  }
  hollow[row[index]][col[index]] = SPACE;
  int r = row[index] + randomInt(2) + 1;
  int c = col[index] + randomInt(3) - 1;
  if(c > MAX_COL){
    c = MAX_COL-1;
  }
  if(c<0){
    c = 0;
  }
  if(r >= MAX_BIRDS-1){
    row[index] = MAX_BIRDS;
    col[index] = MAX_BIRDS;
  }else{
    row[index] = r % MAX_ROW;
    col[index] = c % MAX_COL;
    if(hollow[r][c] != DEAD){
      hollow[r][c] = BIRD;
    }
  }
}