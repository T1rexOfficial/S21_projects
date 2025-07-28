CFLAGS = -Wall -Werror -Wextra
CFILES = s21_matrix.c
CHECKFLAGS = $(shell pkg-config --cflags --libs check)
#CTESTS = tests.check

all: clean s21_matrix.a

#convert_test:
#	checkmk clean_mode=1 $(CTESTS) > test_s21_matrix.c	

test: clean s21_matrix.a
	gcc $(CFLAGS) test_s21_matrix.c s21_matrix.a -o s21_test $(CHECKFLAGS)
	./s21_test

gcov_report: clean
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage test_s21_matrix.c $(CFILES) -o s21_test $(CHECKFLAGS)
	./s21_test
	rm -rf *test_s21_matrix.g*
	lcov -d ./ --capture --output-file s21_test.info
	genhtml s21_test.info --output-directory s21_report
	open ./s21_report/index.html

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -q ./s21_test

s21_matrix.a:
	gcc $(CFLAGS) -c $(CFILES)  
	ar -src s21_matrix.a s21_*.o
	ranlib s21_matrix.a

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c *.h
	rm .clang-format

my:
	gcc $(CFLAGS) -c main.c $(CFILES)
	gcc main.o s21_matrix.o -o main.exe

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf s21_test
	rm -rf main.exe
	rm -rf *.gcno *.gcda *.info
	rm -rf s21_report

rebuild: clean s21_matrix.a test
