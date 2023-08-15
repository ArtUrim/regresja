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

gt: gt.o regresja.o gtest-all.o
	g++ -o $@ $^

gt.o:gt.cpp
	g++ -c -I/usr/src/googletest/googletest/include $<

gtest-all.o:/usr/src/googletest/googletest/src/gtest-all.cc
	g++ -c -I/usr/src/googletest/googletest/include -I/usr/src/googletest/googletest $<
