PROJECT_NAME = s21_SmartCalc_v1
CFLAGS = -Wall -Werror -Wextra
CFILES = backend/s21_SmartCalc.c
CTESTS = backend/calctests.check
CHECKFLAGS = $(shell pkg-config --cflags --libs check)
BUILD_DIR = ../build

install:
	cd SmartCalc && cmake -S . -B ../$(BUILD_DIR) -G "Unix Makefiles" && cd ..
	make -C $(BUILD_DIR)
	cd $(BUILD_DIR) && rm -rf CMakeFiles cmake_install.cmake CMakeCache.txt Makefile s21_SmartCalc_autogen    
	open $(BUILD_DIR)	

unistall:
	rm -rf $(BUILD_DIR)

rebuild: uninstall install

convert_test:
	checkmk clean_mode=1 $(CTESTS) > test_s21_SmartCalc.c

test: clean convert_test s21_SmartCalc.a
	gcc $(CFLAGS) test_s21_SmartCalc.c s21_SmartCalc.a -o s21_test $(CHECKFLAGS)
	./s21_test

gcov_report: clean convert_test s21_SmartCalc.a
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage test_s21_SmartCalc.c $(CFILES) -o s21_test $(CHECKFLAGS)
	./s21_test
	rm -rf *test_s21_SmartCalc.g*
	lcov -d ./ --capture --output-file s21_test.info
	genhtml s21_test.info --output-directory s21_report
	open ./s21_report/index.html

s21_SmartCalc.a:
	gcc $(CFLAGS) -c $(CFILES)
	ar -src s21_SmartCalc.a *.o
	ranlib s21_SmartCalc.a

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n backend/*.c backend/*.h SmartCalc/*.cpp SmartCalc/*.h 
	rm .clang-format

dist:
	make clean
	cd ..; rm -rf $(PROJECT_NAME).tar.gz $(PROJECT_NAME)
	cd ..; mkdir $(PROJECT_NAME)
	cd ..; cp -r ./src/* $(PROJECT_NAME)
	cd ..; tar -cvf $(PROJECT_NAME).tar.gz $(PROJECT_NAME)

dvi:
	open DVI.html

clean:
	rm -rf build*
	rm -rf $(BUILD_DIR)
	rm -rf *.o
	rm -rf *.a
	rm -rf test_s21_SmartCalc.c s21_test
	rm -rf *.gcno *.gcda *.info
	rm -rf s21_report
	rm -rf ../$(PROJECT_NAME)*