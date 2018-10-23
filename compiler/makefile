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
				tree.h \
				dag.h



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
			  opti.o \
			  intepreter.o

COMPILER_AUTOFILES=lex.yy.c \
				   rule.c \
				   rule.h

.SUFFIXES:.c

all: $(COMPILER_DIST)

dag.o: dag.c
	$(CC) $(CFLAGS) -c $<

alloc.o: alloc.c
	$(CC) $(CFLAGS) -c $<

%.o:%.c
	$(CC) $(CFLAGS) -c $<

lex.yy.c:spl.l rule.c
	$(FLEX) $(FLEXFLAGS) spl.l

# $@--目标文件, $^--所有的依赖文件, $<--第一个依赖文件
rule.c:spl.y
	$(BISON) $(BISONFLAGS) -o $@ $<

$(COMPILER_DIST):$(COMPILER_OBJS)
	gcc -o $(COMPILER_DIST) $(LDFLAGS) $(COMPILER_OBJS)

clean:
	rm -f *.o
	rm -f $(COMPILER_DIST)
	rm -f $(COMPILER_AUTOFILES)

