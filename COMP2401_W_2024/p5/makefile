all:		restaurantServer.o orderTaker.o lineCoordinator.o timer.o display.o customer.o generator.o stop.o
	  gcc -o restaurantServer restaurantServer.o orderTaker.o timer.o display.o lineCoordinator.o -lX11 -lpthread
		gcc -o generator generator.o
		gcc -o customer customer.o
		gcc -o stop stop.o

restaurantServer.o: restaurantServer.c restaurant.h 
	gcc -c restaurantServer.c

orderTaker.o: orderTaker.c restaurant.h 
	gcc -c orderTaker.c

lineCoordinator.o: lineCoordinator.c restaurant.h 
	gcc -c lineCoordinator.c

timer.o: timer.c restaurant.h 
	gcc -c timer.c

display.o: display.c restaurant.h display.h
	gcc -c display.c

generator.o:	generator.c restaurant.h
		gcc -c generator.c

customer.o: customer.c restaurant.h
	  gcc -c customer.c

stop.o:		stop.c restaurant.h
		gcc -c stop.c

clean:
		rm -f restaurantServer.o orderTaker.o lineCoordinator.o timer.o display.o customer.o generator.o stop.o restaurantServer customer generator stop

