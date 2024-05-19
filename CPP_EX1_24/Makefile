# Rotem Melamed
# 209039072
# rotem.melamed25@gmail.com

CXX = g++
CXXFLAGS = -std=c++11 -Wconversion
SOURCES = Test.cpp Graph.cpp Algorithms.cpp

all : test Graph.o Algorithms.o
run : test
	./test
tidy :
	clang-format -i Test.cpp Graph.cpp Algorithms.cpp

test : $(SOURCES)
	g++ -o test $(SOURCES) $(CXXFLAGS)
valgrind : test
	valgrind valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }
Graph.o : Graph.cpp Graph.h
	g++ -c Graph.cpp
Graph.h : Graph.cpp
Algorithms.h : Algorithms.cpp
Algorithms.o : Algorithms.cpp Algorithms.h
	g++ -c Algorithms.cpp
clean :
	rm test Graph.o Algorithms.o