CC = gcc
# CFLAGS = -Wall -O2
LDFLAGS = -lm

OBJS = main.o  table_hachage.o function.o	

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -rf *.o $(TARGET)

.PHONY: clean all
