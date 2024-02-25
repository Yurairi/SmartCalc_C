.PHONY: all build static install uninstall rebuild dist test gcov_report clean
CC=gcc
CFLAGS= -Wall -Wextra -Werror -pedantic -std=c11
FLAGS_TEST_LIBS = -lcheck -lm -lpthread

SRC= RPN.c

NAME = Smart_calculator.a
OBJ=$(patsubst %.c, %.o, $(SRC))
OS = $(shell uname)

all: build static

build:
	@cd calculator && $(CC) $(CFLAGS) -c $(SRC)

static:
	@cd calculator && ar rc  $(NAME) $(OBJ)
	@cd calculator && ranlib $(NAME)

test: clean 
	@cd calculator && gcc $(SRC) test.c  -o test -lcheck
	@cd calculator && ./test

gcov_report: all
	@echo "┏=========================================┓"
	@echo "┃     Generating your html report ...     ┃"
	@echo "┗=========================================┛"
	@cd calculator && $(CC) $(CFLAGS) --coverage test.c $(SRC) $(NAME) $(FLAGS_TEST_LIBS) -o gcov_test
	@cd calculator && chmod +x *
	@cd calculator && ./gcov_test
	@cd calculator && lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	@cd calculator && genhtml -o report/ gcov_test.info
	@cd calculator && open ./report/index.html


install:
	@make clean
	@mkdir build
	@cd calculator && qmake && make && make clean && rm Makefile && cd ../ && mv calculator/Smart_Calculator.app build
	@cp -R build/Smart_Calculator.app ~/Desktop/Smart_Calculator.app
	@echo "┏=========================================┓"
	@echo "┃        Installed successfully.          ┃"
	@echo "┃     The project is located in the       ┃"
	@echo "┃    build folder and on the desktop.     ┃"
	@echo "┗=========================================┛"

uninstall:
	@rm -rf build*
	@echo "Uninstall completed successfully"

dvi:
	@open README.md

dist:
	@rm -rf Dist_SmartCalc/
	@mkdir Dist_SmartCalc/
	@mkdir Dist_SmartCalc/src
	@mv ./build/Smart_Calculator.app Dist_SmartCalc/src/
	@tar cvzf Dist_SmartCalc.tgz Dist_SmartCalc/
	@rm -rf Dist_SmartCalc/

clean:
	@cd calculator && rm -rf *.a && rm -rf *.o  && rm -rf *.dSYM && rm -rf *.out && rm -rf gcov_report && rm -rf report && rm -rf CPPLINT.cfg && rm -rf *.gcda 
	@cd calculator && rm -rf *.gcno && rm -rf *.info && rm -rf test && rm -rf Dist_SmartCalc && rm -rf *tgz && rm -rf build && rm -rf SC_test && rm -rf gcov_test && rm -rf .qmake.stash

rebuild: clean all
	
style_check:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@cd calculator && clang-format -style=Google -n *.c *.h *.cpp

format_style:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@cd calculator && clang-format -style=Google -i *.c *.h *.cpp
