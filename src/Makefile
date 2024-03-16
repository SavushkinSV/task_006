CFLAGS=-Werror -Wextra -Wall 
CC=gcc
FSAN=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector

all: cafe

air_traffic: traffic.c
	$(CC) $(CFLAGS) traffic.c -o ../bin/traffic

cafe: cafe.c queue.c
	$(CC) $(CFLAGS) queue.c cafe.c  -o ../bin/cafe

clean:
	rm -rf *.o *.out

check:
	clang-format -style='{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 110}' -n *.c
	clang-format -style='{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 110}' -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	# valgrind --tool=memcheck --leak-check=yes ../bin/house