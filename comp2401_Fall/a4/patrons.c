/*
    patrons.c : initPatronArray(), addPatron(), findPatron(), printPatrons(),cleanupPatronArray()
*/
#include "defs.h"
#include<stdio.h>


void initPatronArray(PatronArrayType *arr);
void addPatron(PatronArrayType *arr, char *n);
int findPatron(PatronArrayType *arr, int id, PatronType **p);
void printPatrons(PatronArrayType *arr);
void cleanupPatronArray(PatronArrayType *arr);

// Extra function
void removePatron(PatronArrayType* arr, int pId);


void initPatronArray(PatronArrayType *arr)
{
    arr->size = 0;
    arr->nextId = arr->size+PATRON_IDS;
}

void addPatron(PatronArrayType *arr, char *n)
{
    if(arr->size>=MAX_CAP){
        return;
    }
    strcpy(arr->elements[arr->size].name,n);
    arr->elements[arr->size].id = arr->nextId;
    arr->nextId++;
    arr->size++;
    return;
}

// Extra funtion (remove a patron if there)
void removePatron(PatronArrayType* arr, int pId){
    if(arr->size == 0){
        printf("--------------------ERROR--------------------\n");
        printf("Number of patron is zero\n");
        printf("---------------------------------------------\n");
        return;
    }
    PatronType* pat;
    int Valid = findPatron(arr,pId,&pat);
    if(Valid == C_NOK){
        printf("--------------------ERROR--------------------\n");
        printf("Not a valid Patron Id (%d)\n",pId);
        printf("---------------------------------------------\n");
        return;
    }
    printf("Patron Detail:\n");
    printf("---------------------------------------------\n");
    printf("Patron Name : %s\n", pat->name);
    printf("Patron id : %d\n",pat->id);
    printf("---------------------------------------------\n");
    int isFound = 0;
    for(int i =0 ;i<arr->size-1;i++){
        if(arr->elements[i].id == pId || isFound == 1 ){
            arr->elements[i] = arr->elements[i+1];
            isFound=1;
        }
    }
    arr->size--;
}

int findPatron(PatronArrayType *arr, int id, PatronType **p)
{
    for (int i = 0; i < arr->size; i++)
    {
        if(arr->elements[i].id == id){
            *p = &arr->elements[i];
            return C_OK;
        }
    }
    return C_NOK;
}

void printPatrons(PatronArrayType *arr)
{
    printf("\nPatrons:\n");
    for(int i = 0;i<arr->size;i++){
        printf("---------------------------------------------\n");
        printf("%d.\n",i+1);
        printf("---------------------------------------------\n");
        printf("Name : %s\n",arr->elements[i].name);
        printf("id   : %d\n",arr->elements[i].id);
        printf("---------------------------------------------\n");
    }
}

void cleanupPatronArray(PatronArrayType *arr)
{
    for(int i = 0;i<arr->size;i++){
        free(&arr->elements[i]);
    }
    free(&arr->size);
    free(&arr->nextId);
    free(&arr->elements);
    free(arr);
}
