#include <stdio.h>
#include <string.h>

#include "defs.h"

int main()
{
	int choice,pid;
	char name[MAX_STR] = "GREAT";
	RestaurantType* restaurnt = (RestaurantType*)malloc(sizeof(RestaurantType));
	initRestaurant(restaurnt,name);
	printf("\n---------------------------------------------\n");
	printf("----------------RESTATURNT-------------------\n");
	printf("LOADING DATA...\n");
	loadPatronData(restaurnt);
	loadResData(restaurnt);
	do{
		printMenu(&choice);
		switch (choice)
		{
		case 0:
			cleanupRestaurant(restaurnt);
			break;
		case 1:
			printPatrons(&restaurnt->patrons);
			break;
		case 2:
			printReservations(&restaurnt->reservations);
			break;
		case 3:
			printf("Enter the Patron id : ");scanf("%d",&pid);
			printResByPatron(restaurnt,pid);
			break;
		case 4:
			printf("Enter the Patron Name : ");scanf("%s", &name);
			addPatron(&restaurnt->patrons,name);
			printf("Patron Detail :\n");
			printf("Name : %s\n", name);
			printf("Patron id : %d\n", restaurnt->patrons.nextId-1);
			break;
		case 5:
			printf("Enter the Patron id: ");scanf("%d",&pid);
			removePatron(&restaurnt->patrons,pid);
			break;
		default:
			break;
		}

	} while (choice != 0);
	return (0);
}

void printMenu(int *choice)
{
	int c = -1;
	int numOptions = 5;

	printf("\nMAIN MENU\n");
	printf("  (1) Print patrons\n");
	printf("  (2) Print reservations\n");
	printf("  (3) Print reservations by patron\n");
	printf("  (4) Add patron\n");
	printf("  (5) Remove patron\n");
	printf("  (0) Exit\n\n");

	printf("Please enter your selection: ");
	scanf("%d", &c);

	if (c == 0)
	{
		*choice = c;
		return;
	}

	while (c < 0 || c > numOptions)
	{
		printf("Please enter your selection: ");
		scanf("%d", &c);
	}

	*choice = c;
}
