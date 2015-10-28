CC := g++
CFLAGS := -std=c++11 -Wall -O3

all: longpath.exe longpath_v1.exe

%.exe: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm longpath.exe

# vim:set noexpandtab:
