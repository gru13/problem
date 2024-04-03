#include "defs.h"

void outputHollow(EscapeType*);//
void initHollow(EscapeType*, char[][MAX_COL]);//
void serializeHollow(EscapeType*, char*);//
void setPos(PositionType*, int, int);//


void initHollow(EscapeType* escape, char Hollow[][MAX_COL]){
    int col,row;
    for (int i = 0; i < MAX_ROW; i++){
        for(int j = 0; j < MAX_COL; j++){
            Hollow[i][j] = SPACE;
        }
    }

    for(int i = 0; i < MAX_ARR; i++){
        if(escape->flyers.elements[i] == NULL){continue;}
        col = escape->flyers.elements[i]->partInfo.pos.col;
        row = escape->flyers.elements[i]->partInfo.pos.row;
        Hollow[row][col] = escape->flyers.elements[i]->partInfo.avatar;
    }
    
    for(int i = 0; i < escape->heroes.size; i++){
        col = escape->heroes.elements[i]->partInfo.pos.col;
        if(col >= MAX_COL && escape->heroes.elements[i]->dead != C_TRUE){continue;}
        if(escape->heroes.elements[i]->dead == C_TRUE){Hollow[MAX_ROW-1][col]=GRAVE;continue;}
        Hollow[MAX_ROW-1][col] = escape->heroes.elements[i]->partInfo.avatar;
    }

}

void serializeHollow(EscapeType* escape, char* message){
    char Hollow[MAX_ROW][MAX_COL];
    char Health[MAX_BUFF];  
    initHollow(escape,Hollow);
    int a = 0;// this contain the index of message

    for(int i =0 ;i< MAX_COL+2 ;i++){message[a] = '-';a++;}message[a]='\n';a++;
    sprintf(Health,"|                       DRAGON HOLLOW                        |\n");
    for(int i = 0 ;i < strlen(Health);i++){message[a] = Health[i];a++;}
    for(int i = 0;i < MAX_COL+2 ;i++){message[a] = '-';a++;}message[a]='\n';a++;

    for (int i = 0; i < MAX_ROW; i++){
        message[a] = '|';a++;
        for (int j = 0; j < MAX_COL; j++){
            message[a] = Hollow[i][j];
            a++;
        } 
        message[a] = '|';a++;
        message[a] = '\n';a++;
    }
    for(int i = 0; i < MAX_COL+2 ;i++){message[a] = '-';a++;}message[a]='\n';a++;
    sprintf(Health,"|THE HEALTH OF HEROES:                                       |\n");
    for(int i = 0 ;i < strlen(Health);i++){message[a] = Health[i];a++;}
    for(int i = 0 ;i<escape->heroes.size;i++){
        sprintf(Health,"|%6s : %2d / 20                                            |\n",escape->heroes.elements[i]->name,escape->heroes.elements[i]->health);
        for (int j = 0; j < strlen(Health); j++){message[a] = Health[j];a++;}   
    }
    for(int i = 0 ;i< MAX_COL+2 ;i++){message[a] = '-';a++;}message[a]='\n';a++;
    message[a] = '\0';
}

void setPos(PositionType* pos, int row, int col){
    if(row >= MAX_ROW){row = MAX_ROW-1;}
    if(row < 0){row = 0;}

    if(col >= MAX_COL){col = MAX_COL-1;}
    if(col < 0){col = 0;}

    pos->row = row;
    pos->col = col;
}

void outputHollow(EscapeType* escape){
    char message[MAX_BUFF];
    serializeHollow(escape, message);
    //send to client
    sendData(escape->viewSocket,message);
    printf("%s\n",message);
    usleep(OUTPUT_INTERVAL);
    system("clear");
}