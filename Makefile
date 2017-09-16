CXXFLAGS=-D_GNU_SOURCE
LDFLAGS=
LDLIBS=-lncurses -ltinfo

all: tictactoe

tictactoe: tictactoe.o
