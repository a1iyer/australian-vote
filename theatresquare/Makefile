CC := g++
CFLAGS := -std=c++11 -Wall -O3

all: theatre.exe

%.exe: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm theatre.exe

# vim:set noexpandtab:
