#****************************************************************
PROG=bluff
CC=g++
CFLAGS=-O3 -std=c++11  -Wall
FILES=*cc
#****************************************************************

$(PROG):
	$(CC) $(CFLAGS) $(FILES) -o $(PROG) 