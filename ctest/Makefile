EXEC = gt

all:$(EXEC)

INCFLAGS = -I..
CFLAGS = -Wall -pedantic $(INCFLAGS) -ggdb3
CC = /usr/bin/gcc

VPATH = .:..

OBJECTS = regresja.o \
			 gt.o \
			 gtest_onecurve.o \
			 gtest_twocurves.o
  

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXEC) $(OBJECTS)


$(EXEC): $(OBJECTS)
	g++ -o $@ $^ -lgtest_main -lgtest

%.o:%.cpp
	g++ -c $<
