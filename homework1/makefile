TARGET = main
TEST_HASHTABLE_TARGET = test_hashtable_executable
TEST_LRU_TARGET = test_lru_executable

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -g --coverage -O0 -fsanitize=address

ROOT_DIR = .
TEST_DIR = .

MAIN_SRC = $(ROOT_DIR)/main.cpp
MAIN_OBJS = $(MAIN_SRC:.cpp=.o)

TEST_HASHTABLE_SRCS = $(TEST_DIR)/test_hashtable.cpp
TEST_HASHTABLE_OBJS = $(TEST_HASHTABLE_SRCS:.cpp=.o)

TEST_LRU_SRCS = $(TEST_DIR)/test_lru.cpp
TEST_LRU_OBJS = $(TEST_LRU_SRCS:.cpp=.o)

COVERAGE_GCNO = $(SRCS:.cpp=.gcno) \
	$(TEST_HASHTABLE_SRCS:.cpp=.gcno) \
	$(TEST_LRU_SRCS:.cpp=.gcno)

COVERAGE_GCDA = $(SRCS:.cpp=.gcda) \
	$(TEST_HASHTABLE_SRCS:.cpp=.gcda) \
	$(TEST_LRU_SRCS:.cpp=.gcda)

all: $(TARGET)

$(TARGET): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_HASHTABLE_TARGET): $(TEST_HASHTABLE_OBJS) 
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_LRU_TARGET): $(TEST_LRU_OBJS) 
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test_hashtable: $(TEST_HASHTABLE_TARGET)
	./$(TEST_HASHTABLE_TARGET)

test_lru: $(TEST_LRU_TARGET)
	./$(TEST_LRU_TARGET)

test: $(TEST_HASHTABLE_TARGET) $(TEST_LRU_TARGET)
	./$(TEST_HASHTABLE_TARGET)
	./$(TEST_LRU_TARGET)

coverage: $(TEST_HASHTABLE_TARGET) $(TEST_LRU_TARGET)
	./$(TEST_HASHTABLE_TARGET)
	./$(TEST_LRU_TARGET)
	lcov --capture --directory . --output-file coverage.info
	lcov --remove coverage.info "/usr/include/*" --output-file coverage_filtered.info
	genhtml coverage_filtered.info --output-directory coverage_report

lint:
	find ../ -iname "*.cpp" -o -iname "*.hpp" | xargs clang-format -i -style=file --dry-run --Werror

format:
	find ../ -iname "*.cpp" -o -iname "*.hpp" | xargs clang-format -i -style=file --Werror	

clean:
	rm -f $(MAIN_OBJS) $(TEST_HASHTABLE_OBJS) $(TEST_LRU_OBJS) $(TARGET) $(TARGET).exe $(TEST_HASHTABLE_TARGET) $(TEST_HASHTABLE_TARGET).exe $(TEST_LRU_TARGET) $(TEST_LRU_TARGET).exe $(COVERAGE_GCNO) $(COVERAGE_GCDA) coverage.info coverage_filtered.info main.gcda main.gcno
	rm -rf coverage_report

.PHONY: all clean
