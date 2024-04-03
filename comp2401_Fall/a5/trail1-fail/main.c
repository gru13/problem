#include "defs.h"




int randomInt(int max);
int ProbableOutcome(int *arrP, int *arrA, int len);

void outputHollow(EscapeType *);
void initHollow(EscapeType *, char[][MAX_COL]);
void serializeHollow(EscapeType *, char *);
void setPos(PositionType *, int, int);

int main(int argc, char *argv[]){
  srand((unsigned)time(NULL));
  EscapeType escape;
  initEscape(&escape);
  char message[MESSAGE_SIZE];
  serializeHollow(&escape, message);printf("%s\n%2d-%2d\n",message,escape.heroes.elements[0]->partInfo.pos.col,escape.heroes.elements[1]->partInfo.pos.col);
 
  // moveHero(escape.heroes.elements[0],&escape);
  // serializeHollow(&escape, message);printf("%s\n%2d-%2d\n",message,escape.heroes.elements[0]->partInfo.pos.col,escape.heroes.elements[1]->partInfo.pos.col);
  // moveHero(escape.heroes.elements[1],&escape);
  // serializeHollow(&escape, message);printf("%s\n%2d-%2d\n",message,escape.heroes.elements[0]->partInfo.pos.col,escape.heroes.elements[1]->partInfo.pos.col);
  
  for(int i =0;i<100;i++){
    moveHero(escape.heroes.elements[0],&escape);
    serializeHollow(&escape, message);printf("%s\n%2d-%2d\n",message,escape.heroes.elements[0]->partInfo.pos.col,escape.heroes.elements[1]->partInfo.pos.col);
    moveHero(escape.heroes.elements[1],&escape);
    serializeHollow(&escape, message);printf("%s\n%2d-%2d\n",message,escape.heroes.elements[0]->partInfo.pos.col,escape.heroes.elements[1]->partInfo.pos.col);
  }
  
  return (0);
}

int randomInt(int max){
  return (rand() % max);
}

/*
Probality Choser
input:
int array => arrP => probality value
int array => arrA => action according to the chossen probality
int len => length of array
Output:
int index =>the Outcome choice from the array
*/
int ProbableOutcome(int *arrP, int *arrA, int len){
  int index = 0, max_val = INT_MIN;
  int arr[len];
  for (int i = 0; i < len; i++)
  {
    arr[i] = arrP[i] * randomInt(10);
    if (arr[i] > max_val)
    {
      max_val = arr[i];
      index = i;
    }
  }
  return arrA[index];
}


