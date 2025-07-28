CFLAGS = -Wall -Werror -Wextra

all: s21_grep clean

s21_grep: s21_grep.o all_structures.o bget_flags.o do_flags.o
	gcc $(CFLAGS) s21_grep.o all_structures.o bget_flags.o do_flags.o -o s21_grep

s21_grep.o: s21_grep.c
	gcc $(CFLAGS) s21_grep.c -c

all_structures.o: grep_modules/all_structures.c
	gcc $(CFLAGS) grep_modules/all_structures.c -c

bget_flags.o: grep_modules/bget_flags.c
	gcc $(CFLAGS) grep_modules/bget_flags.c -c
	
do_flags.o: grep_modules/do_flags.c
	gcc $(CFLAGS) grep_modules/do_flags.c -c

test: s21_grep
	chmod +x test_func_grep.sh
	./test_func_grep.sh
	rm -rf *.o

leak: s21_grep
	chmod +x test_leak_grep.sh
	./test_leak_grep.sh
	rm -rf *.o

clean:
	rm -rf *.o

rebuild: all
