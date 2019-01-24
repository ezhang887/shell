CC = gcc
CFLAGS = -g -I ./include -Wall -Werror -pedantic
TARGET = shell
SRC = $(wildcard src/*.c)
MAIN = main.c
OBJ = $(patsubst %.c, %.o, $(SRC))

.PHONY: shell run clean

%.o: %.c $(SRC) $(MAIN)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(MAIN) $(OBJ) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) 
