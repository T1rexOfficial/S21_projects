CFLAGS = -Wall -Werror -Wextra

all: s21_cat clean

s21_cat: s21_cat.o all_structures.o bget_flags.o do_flags.o
	gcc $(CFLAGS) s21_cat.o all_structures.o bget_flags.o do_flags.o -o s21_cat

s21_cat.o: s21_cat.c
	gcc $(CFLAGS) s21_cat.c -c

all_structures.o: cat_modules/all_structures.c
	gcc $(CFLAGS) cat_modules/all_structures.c -c

bget_flags.o: cat_modules/bget_flags.c
	gcc $(CFLAGS) cat_modules/bget_flags.c -c

do_flags.o: cat_modules/do_flags.c
	gcc $(CFLAGS) cat_modules/do_flags.c -c

test: s21_cat
	chmod +x test_func_cat.sh
	./test_func_cat.sh
	rm -rf *.o

leak: s21_cat
	chmod +x test_leak_cat.sh
	./test_leak_cat.sh
	rm -rf *.o

clean:
	rm -rf *.o

rebuild: all