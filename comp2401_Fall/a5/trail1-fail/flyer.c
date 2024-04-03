#include"defs.h"

void spawnFlyer(EscapeType*, char, int, int, int);
void addFlyer(FlyerArrayType*, FlyerType*);
void moveFlyer(FlyerType*, EscapeType*);
int  flyerIsDone(FlyerType*);


void spawnFlyer(EscapeType* escape, char avatar, int , int, int){
}


void addFlyer(FlyerArrayType* array , FlyerType* element){
    if(array->size >= MAX_ARR){
        return;
    }
    for(int i =0 ;i<=array->size;i++){
        if(array->elements[i] == NULL){
            *array->elements[i] = *element;
        }
    }
}

void moveFlyer(FlyerType* flyer, EscapeType* escape){
    if(flyerIsDone(flyer) == C_TRUE){
        for(int i =0;i<MAX_ARR;i++){
            if(flyer == escape->flyers.elements[i]){
                escape->flyers.elements[i] = NULL;
                escape->flyers.size--;
            }
        }
        return; 
    }
    int row = flyer->partInfo.pos.row;
    int col = flyer->partInfo.pos.col;
    if(flyer->partInfo.avatar == MONKEY){
        row += randomInt(7) - 3;
        int direction;computeHeroDir(escape,flyer,&direction);
        if(direction != 0){
            col += randomInt(3) + 1;
            col *= direction;
        }
    }else{
        row += 1;
        col += randomInt(2) - 1;
    }
    setPos(&flyer->partInfo.pos,row,col);

}


int  flyerIsDone(FlyerType* flyer){
    if(flyer->partInfo.pos.row >= MAX_ROW-1){
        return C_TRUE;
    }else{
        return C_FALSE;
    }
}


void computeHeroDir(EscapeType* escape, FlyerType* flyer, int* direction){
    int min_col = INT_MAX;
    int min_distance = INT_MAX;
    for (int i = 0; i < escape->heroes.size; i++){
        int x = escape->heroes.elements[i]->partInfo.pos.col - flyer->partInfo.pos.col;
        if(abs(x) < min_distance){
            min_distance = abs(x);
            min_col = x;
        }
    }
    if(min_col < 0){
        *direction = -1;
    }else if(min_col > 0){
        *direction = 1;
    }else{
        *direction = 0;
    }
}