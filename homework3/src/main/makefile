# Using WSL
TARGET = main
TEST_TARGET = serializer_test

CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -I /mnt/c/cpp-boost/boost_1_87_0 -I /mnt/c/cpp-boost/json/json-develop/include 

SRCDIR = .
SRC = $(SRCDIR)/main.cpp
OBJ = $(SRCDIR)/main.o

TESTDIR = ../test/serializer
TEST_SRC = $(TESTDIR)/serializer_test.cpp
TEST_OBJ = $(TESTDIR)/serializer_test.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(TEST_OBJ) -o $(TEST_TARGET)

$(TEST_OBJ): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ)

test: $(TEST_TARGET)
		./$(TEST_TARGET)

lint:
	find ../ -iname "*.cpp" -o -iname "*.hpp" | xargs clang-format -i -style=file --dry-run --Werror

format:
	find ../ -iname "*.cpp" -o -iname "*.hpp" | xargs clang-format -i -style=file --Werror	

clean:
	rm -f $(OBJ) $(TARGET).exe $(TARGET) $(TEST_OBJ) $(TARGET).exe $(TEST_TARGET)

.PHONY: all clean test
