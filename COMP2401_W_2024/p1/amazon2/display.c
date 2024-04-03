#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <pthread.h>

#define CITY_DIAMETER		60000		// diameter (in m) of the city

// These are display-related variables
Display *display;
Window   win;
GC       gc;

// These are location-related variables
int						 numLocations, numDrivers;
float					*xArray, *yArray;
unsigned char *zArray;

// Draw the locations on the window.
void drawLocations() {
  // First erase background
  XSetForeground(display, gc, 0xFFFFFF);
  XFillRectangle(display, win, gc, 0, 0, CITY_DIAMETER/100, CITY_DIAMETER/100);

	// Create an array of random colors ... one per driver
  unsigned long colors[numDrivers];
  for (int i=0; i<numDrivers; i++) 
  	colors[i] = rand()%25*655360 + rand()%25*2560 + rand()%256;
  
  // Draw the locationa as circles colored according to the driver
  for (int i=0; i<numLocations; i++) {
  	XSetForeground(display, gc, colors[zArray[i]]);
  	XFillArc(display, win, gc, xArray[i]-2, yArray[i]-2, 5, 5, 0, 360*64);
  	XSetForeground(display, gc, 0x000000);
  	XDrawArc(display, win, gc, xArray[i]-2, yArray[i]-2, 5, 5, 0, 360*64);
  }
  XFlush(display);
  XFlush(display);
}


// Close the window
int closeDisplayWindow() {
  // Clean up and close the window
  XFreeGC(display, gc);
  XUnmapWindow(display, win);
  XDestroyWindow(display, win);
  XCloseDisplay(display);
  exit(0);
}


// Open the window for displaying
void *openDisplayWindow(void *pointer) {
	XConfigureEvent  cEvent;
  XEvent           event;
  Window           window_returned;
  int              x, y, screenX, screenY;
  unsigned int     mask_return;
	
  // Opens connection to X server
  display = XOpenDisplay(NULL);

  // Create a simple window
  win = XCreateSimpleWindow(display,  // our connection to server
			    RootWindow(display, 0),  		// parent window (none in this example)
			    0, 0,	             					// x,y (w.r.t. parent ... ignored here)
			    CITY_DIAMETER/100,					// width
			    CITY_DIAMETER/100,	        // height
			    0, 		             					// border width
			    0x000000,                		// border color (ignored in this example)
          0xFFFFFF);               		// background color = WHITE

  // Indicate which events we want to handle
  XSelectInput(display, win, ButtonPressMask | ExposureMask);      

  // Set the name of the window
  XStoreName(display, win, "Locations Displayer");

  // Get the graphics context
  gc = XCreateGC(display, win, 0, NULL);

  // Make it visible
  XMapWindow(display, win);
  XFlush(display);
  usleep(20000);  // sleep for 20 milliseconds.
 

  // Indicate that we'd like to be able to gracefully handle window closing
  Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False); 
  XSetWMProtocols(display, win, &WM_DELETE_WINDOW, 1);
  
  // Go into infinite loop handling X11 events
  while(1) {
    XNextEvent(display, &event);
    switch(event.type) {
    case Expose:
      drawLocations();
      break;
    case ButtonPress:
      int button = event.xbutton.button;
      XQueryPointer(display, win, &window_returned,
                &window_returned, &screenX, &screenY, &x, &y,
                &mask_return);
      break;
    case ClientMessage:
    	closeDisplayWindow();
    	break;
    }
  }
}



// Where it all begins
void main() {
	char c;
	float x, y, z;
	
	
  // Spawn a thread to handle display
  pthread_t  thread_draw;
  pthread_create(&thread_draw, NULL, openDisplayWindow, NULL);
	usleep(1000000);  // Need this delay
	
	// Read in the number of drivers
	scanf("%d", &numDrivers);
	
	// Read in the number of points and create the arrays needed to store them
	scanf("%d", &numLocations);
	
	printf("NUM DRIVERS %d, PACKAGES %d\n", numDrivers, numLocations);
	xArray = (float *)malloc(sizeof(float)*numLocations);
	yArray = (float *)malloc(sizeof(float)*numLocations);
	zArray = (unsigned char *)malloc(sizeof(unsigned char)*numLocations);
	if ((xArray == NULL) || (yArray == NULL) || (zArray == NULL)) {
		printf("Display: Error Allocating memory\n");
		exit(-1);
	}

	// Read in the points and put them into the arrays
	for (int i=0; i<numLocations; i++) {
		scanf("%f", &x);
		scanf("%f", &y);
		scanf("%f", &z);
		xArray[i] = x*10 + CITY_DIAMETER/100/2;
		yArray[i] = y*10 + CITY_DIAMETER/100/2;
		zArray[i] = z;
	}
	
	// Draw the locations
	drawLocations();
	
	while(1); /// Wait for the display window to be closed
}
























