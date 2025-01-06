CC = g++
C_FLAGS = -g -std=c++17 -Wall -Wextra -Werror

TEST_LIB = unit_tests
TEST_FILE = $(TEST_LIB)/test_main.cpp
TEST_APP = $(TEST_FILE:.cpp=.app)

all : test

clean :
	rm -rf $(TEST_LIB)/*.app 

test :
	$(CC) $(C_FLAGS) $(TEST_FILE) -o $(TEST_APP) -lgtest
	./$(TEST_APP)

style :
	clang-format -i -style=Google $(shell find . -name '*.cpp') $(shell find . -name '*.h')
