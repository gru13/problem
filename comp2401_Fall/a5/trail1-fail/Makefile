#OBJ = main.o connect.o hero.o flyer.o hollow.o
#EXE = a5
#CC = gcc -Wall
#$(EXE):	$(OBJ)
#	$(CC) -o $(EXE) $(OBJ)
#
#hero.o: hero.c defs.h
#	$(CC) -c hero.c
#
#flyer.o: flyer.c defs.h
#	$(CC) -c flyer.c
#
#hollow.o: hollow.c defs.h
#	$(CC) -c hollow.c
#
#game.o: game.c defs.h
#	$(CC) -c game.c
#
#main.o:	main.c defs.h
#	$(CC) -c main.c
#
#connect.o:	connect.c defs.h
#	$(CC) -c connect.c
#
#clean:
#	rm -f $(EXE) $(OBJ)

OBJ = out/main.o out/connect.o out/hero.o out/flyer.o out/game.o out/hollow.o
EXE = a5
CC = gcc -Wall
OUT_DIR = out

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ)

out/hero.o: hero.c defs.h | $(OUT_DIR)
	$(CC) -c hero.c -o out/hero.o

out/flyer.o: flyer.c defs.h | $(OUT_DIR)
	$(CC) -c flyer.c -o out/flyer.o

out/game.o: game.c defs.h | $(OUT_DIR)
	$(CC) -c game.c -o out/game.o

out/main.o: main.c defs.h | $(OUT_DIR)
	$(CC) -c main.c -o out/main.o

out/connect.o: connect.c defs.h | $(OUT_DIR)
	$(CC) -c connect.c -o out/connect.o

out/hollow.o: hollow.c defs.h | $(OUT_DIR)
	$(CC) -c hollow.c -o out/hollow.o

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -f $(EXE) $(OBJ)
