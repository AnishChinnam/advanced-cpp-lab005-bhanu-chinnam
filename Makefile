CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -Iinclude -Itests
BUILD_DIR := build
SRC_DIR := src
TEST_DIR := tests
BENCH_DIR := benchmark
APP_DIR := app

SRC := $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRC := $(TEST_DIR)/test_algorithms.cpp
BENCH_SRC := $(BENCH_DIR)/benchmark.cpp
APP_SRC := $(APP_DIR)/main.cpp

.PHONY: all test benchmark clean

all: $(BUILD_DIR)/main $(BUILD_DIR)/test_algorithms $(BUILD_DIR)/benchmark_app

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main: $(BUILD_DIR) $(SRC) $(APP_SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(APP_SRC) -o $@

$(BUILD_DIR)/benchmark_app: $(BUILD_DIR) $(SRC) $(BENCH_SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(BENCH_SRC) -o $@

$(BUILD_DIR)/test_algorithms: $(BUILD_DIR) $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST_SRC) -o $@

test: $(BUILD_DIR)/test_algorithms
	./$(BUILD_DIR)/test_algorithms

benchmark: $(BUILD_DIR)/benchmark_app
	./$(BUILD_DIR)/benchmark_app 1000 5

clean:
	rm -rf $(BUILD_DIR)
