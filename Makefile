CC := g++
CFLAGS := -std=c++11 -Wall

all: aus

aus: aus.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm aus

# vim:set noexpandtab:
