#include "defs.h"

void runEscape();//
int escapeIsOver(EscapeType*);//
void handleEscapeResult(EscapeType*);
void cleanupEscape(EscapeType*);//
void initEscape(EscapeType*);//

void cleanupEscape(EscapeType* escape){
    for (int i = 0; i < escape->heroes.size; i++) {
        free(escape->heroes.elements[i]);
    }
    free(escape->heroes.elements);

    // Clean up flyers
    for (int i = 0; i < escape->flyers.size; i++) {
        free(escape->flyers.elements[i]);
    }

}

void initEscape(EscapeType* escape){
    srand((unsigned)time(NULL));

    // server creation
    setupServerSocket(&escape->listenSocket);
    printf("\nServer Created \n");
    // connection with client sockect
    printf("Server is listening for client connection...\n");
    acceptConnection(escape->listenSocket,&escape->viewSocket);
    // flyer are initilaized 
    escape->flyers.size = 0;
    for(int i =0 ;i<MAX_ARR;i++){
        escape->flyers.elements[i] = NULL;
    }
    // initializing heroes
    escape->heroes.size = 0;
    escape->heroes.elements = (HeroType**)malloc(sizeof(HeroType*)*MAX_ARR);
    int col1,col2;
    do{
        col1 = randomInt(5);
        col2 = randomInt(5);

    }while(col2 == col1);
    HeroType* a = (HeroType*)malloc(sizeof(HeroType));
    HeroType* b = (HeroType*)malloc(sizeof(HeroType));
    initHero(&a,TIMMY,col1,"TIMMY");
    initHero(&b,HAROLD,col2,"Harold");
    addHero(&escape->heroes,a);
    addHero(&escape->heroes,b);
}

int escapeIsOver(EscapeType* escape){
    for (int i = 0; i < escape->heroes.size; i++){
        HeroType* hero = escape->heroes.elements[i];
        if(hero->partInfo.pos.col < MAX_COL && hero->dead != C_TRUE){
            return C_FALSE;
        }
    }
    return C_TRUE;
   
}


void runEscape(){
    EscapeType escape;
    initEscape(&escape);
    do{
        // creation new flyer
        if(randomInt(100) < BIRD_SPAWN_RATE){
            spawnFlyer(&escape, BIRD,randomInt(3)+3,randomInt(5),randomInt(MAX_COL));
        } 
        if (randomInt(100) < MONKEY_SPAWN_RATE){
            spawnFlyer(&escape, MONKEY, randomInt(4)+8, randomInt(MAX_ROW),randomInt(MAX_COL));
        }        
        // movement of heroes
        for (int i = 0; i < escape.heroes.size; i++){
            moveHero(escape.heroes.elements[i],&escape);
        }
        // movement of flyer
        for(int i =0 ;i<escape.flyers.size; i++){
            FlyerType* flyer = escape.flyers.elements[i];
            if(flyer == NULL){continue;}
            moveFlyer(flyer,&escape);
            HeroType* collison = checkForCollision(&flyer->partInfo.pos,&escape);
            if(collison != NULL){
                incurDamage(collison,flyer);
            }
        }
        outputHollow(&escape);
        // printf("%d-%d\n",escape.heroes.elements[0]->partInfo.pos.col,escape.heroes.elements[1]->partInfo.pos.col);
    }while(escapeIsOver(&escape) != C_TRUE);
    handleEscapeResult(&escape);
}

void handleEscapeResult(EscapeType* escape){
    char message[MAX_BUFF];
    
    char Hollow[MAX_ROW][MAX_COL];
    char Health[MAX_BUFF];  
    initHollow(escape,Hollow);
    int a = 0;// this contain the index of message

    for(int i =0 ;i< MAX_COL+2 ;i++){message[a] = '-';a++;}message[a]='\n';a++;
    sprintf(Health,"|                   DRAGON HOLLOW RESULT                     |\n");
    // sprintf(Health,"|                       DRAGON HOLLOW                        |\n");
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
    sprintf(Health,"|                THE STATUS OF HEROES                        |\n");
    for(int i = 0 ;i < strlen(Health);i++){message[a] = Health[i];a++;}
    for(int i = 0; i < MAX_COL+2 ;i++){message[a] = '-';a++;}message[a]='\n';a++;


    sprintf(Health,"|THE HEALTH OF HEROES:          |LIFE:                       |\n");
    for(int i = 0 ;i < strlen(Health);i++){message[a] = Health[i];a++;}
    sprintf(Health,"|                               |                            |\n");
    for(int i = 0 ;i < strlen(Health);i++){message[a] = Health[i];a++;}


    for(int i = 0 ;i<escape->heroes.size;i++){
        char dead[6];
        if(escape->heroes.elements[i]->dead == C_TRUE){
            strcpy(dead,"DEAD"); 
        }else{
            strcpy(dead,"ALIVE"); 
        }
        sprintf(Health,"|%6s : %2d / 20               |%6s : %5s              |\n",escape->heroes.elements[i]->name,escape->heroes.elements[i]->health,escape->heroes.elements[i]->name,dead);
        for (int j = 0; j < strlen(Health); j++){message[a] = Health[j];a++;}   
    }
    
    
    for(int i = 0 ;i< MAX_COL+2 ;i++){message[a] = '-';a++;}message[a]='\n';a++;
    
    
    message[a] = '\0';
    // send the data to client
    printf("%s\n",message);
    sendData(escape->viewSocket,message);
    usleep(OUTPUT_INTERVAL);
    // quit message
    sendData(escape->viewSocket,"quit\0");
    cleanupEscape(escape);
    return;
}