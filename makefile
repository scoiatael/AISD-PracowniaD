CC=g++
CFLAGS=-Wall -Wextra -Werror -Wno-long-long -Wno-variadic-macros -fexceptions -D_DEBUG -std=gnu++11 -W -O2 -static -g

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(AFLAGS)

do-test: all
	@ruby test.rb
	@echo OK

all: main test

main: main.o

test: test.o

clean:
	@rm -f *.o main *.pyc *.out
