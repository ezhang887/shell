CC = gcc
TARGET = shell
SRC = $(wildcard src/*.c)
MAIN = main.c

.PHONY: shell run clean

$(TARGET): $(SRC)
	gcc -o $(TARGET) $(MAIN) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
