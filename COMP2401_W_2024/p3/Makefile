CC = gcc
CFLAGS = -Wall -Wextra -g

all: phoneSimulation

phoneSimulation: phoneNetwork.o phoneSimulation.o
	$(CC) $(CFLAGS) -o $@ $^

phoneNetwork.o: phoneNetwork.c phoneNetwork.h
	$(CC) $(CFLAGS) -c $<

phoneSimulation.o: phoneSimulation.c phoneNetwork.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f phoneSimulation *.o
