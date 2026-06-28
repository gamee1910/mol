CC = cc
CFLAGS = -std=c99 -Wall
SRC = src/parsing.c src/mpc.c
TARGET = build/parsing

all:
	$(CC) $(CFLAGS) $(SRC) -ledit -lm -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
