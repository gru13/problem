#include"defs.h"

/* top-level function for serializing hollow, printing and sending it
   to client */
void outputHollow(EscapeType *)
{
}

/* initializes 2D grid with participant avatars in current positions */
void initHollow(EscapeType *escape, char Hollow[][MAX_COL])
{
  int row, col;
  char avatar;
  // creating empty hollow
  for (int i = 0; i < MAX_ROW; i++){
    for (int j = 0; j < MAX_COL; j++){
      Hollow[i][j] = SPACE;
    }
  }
  // fitting the flyers
  for (int i = 0; i < escape->flyers.size; i++){
    row = escape->flyers.elements[i]->partInfo.pos.row;
    col = escape->flyers.elements[i]->partInfo.pos.col;
    avatar = escape->flyers.elements[i]->partInfo.avatar;

    if (row < MAX_ROW && row >= 0 && col < MAX_COL && col >= 0){
      Hollow[row][col] = avatar;
    }
  }
  // fitting the heroes
  for (int i = 0; i < escape->heroes.size; i++){
    row = escape->heroes.elements[i]->partInfo.pos.row;
    col = escape->heroes.elements[i]->partInfo.pos.col;
    avatar = escape->heroes.elements[i]->partInfo.avatar;
    Hollow[row][col] = avatar;
  }
}

/* constructs 1D array with formatted Hollow output, containing all avatars
   in their positions, with borders, spacing and newlines */
void serializeHollow(EscapeType *escape, char *message)
{
  char Hollow[MAX_ROW][MAX_COL];
  int a = 0;
  initHollow(escape, Hollow);
  
  
  for (int i = 0; i < G_COL; i++){message[a] = '-';a++;}message[a]='\n';a++;// drawing border
  
  for (int i = 0; i < MAX_ROW ; i++){
    message[a] = '|';a++;
    for (int j = 0; j < MAX_COL; j++){
      message[a] = Hollow[i][j];
      a++;
    }
    message[a] = '|';a++;
    message[a] = '\n';a++;
  }
  
  for (int i = 0; i < G_COL; i++){message[a] = '-';a++;}message[a]='\n';a++; // drawing border

  // updating the heroes record
  char health[MAX_BUFF];
  sprintf(health, "THE HEALTH OF HEROES\nTIMMY  : %02d / 20\nHAROLD : %02d / 20\n",
  escape->heroes.elements[0]->health,escape->heroes.elements[0]->health);
  for (int i = 0;i<strlen(health);i++){message[a]=health[i];a++;}
  for (int i = 0; i < G_COL; i++){message[a] = '-';a++;}message[a]='\n';a++;// drawing border
}

void setPos(PositionType *pos, int row, int col){
  if (row >= MAX_ROW)
  {
    row = MAX_ROW - 1;
  }
  if (row < 0)
  {
    row = 0;
  }
  if (col >= MAX_COL)
  {
    col = MAX_COL - 1;
  }
  if (col < 0)
  {
    col = 0;
  }
  pos->row = row;
  pos->col = col;
}