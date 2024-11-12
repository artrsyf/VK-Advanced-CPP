# Имя исполняемого файла
TARGET = main

# Компилятор и флаги компиляции
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Папка с исходниками
SRC_DIR = .
UNIT_DIR = $(SRC_DIR)/application/units
SHARED_DIR = $(SRC_DIR)/shared

# Все файлы исходного кода
SRCS = $(SRC_DIR)/main.cpp \
       $(UNIT_DIR)/crew_member/crew_members.cpp \
       $(UNIT_DIR)/passenger/passengers.cpp \
       $(UNIT_DIR)/plane/plane.cpp \
	   $(SHARED_DIR)/enums/crew_member_type/crew_member_type.cpp \
	   $(SHARED_DIR)/enums/passenger_segment_type/passenger_segment_type.cpp

# Генерация списка объектных файлов из исходных
OBJS = $(SRCS:.cpp=.o)

# Цель по умолчанию
all: $(TARGET)

# Правило для сборки исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Правило для компиляции каждого исходного файла в объектный
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка сгенерированных файлов
clean:
	rm -f $(OBJS) $(TARGET)

# Файл .PHONY нужен, чтобы make не пытался интерпретировать clean как файл
.PHONY: all clean
