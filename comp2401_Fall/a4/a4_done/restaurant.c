// restaurant.c : initRestaurant(), createResv(), printResByPatron(),cleanupRestaurant(), validateResvTime()
#include<stdio.h>
#include "defs.h"

#define CURYEAR 2023

void initRestaurant(RestaurantType *r, char *n);
int validateResvTime(int yr, int mth, int day, int hr, int min);
void createResv(RestaurantType *r, int pId, int yr, int mth, int day,int hr, int min);
void printResByPatron(RestaurantType *r, int id);
void cleanupRestaurant(RestaurantType *r);


void initRestaurant(RestaurantType *res, char *n){
    PatronArrayType* pat_array;
    ResvListType* res_array;
    pat_array = (PatronArrayType*)malloc(sizeof(PatronArrayType)*MAX_CAP);
    res_array = (ResvListType*)malloc(sizeof(ResvListType)*MAX_CAP);
    sprintf(res->name,"%s",n);
    initPatronArray(pat_array);
    initResvList(res_array);
    res->patrons = *pat_array;
    res->reservations = *res_array;
}

int validateResvTime(int yr, int mth, int day, int hr, int min){
    if(!(yr == CURYEAR || yr == CURYEAR+1)){
        return C_NOK;
    }
    if(mth <= 0 || mth > 12){
        return C_NOK;
    }
    if(day <= 0 || day > 31){
        return C_NOK;
    }
    if(hr < 9 || hr > 22){
        return C_NOK;
    }
    if(min < 0 || min > 60){
        return C_NOK;
    }
    return C_OK;

}

void createResv(RestaurantType *r, int pId, int yr, int mth, int day,int hr, int min){
    int Valid = validateResvTime(yr,mth,day,hr,min);
    if(Valid == C_NOK){
        printf("--------------------ERROR--------------------\n");
        printf("Not a valid Reservation time (on %2d/%2d/%4d time %2d:%2d)\n",day,mth,yr,hr,min);
        printf("---------------------------------------------\n");
        return;
    }
    PatronType* pat;
    Valid = findPatron(&r->patrons,pId,&pat);
    if(Valid == C_NOK){
        printf("--------------------ERROR--------------------\n");
        printf("Not a valid Patron Id (%d)\n",pId);
        printf("---------------------------------------------\n");
        return;
    }
    ResvTimeType* newResT;
    initResvTime(&newResT,yr,mth,day,hr,min);
    ResvType* newResv;
    initResv(&newResv,pat,newResT);
    addResv(&r->reservations,newResv);
}

void printResByPatron(RestaurantType *r, int id){
    NodeType* temp = r->reservations.head;
    int i = 1;
    while (temp != NULL)
    {
        if(temp->data->patron->id == id){
            printf("\n%d\n",i);
            i++;
            printReservation(temp->data);
        }
        temp = temp->next;
    }
}

void cleanupRestaurant(RestaurantType *r){
    cleanupPatronArray(&r->patrons);
    cleanupResvList(&r->reservations);
    free(r->name);
    free(r);
}