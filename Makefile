CC = gcc
CFLAGS = -g -I ./include
TARGET = shell
SRC = $(wildcard src/*.c)
MAIN = main.c
OBJ = $(patsubst %.c, %.o, $(SRC))

.PHONY: shell run clean

%.o: $(SRC) $(MAIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(MAIN) $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
