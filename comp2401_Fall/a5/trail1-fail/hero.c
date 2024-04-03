/*
	This is the Source file
	containing code for the Creation and management of hero
*/
#include "defs.h"

void initHero(HeroType **Hero, char avartar, int col, char *name); //
void addHero(HeroArrayType *array, HeroType *element);			   //
void moveHero(HeroType *, EscapeType *);//
int heroIsSafe(HeroType *);//
void incurDamage(HeroType *, FlyerType *);//

void initHero(HeroType **Hero, char avartar, int col, char *name)
{
	HeroType *hero = (HeroType *)malloc(sizeof(HeroType));
	hero->dead = C_FALSE;
	hero->health = MAX_HEALTH;
	//   fprintf(hero->name,"%s",name);
	strcpy(hero->name, name);
	hero->partInfo.avatar = avartar;
	hero->partInfo.pos.col = col;
	hero->partInfo.pos.row = MAX_ROW - 1; // alway in last row
	*Hero = hero;
}


void addHero(HeroArrayType *array, HeroType *element)
{
	HeroType **new = (HeroType **)malloc(sizeof(HeroType *) * array->size);
	for (int i = 0; i < array->size; i++)
	{
		new[i] = array->elements[i];
	}
	new[array->size] = element;
	array->size++;
	array->elements = new;
}

void moveHero(HeroType *hero, EscapeType *esc){
	if(hero->partInfo.pos.col >= MAX_COL){
		return;// because hero already escaped the hollow
	}
	if (hero->dead == C_TRUE)
	{
		return;// hero is dead
	}
	
	int movement;
	if (hero->partInfo.avatar == TIMMY)
	{
		int probality[] = {5,3,2};
		int action[] = {2,-1,1};
		movement = ProbableOutcome(probality,action,3);
	}else{
		int probality[] = {2,1,1,4,2};
		int action[] = {0,5,-4,3,2};
		movement = ProbableOutcome(probality,action,3);
	}
	hero->partInfo.pos.col += movement;
	printf("\n%d\n",movement);
	setPos(&hero->partInfo.pos,hero->partInfo.pos.row,movement);
	for (int i = 0; i < esc->heroes.size; i++)
	{
		if(hero == esc->heroes.elements[i]){
			*esc->heroes.elements[i] = *hero;
			break;
		}
	}

}

int heroIsSafe(HeroType * hero){
	if(hero->dead == C_TRUE){
		return C_FALSE;
	}else{
		return C_TRUE;
	}
}

void incurDamage(HeroType *hero, FlyerType *flyer){
	hero->health -= flyer->strength;
	if(hero->health <= 0){
		hero->health = 0;
		hero->dead = C_TRUE;
		hero->partInfo.avatar = GRAVE;
	}
}
