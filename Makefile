all: compile

tests:
	g++ -std=c++17 tests.cpp -o tests
	./tests

compile:
	g++ -std=c++17 main.cpp -o edt

opt:
	g++ -std=c++17 main.cpp -O3 -o edt.opt

valgrind: compile opt
	valgrind --leak-check=full ./edt.opt
	valgrind --leak-check=full ./edt

clean:
	rm -rf edt edt.opt *.out
