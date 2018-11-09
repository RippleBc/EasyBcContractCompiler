#include "./common.h"

struct block
{
    struct block *next; /* 指向之前分配的内存 */
};

struct header {
    struct block b;
};

/* 定义内存分配区域数量 */
struct header *arena[LASTARENA];

/* 分配内存 */
void *allocate(unsigned long n, unsigned a)
{
    /* sizeof *new = sizeof(struct header)，在64位机器中指针占用8个字节，总共占用24个字节。32位机器中指针占用4个字节，总共占用12个字节。 */
    struct header *new = malloc(sizeof *new + n);

    /* NELEMS(arena) = 5，表示总共有5个区域可以分配内存，判断内存分配区域是否符合规范 */
    assert(a < NELEMS(arena));

    /* 判断内存是否正确分配 */
    if (new == NULL)
    {
        fprintf(stderr, "insufficient memory\n");
        exit(1);
    }

    /* 分配的内存通过next指针组成一个链表，新分配的内存插入到链表的头部，arena[a]指向链表的头部 */
    new->b.next = (void *)arena[a];
    arena[a] = new;

    /* 返回新分配的内存的地址 */
    return new + 1;
}

/* 释放指定区域的内存 */
void deallocate(unsigned a)
{
    struct header *p, *q;

    assert(a < NELEMS(arena));
    
    for (p = arena[a]; p; p = q)
    {
        /* 指向下一块内存区域 */
        q = (void *)p->b.next;
        /* 释放掉当前内存区域 */
        free(p);
    }

    /* 重置内存 */
    arena[a] = NULL;
}

/* 分配数组 */
void *newarray(unsigned long m, unsigned long n, unsigned a)
{
    return allocate(m * n, a);
}

