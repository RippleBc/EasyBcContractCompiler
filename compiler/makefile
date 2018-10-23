# Makefile for lpc compiler.
# $@：目标的名字
# $^：构造所需文件列表所有所有文件的名字
# $<：构造所需文件列表的第一个文件的名字
# $?：构造所需文件列表中更新过的文件
FLEX=flex
FLEXFLAGS=
# FLEXFLAGS=-oFILE
BISONFLAGS=-d
BISON=bison
COMPILER_DIST=splc
CC=gcc
CFLAGS=-g -Wall
LDFLAGS=-g -Wall
CVS=cvs

#这里使用awk排除了debug文件夹，读取剩下的文件夹
SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "cur_dir") print $$9}')

#目标文件所在的目录
OBJS_DIR=obj
#记住当前工程的根目录路径
ROOT_DIR=$(shell pwd)
#获取c
CUR_SOURCE=${wildcard *.c}

#将对应的c文件名转为o文件
CUR_OBJS=${patsubst %.c, $(OBJS_DIR)/%.o, $(notdir $(CUR_SOURCE))}

COMPILER_AUTOFILES=lex.yy.c \
				   rule.c \
				   rule.h

all:$(COMPILER_DIST)

$(OBJS_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<

pre:
	$(BISON) $(BISONFLAGS) -o rule.c spl.y
	$(FLEX) $(FLEXFLAGS) spl.l

$(COMPILER_DIST):$(CUR_OBJS)
	gcc -o $(COMPILER_DIST) $(LDFLAGS) $(CUR_OBJS)

clean:
	rm -f $(OBJS_DIR)/*.o
	rm -f $(COMPILER_DIST)
	rm -f $(COMPILER_AUTOFILES)

