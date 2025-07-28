CFLAGS = -Wall -Werror -Wextra
CFILES = s21_math.c 
CTESTS = test.check

all: clean test gcov_report s21_math.a

convert_test:
	checkmk clean_mode=1 ./s21_math.h $(CTESTS) > test_s21_math.c	

test: convert_test
	gcc $(CFLAGS) $(CFILES) test_s21_math.c -o s21_test `pkg-config --cflags --libs check`
	./s21_test

gcov_report: convert_test
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage $(CFILES) test_s21_math.c -o s21_test `pkg-config --cflags --libs check`
	./s21_test
	rm -rf test_s21_math.*
	lcov -d ./ --capture --output-file s21_test.info
	genhtml s21_test.info --output-directory s21_report
	open ./s21_report/index.html

s21_math.a:
	gcc $(CFLAGS) -c $(CFILES)
	ar -rc s21_math.a s21_math.o

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf test_s21_math.*
	rm -rf s21_test
	rm -rf *.gcno *.gcda *.info
	rm -rf s21_report

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c *.h
	rm .clang-format

rebuild: clean s21_string.a

