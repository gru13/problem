#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>

#include "restaurant.h"

// Go into an infinite loop to update the driveThruLineup
void *runLineCoordination(void *r) {
	Restaurant *restaurant = (Restaurant *)r;
	
	while(1) {
		sleep(1); // a slight delay so that we don't use up a lot of CPU time
		
	}
}


