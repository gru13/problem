#include "defs.h"

void initHero(HeroType**, char, int, char*);//
void addHero(HeroArrayType*, HeroType*);//
void moveHero(HeroType*, EscapeType*);//
int heroIsSafe(HeroType*);//
void incurDamage(HeroType*, FlyerType*);//


void initHero(HeroType** hero, char avatar, int col, char* name){
    HeroType *H = (HeroType*)malloc(sizeof(HeroType));
    H->dead = C_FALSE;
    H->health = MAX_HEALTH;
    H->partInfo.avatar = avatar;
    sprintf(H->name, "%s", name);
    H->partInfo.pos.row = MAX_ROW - 1;
    H->partInfo.pos.col = col;
    *hero = H;
}

void addHero(HeroArrayType* arr, HeroType* hero){
    if(arr->size >= MAX_ARR){
        return;
    }
    arr->elements[arr->size] = hero;
    arr->size++;
}

void moveHero(HeroType* hero, EscapeType* esc){
    if(hero->partInfo.pos.col >= MAX_COL){return;}// because hero already escaped the hollow
	if (hero->dead == C_TRUE){return;}// hero is dead
	
	int movement;
	if (hero->partInfo.avatar == TIMMY)
	{
		int probality[] = {5,3,2};
		int action[] = {2,-1,1};
		movement = ProbableOutcome(probality,action,3);
	}else{
		int probality[] = {2,1, 1,4,2};
		int action[]    = {0,5,-4,3,2};
		movement = ProbableOutcome(probality,action,5);
	}
	hero->partInfo.pos.col += movement;
	for (int i = 0; i < esc->heroes.size; i++)
	{
		if(hero == esc->heroes.elements[i]){
			*esc->heroes.elements[i] = *hero;
			break;
		}
	}

}

int heroIsSafe(HeroType* hero){
	if(hero->dead == C_FALSE  && hero->partInfo.pos.col >= MAX_COL){
		return C_TRUE;
	}
	return C_FALSE;
}
void incurDamage(HeroType* hero, FlyerType* flyer){
	if(hero == NULL || flyer == NULL){return;}
	if(heroIsSafe(hero) == C_TRUE){return;}//hero escaped
	if(hero->dead == C_TRUE){return;}//hero died
	if(flyer->partInfo.pos.row != MAX_ROW-1){return;}//not in same row
	if(flyer->partInfo.pos.col != hero->partInfo.pos.col){return;}// not in col
	hero->health -= flyer->strength;
	if(hero->health <= 0){
		hero->dead = C_TRUE;
		hero->health = 0;
		hero->partInfo.avatar = GRAVE;
	}
}