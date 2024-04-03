#include "defs.h"
#include <limits.h>

void spawnFlyer(EscapeType*, char, int, int, int);//
void addFlyer(FlyerArrayType*, FlyerType*);//
void moveFlyer(FlyerType*, EscapeType*);//
void computeHeroDir(EscapeType*, FlyerType*, int*);//
int  flyerIsDone(FlyerType*);//
HeroType* checkForCollision(PositionType*, EscapeType*);//

void addFlyer(FlyerArrayType* arr, FlyerType* flyer){
    if(arr->size > MAX_ARR){
        return;
    }
    for (int i = 0; i < MAX_ARR; i++){
        if(arr->elements[i] == NULL){
            arr->elements[i] = flyer;
            arr->size++;
            break;
        } 
    }
}

void moveFlyer(FlyerType* flyer, EscapeType* escape){
    if(flyer == NULL){return;}
    if(flyerIsDone(flyer) == C_TRUE){
        for(int i =0 ;i < MAX_ARR;i++){
            if(escape->flyers.elements[i] == flyer){
                escape->flyers.elements[i] = NULL;
                escape->flyers.size--; 
            }
        }
    }
    int row,col,direction;
    if(flyer->partInfo.avatar == BIRD){
        row = flyer->partInfo.pos.row + 1;
        col = flyer->partInfo.pos.col + randomInt(3) - 1;
    }else if(flyer->partInfo.avatar == MONKEY){
        row = flyer->partInfo.pos.row + randomInt(7) - 3;
        computeHeroDir(escape,flyer,&direction);
        col = flyer->partInfo.pos.col + direction*(randomInt(2)+1);
    }
    setPos(&flyer->partInfo.pos,row,col);
}

void spawnFlyer(EscapeType* escape, char avatar, int strength, int row, int col){
    FlyerType* flyer = (FlyerType*)malloc(sizeof(FlyerType));
    flyer->strength = strength; 
    flyer->partInfo.avatar = avatar;
    flyer->partInfo.pos.row = row;
    flyer->partInfo.pos.col = col;
    addFlyer(&escape->flyers,flyer);
}

int  flyerIsDone(FlyerType* flyer){
    if(flyer->partInfo.pos.row == MAX_ROW-1){
        return C_TRUE;
    }else{
        return C_FALSE;
    }
}

HeroType* checkForCollision(PositionType* pos, EscapeType* escape){
    for(int i = 0;i<escape->heroes.size;i++){
        PositionType curP = escape->heroes.elements[i]->partInfo.pos;
        if(curP.col == pos->col && curP.row == pos->row){
            return escape->heroes.elements[i];
        }
    }
    return NULL;
}

void computeHeroDir(EscapeType* escape, FlyerType* flyer, int* direction){
    int minDist = INT_MAX;
    for (int i = 0; i < escape->heroes.size; i++){
        int colPos = escape->heroes.elements[i]->partInfo.pos.col;
        if(abs(colPos-flyer->partInfo.pos.col)<abs(minDist)){
            minDist = colPos-flyer->partInfo.pos.col;
        }
    }
    if(minDist == 0){
        *direction = DIR_SAME;
    }else if(minDist > 0){
        *direction = DIR_LEFT;
    }else{
        *direction = DIR_RIGHT;
    }
}