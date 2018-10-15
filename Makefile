default:
	g++ -std=c++17 main.cpp 
	./a.out

tests:
	g++ -std=c++17 tests.cpp 
	./a.out

compile:
	g++ -std=c++17 main.cpp

valgrind: compile
	valgrind --leak-check=full ./a.out
