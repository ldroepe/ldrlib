CXX = g++
STD = c++17
CXXFLAGS = -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2
DEBUG_FLAGS = -g -O0

sets: ./sets/sets.h ./sets/tests/test_main.cpp 
	$(CXX) --std $(STD) $(CXXFLAGS) $(DEBUG_FLAGS) $^ -o sets_result
