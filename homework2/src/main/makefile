# Имя исполняемого файла
TARGET = main
TEST_TARGET = test_executable

# Компилятор и флаги компиляции
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g --coverage
# CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -g --coverage -O0 -fsanitize=address

# Папка с исходниками
ROOT_DIR = ../
SRC_DIR = .
UNIT_DIR = $(SRC_DIR)/application/units
SHARED_DIR = $(SRC_DIR)/shared
TEST_DIR = $(ROOT_DIR)/test

# Все файлы исходного кода
SRCS = $(UNIT_DIR)/crew_member/crew_members.cpp \
       $(UNIT_DIR)/passenger/passengers.cpp \
       $(UNIT_DIR)/plane/plane.cpp \
	   $(SHARED_DIR)/enums/crew_member_type/crew_member_type.cpp \
	   $(SHARED_DIR)/enums/passenger_segment_type/passenger_segment_type.cpp

OBJS = $(SRCS:.cpp=.o)

MAIN_SRC = $(SRC_DIR)/main.cpp
MAIN_OBJS = $(MAIN_SRC:.cpp=.o)

TEST_SRCS = $(TEST_DIR)/test.cpp
# TEST_SRCS = $(TEST_DIR)/shared/enums/passenger_segment_type/passenger_segment_type_test.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

COVERAGE_GCNO = $(SRCS:.cpp=.gcno) \
	$(TEST_SRCS:.cpp=.gcno)

COVERAGE_GCDA = $(SRCS:.cpp=.gcda) \
	$(TEST_SRCS:.cpp=.gcda)

# Цель по умолчанию
all: $(TARGET)

# Правило для сборки исполняемого файла
$(TARGET): $(OBJS) $(MAIN_OBJS) 
	$(CXX) $(CXXFLAGS) -o $@ $^

# Цель для сборки тестов
$(TEST_TARGET): $(OBJS) $(TEST_OBJS) 
	$(CXX) $(CXXFLAGS) -o $@ $^

# Правило для компиляции каждого исходного файла в объектный
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Запуск тестов
test: $(TEST_TARGET)
	./$(TEST_TARGET)

coverage: $(TEST_TARGET)
	./$(TEST_TARGET)
	lcov --capture --directory . --output-file coverage.info
	lcov --remove coverage.info "/usr/include/*" --output-file coverage_filtered.info
	genhtml coverage_filtered.info --output-directory coverage_report

# Очистка сгенерированных файлов
clean:
	rm -f $(OBJS) $(MAIN_OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET) $(COVERAGE_GCNO) $(COVERAGE_GCDA) coverage.info coverage_filtered.info
	rm -rf coverage_report

# Файл .PHONY нужен, чтобы make не пытался интерпретировать clean как файл
.PHONY: all clean test coverage
