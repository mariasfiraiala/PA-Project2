CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm

.PHONY: build clean

build: supercomputer ferate teleportare magazin

run-p1:
	./supercomputer
run-p2:
	./ferate
run-p3:
	./teleportare
run-p4:
	./magazin

supercomputer: supercomputer.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
ferate: ferate.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
teleportare: teleportare.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
magazin: magazin.cpp
	$(CC) -o $@ $^ $(CCFLAGS)

clean:
	rm -f supercomputer ferate teleportare magazin