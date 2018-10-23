FLEX=flex
FLEXFLAGS=
BISONFLAGS=-d
BISON=bison
CC=gcc
CFLAGS=-g -Wall

#目标文件所在的目录
OBJS_DIR=../obj
#获取当前目录下的c文件集
CUR_SOURCE=${wildcard *.c}
#将对应的c文件名转为o文件
CUR_OBJS=${patsubst %.c, $(OBJS_DIR)/%.o, $(notdir $(CUR_SOURCE))}

COMPILER_AUTOFILES=lex.yy.c \
				   rule.c \
				   rule.h

all:$(CUR_OBJS)
	@echo $(CUR_SOURCE)
	@echo $(CUR_OBJS)

pre:
	$(BISON) $(BISONFLAGS) -o rule.c spl.y
	$(FLEX) $(FLEXFLAGS) spl.l

$(OBJS_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<
