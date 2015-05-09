CC=g++
CFLAGS=-Wall -Wextra -Werror -Wno-long-long -Wno-variadic-macros -fexceptions -D_DEBUG -std=gnu++11 -W -O2 -static -g

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(AFLAGS)

main: main.o

clean:
	@rm -f *.o main *.pyc *.out

do-test: main
	@ruby test.rb
	@echo OK
