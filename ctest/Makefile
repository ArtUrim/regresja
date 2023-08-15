EXEC = ctest

all:$(EXEC)

INCFLAGS = -I..
CFLAGS = -Wall -pedantic $(INCFLAGS) -ggdb3
CC = /usr/bin/gcc

VPATH = .:..

OBJECTS = main.o \
			 regresja.o

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXEC) $(OBJECTS)
