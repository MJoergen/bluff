#****************************************************************
PROG=bluff
CC=g++
CFLAGS=-O3 -std=c++11  -Wall
FILES=*cc
#****************************************************************

$(PROG):	*cc *h Makefile
	$(CC) $(CFLAGS) $(FILES) -o $(PROG) 
