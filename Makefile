CC := g++
CFLAGS := -std=c++11 -Wall

all: aus.exe

aus.exe: aus.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm aus.exe

# vim:set noexpandtab:
