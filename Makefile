CC = gcc
CFLAGS = -O2 -Wall
SRC = gameoflife1.c gameoflife.c
OUT = a.out

INPUT_FILES = $(wildcard InputData/data*.in)

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: $(OUT)
	mkdir -p OutputData
	make clean_outputs
	./$(OUT) $(INPUT_FILES)

clean:
	rm -f $(OUT)

clean_outputs:
	rm -f OutputData/*.out OutputData/*.out.out
