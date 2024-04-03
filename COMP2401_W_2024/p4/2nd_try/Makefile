CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lX11

SRC = display.c graphMaker.c graphTester.c
HDR = display.h obstacles.h

OBJ = $(SRC:.c=.o)
EXEC = graphTester

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
