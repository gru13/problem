#include "defs.h"
#include<string.h>
/*
books.c : initBook(), initBookArray(), addBookToArray(), findInsPt(),
          printBook(),printBookArray(), cleanupBookArray()

*/

void initBook(BookType*, int, char*, char*, int, float);//
void initBookArray(BookArrayType*, OrderType);//

int  addBookToArray(BookArrayType*, BookType*);//
int  findInsPt(BookArrayType*, BookType*, int*);//

void printBook(BookType*);//
void printBookArray(BookArrayType*);//
void cleanupBookArray(BookArrayType*);//

void initBook(BookType *b, int id, char *t, char *a, int y, float r){
    b->id = id;
    b->year = y;
    b->rating = r;
    strcpy(b->author,a);
    strcpy(b->title,t);
}

void initBookArray(BookArrayType *arr, OrderType o){
    arr->order = o;
    arr->size = 0;
}

void printBook(BookType* b){
    printf("\n-----------------------------------\n");
    printf("title  : %s\n",b->title);
    printf("id     : %d\n",b->id);
    printf("author : %s\n",b->author);
    printf("rating : %.2f\n",b->rating);
    printf("year   : %d\n",b->year);
    printf("\n-----------------------------------\n");
}

void printBookArray(BookArrayType* arr){
    for(int i=0;i<arr->size;i++){
        printf("\n%d\n",i+1);
        printBook(arr->elements[i]);
    }
}

void cleanupBookArray(BookArrayType* arr){
    for(int i =0 ;i<arr->size;i++){
        free(arr->elements[i]);
    }
    arr->size = 0;
}


int addBookToArray(BookArrayType *arr, BookType *b){
    if(arr->size >= MAX_CAP){
        return 1;
    }
    int index;
    findInsPt(arr, b, &index);
    for(int i = arr->size;i>index;i--){
        arr->elements[i] = arr->elements[i-1];
    }
    arr->elements[index] = b;
    arr->size++;
    return 0;
}

int findInsPt(BookArrayType *arr, BookType *b, int *insPt){
    int cmp,index = 0;

    if(arr->order == ORDER_BY_RATING){
        for(;index<arr->size;index++){
            if(b->rating > arr->elements[index]->rating){break;}
        }
    }else{
        for(;index<arr->size;index++){
            cmp = strcmp(b->author,arr->elements[index]->author);
            if(cmp<0){
                break;
            }else if(cmp == 0){
                cmp = strcmp(b->title, arr->elements[index]->title);
                if(cmp<0){
                    break;
                }
            }
        }

    }

    *insPt = index;
    return 0;
}
