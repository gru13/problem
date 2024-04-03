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
