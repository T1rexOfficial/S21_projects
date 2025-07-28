CFLAGS = -Wall -Werror -Wextra
CTESTS = backend/viewer_tests.check
CFILES = backend/viewer_back.c
BUILD_DIR = ../build
FRONT_DIR = QT3DViewer
PROJECT_NAME = 3DViewer_v1
CHECKFLAGS = $(shell pkg-config --cflags --libs check)
OS = $(shell uname)

all: install

install:
	cd $(FRONT_DIR) && cmake -S . -B ../$(BUILD_DIR) -G "Unix Makefiles" && cd ..
	make -C $(BUILD_DIR)
	cd $(BUILD_DIR) && rm -rf CMakeFiles cmake_install.cmake CMakeCache.txt Makefile 3DViewer_autogen    
	open $(BUILD_DIR)

uninstall:
	rm -rf $(BUILD_DIR)

rebuild: uninstall install

convert_test:
	checkmk clean_mode=1 $(CTESTS) > test_3DViewer.c

test: clean convert_test s21_3DViewer.a
	gcc $(CFLAGS) test_3DViewer.c s21_3DViewer.a -o s21_test $(CHECKFLAGS)
	./s21_test

gcov_report: clean convert_test s21_3DViewer.a
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage test_3DViewer.c $(CFILES) -o s21_test $(CHECKFLAGS)
	./s21_test
	rm -rf *test_3DViewer.g*
	lcov -d ./ --capture --output-file s21_test.info
	genhtml s21_test.info --output-directory s21_report
	open ./s21_report/index.html

s21_3DViewer.a:
	gcc $(CFLAGS) -c $(CFILES)
	ar -src s21_3DViewer.a *.o
	ranlib s21_3DViewer.a

format:
	cp ../materials/linters/.clang-format ./
	clang-format -i backend/*.c backend/*.h $(FRONT_DIR)/*.cpp $(FRONT_DIR)/*.h 
	rm .clang-format

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n backend/*.c backend/*.h $(FRONT_DIR)/*.cpp $(FRONT_DIR)/*.h 
	rm .clang-format

leaks: test
ifeq ($(OS),Darwin)
	leaks -atExit -- ./s21_test
else
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./s21_test
endif

dist:
	make clean
	cd ..; rm -rf $(PROJECT_NAME).tar.gz
	cd ..; mkdir $(PROJECT_NAME)
	cd ..; cp -r ./src/* $(PROJECT_NAME)
	cd ..; tar -cvf $(PROJECT_NAME).tar.gz $(PROJECT_NAME)
	cd ..; rm -rf $(PROJECT_NAME)

dvi: 
ifeq ($(OS),Darwin)
	open -a "Google Chrome" ../materials/doc/html/files.html
else
	xdg-open ../materials/doc/html/files.html
endif

clean:
	rm -rf build*
	rm -rf $(BUILD_DIR)
	rm -rf *.o *.a
	rm -rf test_3DViewer.c s21_test
	rm -rf *.gcno *.gcda *.info
	rm -rf s21_report
	rm -rf ../$(PROJECT_NAME)*