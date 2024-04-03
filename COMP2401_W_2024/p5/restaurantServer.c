#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>

#include "restaurant.h"

// External Functions
extern void *runTimer(void *);
extern void *runLineCoordination(void *);
extern void *runDisplay(void *);
extern void startAcceptingCustomers(Restaurant *);


// These are the menu items
const char *ItemNames[NUM_MENU_ITEMS] = {"Hamburger", "CheeseBurger", "VeggieBurger", "ChickenFingers", 
                           "SmallFries", "LargeFries", "SmallSalad", "LargeSalad", 
                           "SmallDrink", "LargeDrink", "IceCreamSundae"};
                    
// These are the prices of the menu items
const float ItemPrices[NUM_MENU_ITEMS] = {3.99, 4.99, 5.29, 6.99, 2.99, 4.19, 4.99, 7.99, 2.29, 3.79, 5.99};

// These are the preparation (e.g., cooking/preparation/filling time) for the menu items
const float ItemCookTime[NUM_MENU_ITEMS] = {120, 120, 115, 180, 90, 90, 0, 0, 0, 0, 0};
const float ItemPrepTime[NUM_MENU_ITEMS] = {10, 12, 10, 8, 8, 10, 2, 2, 2, 2, 3};
const float ItemFillTime[NUM_MENU_ITEMS] = {0, 0, 0, 0, 0, 0, 0, 0, 10, 15, 30};


// This is where it all begins
int main() {
	Restaurant	yummyFoodGuys;
	
	pthread_t  timerThread, lineCoordinatorThread, drawingThread;
	
	if (sem_init(&yummyFoodGuys.LineupSemaphore, 0, 1) < 0) {
    printf("Error: on semaphore init.\n");
    exit(1);
  }
  
	// Initialize the driveThruLine to have no customers
	for (int i=0; i<MAX_CUSTOMERS; i++) {
		yummyFoodGuys.driveThruLine[i].customerPid = 0;
		yummyFoodGuys.driveThruLine[i].startedOrder = 0;
		yummyFoodGuys.driveThruLine[i].order.orderNumber = NO_ORDER_YET;
		yummyFoodGuys.nextOrderNumber = 0;
	}

	// Spawn a thread to start the cooking timer
	pthread_create(&timerThread, NULL, runTimer, (void *)&yummyFoodGuys);
	
	// Spawn a thread to handle coordinatinr of the lineup
	pthread_create(&lineCoordinatorThread, NULL, runLineCoordination, (void *)&yummyFoodGuys);

	// Spawn a thread to handle display
	pthread_create(&drawingThread, NULL, runDisplay, (void *)&yummyFoodGuys);

	// Start handling customers (keep doing until a SHUT_DOWN)
	startAcceptingCustomers(&yummyFoodGuys);

	printf("Restaurant Closed\n");
}

