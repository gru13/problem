#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "restaurant.h"

#define BUFFER_LIMIT		100


// A RestaurantServer connection ... when made
int                 clientSocket;  // client socket id
struct sockaddr_in  clientAddress; // client address


// Set up a client socket and connect to the RestaurantServer.  Return -1 if there was an error.
int connectToRestaurantServer(int *sock,  struct sockaddr_in *address) {
  int status;
  
  // Create socket
  *sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (*sock < 0) {
    printf("*** CUSTOMER ERROR: Could open socket to Restaurant Server\n");
    return(-1);
  }
  // Setup address
  memset(address, 0, sizeof(struct sockaddr_in));
  address->sin_family = AF_INET;
  address->sin_addr.s_addr = inet_addr(SERVER_IP);
  address->sin_port = htons((unsigned short) SERVER_PORT);

  // Connect to server
  status = connect(*sock, (struct sockaddr *)address, sizeof(struct sockaddr_in));
  if (status < 0) {
    close(*sock);
    printf("*** CUSTOMER ERROR: Could not connect to Restaurant Server\n");
    return(-1);
  }
  return 0;
}



// Start up a Customer process. There should be a sequence of integers as command line arguments.  
// Each integer must be a number from 1 to the number of menu items at the restaurant.
void main(int argc, char *argv[]) {
	struct sockaddr_in   restaurantServerAddress; // client address for restaurant server
	int                  restaurantServerSocket;  // client socket id for restaurant server
	int                                  status;  // status from a sent message
	int					               bytesRcv;  // number of bytes received
	unsigned char buffer[MAX_ITEMS_PER_ORDER+3];  // buffer used for sending and receiving data (3 extra to allow for command and pid)
	
	char denied = 1;
	while(denied) {
		
	}

}


