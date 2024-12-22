# Using WSL
TARGET = main

CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -I /mnt/c/cpp-boost/boost_1_87_0 -I /mnt/c/cpp-boost/json/json-develop/include 

SRCDIR = ./serializer
SRC = $(SRCDIR)/main.cpp
OBJ = $(SRCDIR)/main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET).exe $(TARGET)
