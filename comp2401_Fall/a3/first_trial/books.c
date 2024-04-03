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
        printBook(arr->elements[i]);
    }
}

void cleanupBookArray(BookArrayType* arr){
    for(int i =0 ;i<arr->size;i++){
        free(arr->elements[i]);
    }
    arr->size = 0;
}

/*
Implement the int addBookToArray(BookArrayType *arr, BookType *b) function that stores
the given book directly into its correct position in the given book collection.
At all times, the book collection must be ordered as indicated by the order field: either in ascending
alphabetical order by author name, then by title for multiple books by the same author, or in de-
scending order by book rating. To add a book to the collection, first its correct insertion point must
be found, then the other books must be moved within the array to make room for it
The addBookToArray() function must be implemented as follows:

(a) check whether there is room in the array for the new book; if not, the book cannot be added, and an error flag must be returned

(b) find the insertion point for the new book by calling an existing function

(c) if the insertion point for the new book was found successfully, you must move each element one
    position towards the back (the end) of the array, from the last book down to the insertion point

    NOTE: the insertion of the new book requires “moving” the other books to make room for the
          new one; do not add to the end of the array and sort; do not use any sort function
          or sorting algorithm anywhere in this program

(d) store the new book into the array at the insertion point

(e) increase the size of the array

*/

int addBookToArray(BookArrayType *arr, BookType *b){
    if(arr->size >= MAX_CAP){
        return 1;
    }
    int index;
    findInsPt(arr, b, &index);
    // index = arr->size;
    for(int i = arr->size;i>index;i--){
        arr->elements[i] = arr->elements[i-1];
    }
    arr->elements[index] = b;
    arr->size++;
    return 0;
}
/*
Implement the int findInsPt(BookArrayType *arr, BookType *b, int *insPt)
function that searches an array to find the index where a new book should be inserted, as follows:

    (a) loop over the elements of the given array arr, with the goal of finding the index where the given
        book b belongs, so that the elements of the array remain in the correct order

    (b) if the array must be ordered by author, then find the array index where the new book belongs
        so that the array elements remain in ascending (increasing) alphabetical order by author; if the
        array contains multiple books by the same author, then these must be ordered by title

    (c) if the array must be ordered by rating, then find the array index where the new book belongs so
        that the array elements remain in descending (decreasing) numerical order by rating

    (d) when the insertion point is found, as an index in the given array where the new book belongs, it
        must be returned in the insPt parameter

    (e) if any error occurs, the function returns an error flag, provided in the base code as a constant,
        or it returns a success flag otherwise
*/
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
