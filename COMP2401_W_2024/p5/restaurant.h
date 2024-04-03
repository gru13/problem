#include <semaphore.h>

//#define DEBUG	1

#define MAX_ITEMS_PER_ORDER      10 // Maximum # of items that can be ordered at once
#define	MAX_CUST_WAIT_TO_ORDER    5 // Maximum # of customers allowed to wait to order
#define	MAX_CUST_WAIT_FOR_FOOD    5 // Maximum # of customers allowed to wait to pick up food
#define	MAX_CUSTOMERS            10 // Maximum # of customers being dealt with at any time
#define	MAX_ORDERS                6 // Maximum number of orders that are being processed at any time
#define	NUM_MENU_ITEMS           11 // The # of menu items available
#define	MAX_ITEM_NAME_SIZE       15 // The maximum # of characters in a menu item name


// Commands that a Restaurant Server may get
#define   ARRIVED                 1 // Inform the restaurant that a customer has arrived
#define   PLACE_ORDER             2 // Place an order at the drivethru window
#define   SHUT_DOWN               3 // Shut down the restaurant

// Responses that a Restaurant Server may send back
#define   ACCEPTED                4 // Customer able to get in line
#define   DENIED                  5 // Customer not able to get in line

// Order-related constants
#define   NO_ORDER_YET          255 // Indicates that no order has been made yet
#define   PACK_TIME               2 // Time it takes (in seconds) to pack an item into the bag

// Settings for Restaurant Server setup
#define   SERVER_IP     "127.0.0.1"  // IP address of RestaurantServer
#define   SERVER_PORT          6000  // PORT of the RestaurantServer



// This represents an item that can be ordered
typedef struct mi {
	const char  *name;  // Name of the item ordered
	float        cost;  // Cost of the item ordered
} MenuItem;


// This represents an order that a customer makes
typedef struct ord {
	unsigned char   orderNumber;                // Unique order number for each customer
	MenuItem        items[MAX_ITEMS_PER_ORDER]; // The items ordered
	unsigned char   numItems;                   // # of items ordered
	short           secondsUntilReady;          // Time until food is ready
} Order;


// This represents a customer in line
typedef struct cust {
	unsigned int    customerPid;  // process ID of this customer
	Order           order;        // order that customer made, NULL if not made yet
	char            startedOrder; // set to true if we told the customer to start ordering
} Customer;


// This represents the shared data in the restaurant
typedef struct rest {
	Customer        driveThruLine[MAX_CUSTOMERS]; // Customers in line
	unsigned int    nextOrderNumber;              // Global customer count
	sem_t           LineupSemaphore;              // Allows us to lock up line
} Restaurant;



// External Global Variables
extern const char       *ItemNames[NUM_MENU_ITEMS];
extern const float       ItemPrices[NUM_MENU_ITEMS];
extern const float       ItemCookTime[NUM_MENU_ITEMS];
extern const float       ItemPrepTime[NUM_MENU_ITEMS];
extern const float       ItemFillTime[NUM_MENU_ITEMS];


