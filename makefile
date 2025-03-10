CC = gcc
CFLAGS = -Wall

SRC = main.c jit.c bf.c
OBJ = $(SRC:.c=.o)

TARGET = bf

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
