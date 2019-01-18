default:
	g++ -std=c++17 main.cpp  -O3
	./a.out

tests:
	g++ -std=c++17 tests.cpp -O3
	./a.out

compile:
	g++ -std=c++17 main.cpp -O3

valgrind: compile
	valgrind --leak-check=full ./a.out
