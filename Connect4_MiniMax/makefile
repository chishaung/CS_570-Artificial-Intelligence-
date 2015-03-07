BIN  = connect4

CC=g++
SHELL=/bin/sh

CPPFLAGS= -L /usr/lib/libp/  -pg
CPPFLAGS=-O3 -Wall
CPPFLAGS=-g -Wall
CFLAGS=$(CPPFLAGS) -DCPLUSPLUS -DMallocHelp 
LIBS = -lm

SRCS=\
c4.cpp\
c4board.cpp\
rand.cpp

HDRS=\
rand.h\
c4board.h

OBJS=\
c4.o\
c4board.o\
rand.o

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(BIN)

srcs:	$(HDRS)  $(SRCS) 
	echo $(HDRS)  $(SRCS) 

all:
	touch $(HDRS)  $(SRCS) 

clean:
	/bin/rm -f *.o $(BIN)*.tar *~ core gmon.out a.out

tar: makefile $(SRCS) $(HDRS)
	tar -cvf $(BIN).tar makefile $(SRCS) $(HDRS) 
	ls -l $(BIN)*tar

commit: 
	hg commit makefile $(SRCS) $(HDRS) 

add:
	hg add makefile  $(SRCS) $(HDRS) 

status: 
	hg status makefile  $(SRCS) $(HDRS) -A | grep -v '^?'
