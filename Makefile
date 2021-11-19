objects = main.cpp src/*.cpp
all: build run memcheck remove

build: $(objects)
	g++ -g -O0 -Wall -Wextra -pedantic -Weffc++ -Werror $(objects) -o src/main

run: src/main
	cd src/ && ./main

memcheck: src/main
	cd src/ && valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./main

remove: src/main
	rm src/main