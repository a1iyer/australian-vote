CC := g++
CFLAGS := -std=c++11 -Wall -O3

all: duff.exe

%.exe: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm duff.exe

# vim:set noexpandtab:
