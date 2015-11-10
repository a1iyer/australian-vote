CC := g++
CFLAGS := -std=c++11 -Wall -O3

all: bear.exe

%.exe: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm bear.exe

# vim:set noexpandtab:
