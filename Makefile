all: test

test: test.cpp ExpressionTree.cpp
	g++ -Wall -o test test.cpp ExpressionTree.cpp -std=c++11
