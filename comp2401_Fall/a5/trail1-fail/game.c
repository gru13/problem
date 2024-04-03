#include "defs.h"

void runEscape();
void initEscape(EscapeType* escape);
int escapeIsOver(EscapeType* );
void handleEscapeResult(EscapeType*);
void cleanupEscape(EscapeType*);

void initEscape(EscapeType* escape){
	escape->flyers.size=0;
	escape->heroes.size=0;

	for(int i =0;i<MAX_ARR;i++){
		escape->flyers.elements[i] = NULL;
	}
	int loc_a,loc_b;
	do{
		loc_a = randomInt(5);
		loc_b = randomInt(5);
	} while (loc_a == loc_b);
	
	HeroType* a; initHero(&a,TIMMY,loc_a,"Timmy");
	// void initHero(HeroType **Hero, char avartar, int col, char *name)
	HeroType* b; initHero(&b,HAROLD,loc_b,"Harold");
	
	addHero(&escape->heroes,a);
	addHero(&escape->heroes,b);
}
