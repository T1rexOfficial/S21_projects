CFLAGS = -Wall -Werror -Wextra
CFILES = s21_string.c s21_sprintf.c
#CTESTS = $(wildcard ./tests/string_functions/*.check ./tests/special_functions/*.check ./tests/sprintf/*.check)
#EXTRA_TESTS = tests/printftests.c

all: clean test gcov_report s21_string.a

#convert_test:
#	checkmk clean_mode=1 ./s21_string.h $(CTESTS) $(EXTRA_TESTS) > test_s21_string.c	

test:
	gcc $(CFLAGS) $(CFILES) test.c -o s21_test `pkg-config --cflags --libs check`
	./s21_test

gcov_report:
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage $(CFILES) test.c -o s21_test `pkg-config --cflags --libs check`
	./s21_test
	rm -rf *test-test.*
	lcov -d ./ --capture --output-file s21_test.info
	genhtml s21_test.info --output-directory s21_report
	open ./s21_report/index.html

s21_string.a:
	gcc $(CFLAGS) -c $(CFILES)
	ar -rc s21_string.a s21_string.o s21_sprintf.o

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf test_s21_string.*
	rm -rf s21_test
	rm -rf *.gcno *.gcda *.info
	rm -rf s21_report

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c *.h
	rm .clang-format

rebuild: clean s21_string.a
