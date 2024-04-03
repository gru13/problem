/**
 *   resv.c : initResvList(), initResv(), initResvTime(), addResv(), lessThan(),printReservations(), printReservation(), cleanupResvList()
 **/

#include "defs.h"

void initResvList(ResvListType *);//
void initResvTime(ResvTimeType **, int , int , int , int ,int );//
void initResv(ResvType **, PatronType *, ResvTimeType *);//
int lessThan(ResvTimeType *, ResvTimeType *);//
void addResv(ResvListType *, ResvType *);//
void printReservation(ResvType *);//
void printReservations(ResvListType *);//
void cleanupResvList(ResvListType *);//

//extra
void initNode(NodeType** node,ResvType *data);//


void initResvList(ResvListType *list){
    list->head = NULL;
    list->nextId = RES_IDS;
}

void initResvTime(ResvTimeType **rt, int yr, int mth, int day, int hr,int min){
    ResvTimeType* r_t = (ResvTimeType*)malloc(sizeof(ResvTimeType));
    r_t->year=yr;
    r_t->month=mth;
    r_t->day = day;
    r_t->hours = hr;
    r_t->minutes = min;
    *rt = r_t;
}

void initResv(ResvType **r, PatronType *p, ResvTimeType *rt){
    ResvType* r_t = (ResvType*)malloc(sizeof(ResvType));
    r_t->patron = p;
    r_t->resvTime = rt;
    *r = r_t;
}

//Extra function
void initNode(NodeType** node,ResvType *data){
    NodeType* new = (NodeType*)malloc(sizeof(NodeType));
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
    *node = new;
}

int lessThan(ResvTimeType *r1, ResvTimeType *r2){
    if(r1->year > r2->year){
        return C_FALSE;
    }
    if(r1->month > r2->month){
        return C_FALSE;
    }
    if(r1->day > r2->day){
        return C_FALSE;
    }
    if(r1->hours > r2->hours){
        return C_FALSE;
    }
    if(r1->minutes > r2->minutes){
        return C_FALSE;
    }
    return C_TRUE;
}

void addResv(ResvListType *list, ResvType *r){
    NodeType* tempHead = list->head;
    NodeType* new;
    initNode(&new, r);
    r->id = list->nextId;
    new->prev = tempHead;
    if(tempHead != NULL){
        while (tempHead->next != NULL)
        {
            tempHead = tempHead->next;
        }
        tempHead->next = new;
    }else{
        list->head = new;
    }
    list->nextId++;
}

void printReservation(ResvType *r){
    printf("---------------------------------------------\n");
    printf("Patron Name    : %s\n",r->patron->name);
    printf("Patron id      : %d\n",r->patron->id);
    printf("Reservation id : %d\n",r->id);
    printf("Booked time    : %2d:%2d\n",r->resvTime->hours,r->resvTime->minutes);
    printf("Booked day     : %2d/%2d/%4d\n",r->resvTime->day,r->resvTime->month,r->resvTime->year);
    printf("---------------------------------------------\n");
}

void printReservations(ResvListType *list){
    printf("---------------------------------------------\n");
    printf("----------------Reservations-----------------\n");
    printf("---------------------------------------------\n");
    int i = 1;
    NodeType* temp = (NodeType*)list->head;
    while(temp!=NULL){
        printf("%d\n",i);
        printReservation(temp->data);
        temp = temp->next;
        i++;
    }
}

void cleanupResvList(ResvListType *list){
    while(list->head->next != NULL){
        list->head = list->head->next;
        free(list->head->prev);
    }
    free(&list->nextId);
    free(list);
}
