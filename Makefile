all:
	g++ -O3 -Wall -pthread --std=c++2a main.cpp primechecker.cpp -o Checker_exec
