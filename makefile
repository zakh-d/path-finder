default:
	g++ src/*.cpp -std=c++14 -Wall -I include -I src -o build/main
memory:
	valgrind --leak-check=yes ./build/main