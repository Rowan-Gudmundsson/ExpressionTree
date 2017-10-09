all: test test8

test8: test8.cpp ExpressionTree.cpp
	g++ -Wall -o test8 test8.cpp ExpressionTree.cpp -std=c++98

test: test.cpp ExpressionTree.cpp
	g++ -Wall -o test test.cpp ExpressionTree.cpp -std=c++98

ExpressionTree.cpp: ExpressionTree.h
