CC := g++
CFLAGS := -std=c++11 -Wall -O3

all: ribbon.exe ribbon2.exe

ribbon2.exe: ribbon2.cpp
	$(CC) $(CFLAGS) $^ -o $@

ribbon.exe: ribbon.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm ribbon.exe ribbon2.exe

# vim:set noexpandtab:
