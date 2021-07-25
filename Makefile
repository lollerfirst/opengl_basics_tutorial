CC=gcc
INCLUDE=./include
SRC=./src
BIN=./bin
DEPENDENCIES=-lGL -lGLEW -lSDL2 -LCGLM -lm
TARGET=main.c
OUTPUT=main
LIB=./lib
O_FILES=$(BIN)/error.o $(BIN)/texture.o $(BIN)/shader.o $(BIN)/mesh.o $(BIN)/view.o $(BIN)/vertex.o $(BIN)/transform.o $(LIB)/vector.o $(LIB)/stb_image.o

main: shader.o view.o mesh.o vertex.o texture.o error.o transform.o
	$(CC) $(TARGET) $(O_FILES) -o $(OUTPUT) -I$(INCLUDE) $(DEPENDENCIES)

debug: g-shader.o g-view.o g-mesh.o g-vertex.o g-texture.o g-error.o g-transform.o
	$(CC) $(TARGET) $(O_FILES) -o $(OUTPUT) -I$(INCLUDE) $(DEPENDENCIES) -g

shader.o: $(INCLUDE)/narg.h $(INCLUDE)/shader.h $(SRC)/shader.c
	$(CC) -c $(SRC)/shader.c -o $(BIN)/shader.o -I$(INCLUDE)
 
view.o: $(INCLUDE)/view.h $(SRC)/view.c
	$(CC) -c $(SRC)/view.c -o $(BIN)/view.o -I$(INCLUDE)

vertex.o: $(INCLUDE)/vertex.h $(SRC)/vertex.c
	$(CC) -c $(SRC)/vertex.c -o $(BIN)/vertex.o -I$(INCLUDE)

mesh.o: vertex.o $(INCLUDE)/mesh.h $(SRC)/mesh.c $(INCLUDE)/error.h
	$(CC) -c $(SRC)/mesh.c -o $(BIN)/mesh.o -I$(INCLUDE)

texture.o: $(INCLUDE)/texture.h $(SRC)/texture.c
	$(CC) -c $(SRC)/texture.c -o $(BIN)/texture.o -I$(INCLUDE)

error.o: $(INCLUDE)/error.h
	$(CC) -c $(SRC)/error.c -o$(BIN)/error.o -I$(INCLUDE)

transform.o: $(INCLUDE)/transform.h
	$(CC) -c $(SRC)/transform.c -o $(BIN)/transform.o -I$(INCLUDE)


g-shader.o: $(INCLUDE)/narg.h $(INCLUDE)/shader.h $(SRC)/shader.c
	$(CC) -c $(SRC)/shader.c -o $(BIN)/shader.o -I$(INCLUDE) -g

g-view.o: $(INCLUDE)/view.h $(SRC)/view.c
	$(CC) -c $(SRC)/view.c -o $(BIN)/view.o -I$(INCLUDE) -g

g-vertex.o: $(INCLUDE)/vertex.h $(SRC)/vertex.c
	$(CC) -c $(SRC)/vertex.c -o $(BIN)/vertex.o -I$(INCLUDE) -g

g-mesh.o: g-vertex.o $(INCLUDE)/mesh.h $(SRC)/mesh.c $(INCLUDE)/error.h
	$(CC) -c $(SRC)/mesh.c -o $(BIN)/mesh.o -I$(INCLUDE) -g

g-texture.o: $(INCLUDE)/texture.h $(SRC)/texture.c
	$(CC) -c $(SRC)/texture.c -o $(BIN)/texture.o -I$(INCLUDE) -g

g-error.o: $(INCLUDE)/error.h
	$(CC) -c $(SRC)/error.c -o$(BIN)/error.o -I$(INCLUDE) -g

g-transform.o: $(INCLUDE)/transform.h
	$(CC) -c $(SRC)/transform.c -o $(BIN)/transform.o -I$(INCLUDE) -g