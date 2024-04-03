#include "defs.h"
#include <stdio.h>
/*
club.c : initBookClub(), addBookToClub(), printBooks(), printTopRatedBooks()
*/

void initBookClub(BookClubType*, char*);//
int  addBookToClub(BookClubType*, int, char*, char*, char*, int, float);//
void printBooks(BookClubType*);//
void printTopRatedBooks(BookClubType*);

void initBookClub(BookClubType *club, char *n){
    strcpy(club->name, n);
    initBookArray(&club->books,ORDER_BY_AUTHOR);
    // initBookArray(&club->books,ORDER_BY_RATING);
}
void printBooks(BookClubType* club){
    printf("\n-----------------------------------\n");
    printf("BookClub : %s", club->name);
    printBookArray(&club->books);
}

/*
Implement the int addBookToClub(BookClubType *club, int id, char *t, char *af,
char *al, int y, float r) function that takes as parameters a new book id, title, author’s first
name, author’s last name, year of publication, and rating. The function then creates a new book and
adds it to the given book club’s collection. The function must do the following:
(a) validate the id and the year as positive numbers
(b) validate the rating to be in the range between 0 and 5, inclusively
(c) if any parameter is invalid, then the function returns an error flag
(d) create a single string for the author’s name, using sprintf(), so that the author’s name is stored
in the format "LastName, FirstName"
(e) dynamically allocate the memory for a new book, and initialize it by calling an existing function
with the correct information
(f) add the new book to the book club’s collection, using an existing function
(g) return an error flag if the book could not be added to the collection, or success otherwise

*/
int addBookToClub(BookClubType *club, int id, char *t, char *af,char *al, int y, float r){
    /*
        this Function vaildate the parameter if all are valid and the book is added to th club then this return 0;
        other wise error flag
        2 => id error
        3 => year error
        4 => rating error
    */
    if(id <= 0){
        return 2;
    }
    if(y <= 0){
        return 3;
    }
    if(!(r>=0 && r<=5)){
        return 4;
    }
    char name[MAX_STR+MAX_STR];
    sprintf(name,"%s, %s",al,af);
    BookType *b =(BookType*)malloc(sizeof(BookType));
    initBook(b,id,t,name,y,r);
    addBookToArray(&club->books,b);
    return 0;
}

void printTopRatedBooks(BookClubType* club){
    BookArrayType total,selected;
    int bo[club->books.size];for(int i =0 ;i<club->books.size;i++){bo[i]=0;}
    initBookArray(&selected, ORDER_BY_RATING);
    int len = (int)(club->books.size * 0.20);

    if(club->books.order == ORDER_BY_AUTHOR){
        initBookArray(&total, ORDER_BY_AUTHOR);
        for(int i_ =0;i_<len;i_++){
            int min_rating = INT_MAX;
            int min_index = -1;
            for(int i =0 ;i<club->books.size;i++){
                if(!bo[i] && min_rating  && min_rating >= club->books.elements[i]->rating){
                    min_rating = club->books.elements[i]->rating;
                    min_index = i;
                }
            }
            bo[min_index] = 1;
            addBookToArray(&selected,club->books.elements[min_index]);
        }
    }else{
        initBookArray(&total, ORDER_BY_RATING);
        for(int i =0 ;i<len;i++){
            addBookToArray(&selected,club->books.elements[i]);
        }
    }
    printf("\n-----------------------------------\n");
    printf("BookClub : %s", club->name);
    printBookArray(&selected);

}