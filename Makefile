CFLAGS = -lgraph
default: build
build: main
run: main.o
	g++ main.cpp -lgraph -o main
	./main