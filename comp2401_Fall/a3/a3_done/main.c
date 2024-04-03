#include <string.h>
#include "defs.h"
#include<stdio.h>

int clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return 0;  // Return 0 to indicate success, or you can use another value to indicate an error if needed.
}

int main()
{
    int id,year,opt;
    float rating;
    char fst_name[MAX_STR],lst_name[MAX_STR],title[MAX_STR];
    BookClubType* club = (BookClubType*)malloc(sizeof(BookClubType));
    initBookClub(club,"BOOKCLUB");
    loadBookData(club);
    int choice;
    do{
        printMenu(&choice);
        switch (choice)
        {
        case 0:
            printf("\nExiting...\n");
            break;
        case 1:
            printBooks(club);
            break;
        case 2:
            printTopRatedBooks(club);
            break;
        case 3:
            printf("Enter id:");
            scanf("%d", &id);
            clearInputBuffer();
            printf("Enter Book Title:");
            scanf("%[^\n]", title);
            printf("Enter First name:");
            scanf("%s", fst_name);
            printf("Enter Last name:");
            scanf("%s", lst_name);
            printf("Enter Year:");
            scanf("%d", &year);
            printf("Enter Your Rating:");
            scanf("%f", &rating);
        //    int addBookToClub(BookClubType *club, int id, char *t, char *af,char *al, int y, float r 
            addBookToClub(club,id,title,fst_name,lst_name,year,rating);
            break;
        case 4:
            cleanupBookArray(&club->books);
            break;
        case 5:
            printf("\n-----------------------------------\n");
            printf("BOOK CLUB NAME : '%s' ",club->name);
            printf("\n-----------------------------------\n");
            break;
        case 6:
            printf("\nTotal number of books recorded : %d\n",club->books.size);
            break;
        case 7:
            printf("\n-----------------------------------\n");
            if(club->books.order == ORDER_BY_AUTHOR){
                printf("\nBook Club is Order by AUTHOR");
            }else{
                printf("\nBook Club is Order by RATING");
            }
            printf("\n-----------------------------------\n");
            break;
        case 8:
        // this part changee from the list stored from one type to another
            printf("\n-----------------------------------\n");
            printf("\nchange to ORDER_BY_AUTHOR => 1\nchange to ORDER_BY_RATING => 2\n enter the option:");
            scanf("%d", &opt);
            if(opt == 1){
                if(club->books.order == ORDER_BY_AUTHOR){
                    break;
                }
                BookArrayType new;
                initBookArray(&new,ORDER_BY_AUTHOR);
                for(int i =0;i<club->books.size;i++){
                    addBookToArray(&new,club->books.elements[i]);
                }
                club->books = new;
            }else if(opt == 2){
                if(club->books.order == ORDER_BY_RATING){
                    break;
                }
                BookArrayType new;
                initBookArray(&new,ORDER_BY_RATING);
                for(int i =0;i<club->books.size;i++){
                    addBookToArray(&new,club->books.elements[i]);
                }
                club->books = new;
            }
            break;
            printf("\n-----------------------------------\n");
        case 9:
            clearInputBuffer();
            printf("\n-----------------------------------\n");
            printf("Enter new Club Name : ");
            scanf("%[^\n]",club->name);
            printf("\n-----------------------------------\n");
            break;
        default:
            break;
        }
    }while(choice != 0);
    return(0);
}

void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 9;

  printf("\nMAIN MENU\n");
  printf("  (1) Print all books\n");
  printf("  (2) Print top rated books\n");
  printf("  (3) Add a book\n");
  printf("  (4) clear book records\n");
  printf("  (5) BOOK club name\n");
  printf("  (6) Total number of books\n");
  printf("  (7) currently order by\n");
  printf("  (8) change the order\n");
  printf("  (9) change the CLUB name :\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    scanf("%d", &c);
  }

  *choice = c;
}