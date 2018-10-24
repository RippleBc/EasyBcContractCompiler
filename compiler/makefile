FLEX=flex
FLEXFLAGS=-o
BISON=bison
BISONFLAGS=-d -o
COMPILER_DIST=splc
CC=gcc
CFLAGS=-g -Wall
LDFLAGS=-g -Wall

#
SUB_DIRS=parser

#记住当前工程的根目录路径
ROOT_DIR=$(shell pwd)

#目标文件所在的目录
OBJS_DIR=$(ROOT_DIR)/obj

#获取c
CUR_SOURCE=${wildcard *.c} ${wildcard $(SUB_DIRS)/*.c}

#将对应的c文件名转为o文件
CUR_OBJS=${patsubst %.c, $(OBJS_DIR)/%.o, $(notdir $(CUR_SOURCE))}

#
COMPILER_AUTOFILES=parser/lex.yy.c parser/rule.c parser/rule.h

#
export OBJS_DIR

all:$(SUB_DIRS) $(COMPILER_DIST)

#递归执行子目录下的makefile文件
$(SUB_DIRS):ECHO
	make -C $@

ECHO:
	@echo $(SUBDIRS)

$(OBJS_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<

pre:
	$(BISON) $(BISONFLAGS) parser/rule.c parser/spl.y
	$(FLEX)  $(FLEXFLAGS) parser/lex.yy.c parser/spl.l

$(COMPILER_DIST):$(CUR_OBJS)
	gcc -o $(COMPILER_DIST) $(LDFLAGS) $(CUR_OBJS)

clean:
	rm -f $(OBJS_DIR)/*.o
	rm -f $(COMPILER_DIST)
	rm -f $(COMPILER_AUTOFILES)

