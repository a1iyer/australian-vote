CC := g++
CFLAGS := -std=c++11 -Wall -O3

all: coach.exe coach_rel.exe

%.exe: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm coach.exe

# vim:set noexpandtab:
