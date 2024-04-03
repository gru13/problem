#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "phoneNetwork.h"


// This the sample data for 20 customers to be used for testing
char *SampleNames[] = {"Rob Banks", "April Rain", "Rita Book", "Sue Permann", "Tim Bur", 
                       "Paddy O'Lantern", "Sam Pull", "Sandy Beach", "Adam Bomm", "Hugo First", 
                       "Dan Druff", "Mabel Syrup", "Mike Rohsopht", "Adam Sapple", "Moe Skeeto", 
                       "Anita Bath", "Rusty Chain", "Stu Pitt", "Val Crow", "Neil Down"};

char *SampleNumbers[] = {"(613)111-1111", "(819)222-2222", "(613)333-3333", "(343)444-4444", 
                         "(819)555-5555", "(613)666-6666", "(343)777-7777", "(613)888-8888", 
                         "(819)999-9999", "(613)555-1234", "(613)555-5678", "(613)666-1234", 
                         "(613)666-5678", "(343)777-1234", "(613)777-5678", "(819)888-1234", 
                         "(343)888-5678", "(613)999-1234", "(613)999-5678", "(613)444-1234"};
                         
unsigned short int SamplePlans[] = {UNLIMITED, 200, PAY_PER_MINUTE, UNLIMITED, PAY_PER_MINUTE, UNLIMITED,
                                    200, UNLIMITED, UNLIMITED, UNLIMITED, 200, UNLIMITED, UNLIMITED, 
                                    100, 200, UNLIMITED, PAY_PER_MINUTE, 200, UNLIMITED, UNLIMITED};


// This is where the fun begins
int main() {
	PhoneNetworkType	phoneNetwork;
	srand(time(NULL));

	init_phoneNetwork(&phoneNetwork);

	// Register some customers according to the sample arrays above
	// ...
	for (int i = 0; i < 20; i++){
		registerCustomer(&phoneNetwork,SampleNames[i],SampleNumbers[i],SamplePlans[i]);
	}
	displayCharges(phoneNetwork);
	// Reset the phoneNetwork calls for a new month
	// ...
	resetMonth(&phoneNetwork);	
	// Simulate 100 calls being made randomly between customers.
	// ...
	int num_of_calls = 100;
	for(int _= 0;_<num_of_calls;_++){
		int madeFrom,madeTo;
		do{
			madeFrom = rand()%(phoneNetwork.numCustomers);
			madeTo = rand()%(phoneNetwork.numCustomers);
		}while(madeFrom == madeTo);
		struct tm start;
		start.tm_mon = 2;
		start.tm_year = 2024-1900;
		start.tm_sec = 10;
		start.tm_mday = rand()%30 + 1;
		start.tm_hour = rand()%25;
		start.tm_min = rand()%61;
		start.tm_sec = rand()%61;
		time_t t = mktime(&start);
		start.tm_sec += rand()%(120*60);
		time_t d = mktime(&start);
		recordCall(&phoneNetwork,phoneNetwork.customers[madeFrom].number,phoneNetwork.customers[madeTo].number,t,d);
	}
	// Go through the recorded calls and display them
	// ...
	displayCallLog(&phoneNetwork);
	// Display the monthly charges for all customers
	// ...
	displayCharges_Modified(phoneNetwork);
}
