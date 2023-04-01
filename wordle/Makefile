CC = clang

CFLAGS = -Wall -Wpedantic -Werror -Wextra


all: hw5

hw5: hw5.c
	$(CC) $(CFLAGS) hw5.c -o hw5

clean:
	rm -f hw5

format:
	clang-format -i -style=file *.[ch]
