#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "restaurant.h"
#include "display.h"

#define  CAR_WIDTH        100
#define  CAR_HEIGHT        45
#define  CAR_GAP            5


#define  ENV_WIDTH       1055
#define  ENV_HEIGHT      200


const unsigned int   TEXT_COLOR		        = 0x000000;
const unsigned int   WAIT_TO_ORDER_COLOR   = 0xFFFFFF;
const unsigned int   ORDERING_COLOR        = 0x99DD99;
const unsigned int   WAIT_TO_PICKUP_COLOR  = 0xEEAAAA;
const unsigned int   PICKING_UP_COLOR      = 0xCCCCEE;

const unsigned int   BORDER_COLOR          = 0x000000;
const unsigned int   BLANK_COLOR           = 0xFFFFFF;
const unsigned int   ORDER_WINDOW_COLOR    = 0xFFFF00;
const unsigned int   PICKUP_WINDOW_COLOR   = 0x00FFFF;
const unsigned int   ROOF_COLOR            = 0x770000;
const unsigned int   RESTAURANT_COLOR      = 0xEEEEDD;

// Display-related variables
Display *display;
Window   win;
GC       gc;


// Structure of cars being drawn
typedef struct car {
	unsigned int    customerPid;
	unsigned char   orderNumber;
	unsigned char		lineupIndex;
	short						destX;
	short						currX;
	short						currY;
	float						speed;
	unsigned int   	color;
} Car;

// Cars to draw
Car						cars[MAX_CUSTOMERS+2];
unsigned char	numCars = 0;

// This woll hold the order ... assuming maximum of 10 items ordered
char					orderString[MAX_ITEM_NAME_SIZE*10 + 20];
Order					lastOrder;

// A previous copy of the DriveThru Line
Customer   previousDriveThruLine[MAX_CUSTOMERS];

// Draw the background
void drawBackground() {
 		// Clear the window
		XSetForeground(display, gc, BLANK_COLOR);
   	XFillRectangle(display, win, gc, 0, 0, ENV_WIDTH, ENV_HEIGHT);

		// Draw the rooftop  
		XPoint   polygon[4];
  	polygon[0].x = -5;
  	polygon[0].y = 30;
  	polygon[1].x = 50;
  	polygon[1].y = 5;
  	polygon[2].x = ENV_WIDTH-55;
  	polygon[2].y = 5;
  	polygon[3].x = ENV_WIDTH+5;
  	polygon[3].y = 30;
  	XSetForeground(display, gc, ROOF_COLOR);
  	XFillPolygon(display, win, gc, polygon, 4, Convex, CoordModeOrigin);
  	
  	// Draw the restaurant
		XSetForeground(display, gc, RESTAURANT_COLOR);
   	XFillRectangle(display, win, gc, 5, 30, ENV_WIDTH-10, ENV_HEIGHT-31);
		XSetForeground(display, gc, 0x000000);
   	XDrawRectangle(display, win, gc, 5, 30, ENV_WIDTH-10, ENV_HEIGHT-31);

		// Draw the order window
		XSetForeground(display, gc, ORDER_WINDOW_COLOR);
   	XFillRectangle(display, win, gc, 440, 130, 50, 40);
		XSetForeground(display, gc, 0x000000);
   	XDrawRectangle(display, win, gc, 440, 130, 50, 40);
		XSetForeground(display, gc, TEXT_COLOR);
	  XDrawString(display, win, gc, 450, 128, "ORDER", 5);
	  
		// Draw the pickup window
		XSetForeground(display, gc, ORDER_WINDOW_COLOR);
   	XFillRectangle(display, win, gc, 965, 130, 50, 40);
		XSetForeground(display, gc, 0x000000);
   	XDrawRectangle(display, win, gc, 965, 130, 50, 40);
		XSetForeground(display, gc, TEXT_COLOR);
	  XDrawString(display, win, gc, 972, 128, "PICKUP", 6);
}

// Display the items ordered by the customer who placed the last order
void drawOrder(Restaurant *restaurant) {	 
	if (restaurant->driveThruLine[MAX_CUST_WAIT_TO_ORDER-1].order.orderNumber != NO_ORDER_YET)
		lastOrder = restaurant->driveThruLine[MAX_CUST_WAIT_TO_ORDER-1].order;
	
	if (lastOrder.orderNumber == 0)
		return;
		
	// Draw the latest order made
	sprintf(orderString, "Last Order #%d = ", lastOrder.orderNumber);
	for (int i=0; i<lastOrder.numItems; i++) {
   strcat(orderString, lastOrder.items[i].name);
   if (i != lastOrder.numItems-1)
    strcat(orderString, ", ");
  }
  strcat(orderString, "\0");
  XSetForeground(display, gc, TEXT_COLOR);
	XDrawString(display, win, gc, 50, 50, orderString, strlen(orderString));
}



// Draw a car at the given location with the given color
void drawCar(int x, int y, int fillColor, unsigned short orderNumber) {
  XPoint   polygon[4];
  char 		 textDisplay[11];	// holds onto a string for displaying

  // Draw the body
  XSetForeground(display, gc, fillColor);
  XFillRectangle(display, win, gc, x, y-30, 100, 20);
  polygon[0].x = x+20;
  polygon[0].y = y-30;
  polygon[1].x = x+30;
  polygon[1].y = y-45;
  polygon[2].x = x+55;
  polygon[2].y = y-45;
  polygon[3].x = x+70;
  polygon[3].y = y-30;
  XFillPolygon(display, win, gc, polygon, 4, Convex, CoordModeOrigin);
  
  XSetForeground(display, gc, 0x000000);
  XDrawRectangle(display, win, gc, x, y-30, 100, 20);
  polygon[0].x = x+20;
  polygon[0].y = y-30;
  polygon[1].x = x+30;
  polygon[1].y = y-45;
  polygon[2].x = x+55;
  polygon[2].y = y-45;
  polygon[3].x = x+70;
  polygon[3].y = y-30;
  XDrawLines(display, win, gc, polygon, 4, CoordModeOrigin);

  // Draw the wheels
  XSetForeground(display, gc, 0x000000); // black
  XFillArc(display, win, gc, x+10, y-20, 20, 20, 0, 360*64);
  XFillArc(display, win, gc, x+70, y-20, 20, 20, 0, 360*64);
  
  XSetForeground(display, gc, 0xFFFFFF); // white
  XFillArc(display, win, gc, x+15, y-15, 10, 10, 0, 360*64);
  XFillArc(display, win, gc, x+75, y-15, 10, 10, 0, 360*64);
  
  // Draw the order number
  if (orderNumber != NO_ORDER_YET) {
   	XSetForeground(display, gc, TEXT_COLOR);
		sprintf(&(textDisplay[0]), "%03d", orderNumber);
		XDrawString(display, win, gc, x + 42, y-15, textDisplay, strlen(textDisplay));
	}
}



// Initialize and open the simulator window with size ENV_WIDTH x ENV_HEIGHT.
void initializeWindow() {
  	// Open connection to X server
  	display = XOpenDisplay(NULL);

  	// Create a simple window, set the title and get the graphics context then
  	// make is visible and get ready to draw
  	win = XCreateSimpleWindow(display,  RootWindow(display, 0), 0, 0, ENV_WIDTH, ENV_HEIGHT, 0, 0x000000, 0xFFFFFF);
  	XStoreName(display, win, "DriveThru Simulator");
  	gc = XCreateGC(display, win, 0, NULL);
  	XMapWindow(display, win);
  	XFlush(display);
  	usleep(20000);  // sleep for 20 milliseconds.
}

// Close the display window
void closeWindow() {
  	XFreeGC(display, gc);
  	XUnmapWindow(display, win);
  	XDestroyWindow(display, win);
  	XCloseDisplay(display);
}


// Decide on how the car locations need to be updated
void updateCars(Restaurant *restaurant) {
	// First check if a new car has arrived.  If so, set up the car to start drawing from off left side of window
	if ((previousDriveThruLine[0].customerPid == 0) && (restaurant->driveThruLine[0].customerPid != 0)) {
		cars[numCars].customerPid = restaurant->driveThruLine[0].customerPid;
		cars[numCars].orderNumber = NO_ORDER_YET;
		cars[numCars].lineupIndex = 0;
		cars[numCars].currX       = 0 - CAR_WIDTH/2;
		cars[numCars].currY       = ENV_HEIGHT;
		cars[numCars].speed       = 1;
		cars[numCars].color       = WAIT_TO_ORDER_COLOR;
		numCars++; 
		
		// Set the destinationX to be as far up the line as possible
		for (int i=1; i<MAX_CUST_WAIT_TO_ORDER-1; i++) {
			if (restaurant->driveThruLine[i].customerPid == 0) {
				cars[numCars].destX = i*CAR_WIDTH + i*CAR_GAP;
			}
		}
	}

	// For each car, check if it moved forward in the lineup and if so, readjust its destination	
	for (int i=0; i<numCars; i++) {
		// Detect if the oldest car (i.e., one that is rightmost) is all done
		if (cars[0].lineupIndex == MAX_CUSTOMERS) {
			cars[0].destX = 10 * CAR_WIDTH + 10 * CAR_GAP;
			cars[0].speed = 1;
			continue;
		}
		
		// Detect if the car has moved forward
		if (restaurant->driveThruLine[cars[i].lineupIndex].customerPid != cars[i].customerPid) {
			// Find where it should be
			char foundAt = -1;
			for (int j=cars[i].lineupIndex+1; j<MAX_CUSTOMERS; j++) {
				if (restaurant->driveThruLine[j].customerPid == cars[i].customerPid) {
					foundAt = j;
					break;
				}
			}
			// We found it moved ahead, so update car i destination now
			if (foundAt > 0) {
				cars[i].destX = foundAt*CAR_WIDTH + foundAt*CAR_GAP;
				printf("Car moved to %d with destX = %d\n", cars[i].lineupIndex, cars[i].destX);
				if (cars[i].speed == 0) 
					cars[i].speed = 1; // start moving, if it was stopped
				cars[i].lineupIndex = foundAt;
				cars[i].orderNumber = restaurant->driveThruLine[foundAt].order.orderNumber;
			}
			else {
				// We didn't find the car so send it off screen
				cars[i].lineupIndex = MAX_CUSTOMERS;
			}
		}
	}
	
	//Check to see if a car has gone off screen, and if so ... then move all cars backwards one in the lineup
	if ((numCars > 0) && (cars[0].lineupIndex == MAX_CUSTOMERS) && (cars[0].currX > 10 * CAR_WIDTH + 10 * CAR_GAP - 1)) {
		// Move all car data back one.
		for (int i=0; i<numCars-1; i++) {
			cars[i] = cars[i+1];
		}
		numCars--;
	}

	// Keep previous for next time
	for (int i=0; i<MAX_CUSTOMERS; i++) 
		previousDriveThruLine[i] = restaurant->driveThruLine[i];
}


// Redraw all the cashier lineups repeatedly
void *runDisplay(void *r) {
	Restaurant *restaurant = (Restaurant *)r;
	
	initializeWindow();
	
	// Get a copy of the driveThru lineup
	for (int i=0; i<MAX_CUSTOMERS; i++)
		previousDriveThruLine[i] = restaurant->driveThruLine[i];

		
	// Now keep redrawing until someone kills the thread
 	while(1) {
 		// Draw the background
		drawBackground();
		
		// Update the car locations
		updateCars(restaurant);
		
  	// Draw the Cars
    for (int i=0; i<numCars; i++) {
    	// Set the correct car color
    	if (cars[i].lineupIndex == MAX_CUST_WAIT_TO_ORDER-1) {
    		if (cars[i].orderNumber == NO_ORDER_YET) {
    			if (cars[i].speed == 0)
    				cars[i].color = ORDERING_COLOR;
    		}
    		else
    			cars[i].color = WAIT_TO_PICKUP_COLOR;
    	}
    	else {
    		if (cars[i].lineupIndex >= MAX_CUST_WAIT_TO_ORDER) {
    			cars[i].color = WAIT_TO_PICKUP_COLOR;
    			if (cars[i].lineupIndex == MAX_CUSTOMERS-1) {
    				if (cars[i].speed == 0)
    					cars[i].color = PICKING_UP_COLOR; 
    			}
    			else if (cars[i].lineupIndex == MAX_CUSTOMERS) {
    				cars[i].color = WAIT_TO_ORDER_COLOR;
    			} 
    		}   	
    	}	
    	
    	// Draw the car now
    	drawCar(cars[i].lineupIndex*CAR_WIDTH + cars[i].lineupIndex*CAR_GAP, cars[i].currY, cars[i].color, cars[i].orderNumber);
    	
    	// Move the car forward if it has not yet reached its destination, otherwise stop it
    	if (cars[i].currX < cars[i].destX) {
    		cars[i].currX += cars[i].speed;
    		if (cars[i].currX > cars[i].destX)
    			cars[i].currX = cars[i].destX;
    	}
    	else {
    		cars[i].speed = 0;
    	}
    	
    }

    // display the latest order info
    drawOrder(restaurant);
    
  	XFlush(display);
  	usleep(2000);
  }
  
  closeWindow();
  pthread_exit(NULL);
}


