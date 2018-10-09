# Makefile for lpc compiler.
#
FLEX=flex
FLEXFLAGS=
BISONFLAGS=-d
BISON=bison
COMPILER_DIST=splc
CC=gcc
CFLAGS=-g -Wall
LDFLAGS=-g -Wall
CVS=cvs

COMPILER_HEADER=common.h \
				config.h \
				symtab.h \
				x86.h \
				tree.h \
				dag.h \
				config.h

COMPILER_SOURCE= common.h \
				error.c \
				h.l \
				h.y \
				config.h \
				main.c \
				symtab.c \
				symtab.h \
				type.c \
				x86.c \
				x86.h \
				rule.c \
				lex.yy.c \
				alloc.c \
				tree.c \
				tree.h \
				list.c \
				dag.h \
				dag.c \
				ops.c \
				x86linux.c \
				opti.c

COMPILER_OBJS=error.o \
			  lex.yy.o \
			  main.o \
			  symtab.o \
			  type.o \
			  rule.o \
			  tree.o \
			  alloc.o \
			  list.o \
			  dag.o \
			  ops.o \
			  x86.o \
			  x86linux.o \
			  opti.o

COMPILER_AUTOFILES=y.tab.c \
				   lex.yy.c \
				   rule.c \
				   h.tab.h \
				   rule.h

.SUFFIXES:.c

all: $(COMPILER_DIST)

dag.o: dag.c common.h
	$(CC) $(CFLAGS) -c $<

alloc.o: alloc.c common.h
	$(CC) $(CFLAGS) -c $<

%.o:%.c $(COMPILER_HEADER)
	$(CC) $(CFLAGS) -c $<

lex.yy.c:spl.l rule.c
	$(FLEX) $(FLEXFLAGS) spl.l

rule.c:spl.y
	$(BISON) $(BISONFLAGS) -o rule.c $<

$(COMPILER_DIST):$(COMPILER_OBJS) $(COMPILER_HEADER)
	gcc -o $(COMPILER_DIST) $(LDFLAGS) $(COMPILER_OBJS)

clean:
	rm -f *.o
	rm -f $(COMPILER_DIST)
	rm -f $(COMPILER_AUTOFILES)

