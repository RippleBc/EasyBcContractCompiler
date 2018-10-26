#include "common.h"

/* x为DAG节点或者AST节点 */
List list_append(List list, void *x)
{

    List new;

    /* 给指针在permanent区域分配内存 */
    NEW(new, PERM);

    /* 节点初始化 */
    new->link = NULL;
    /* 记录AST节点或者DAG节点 */
    new->x = x;

    if (list->x)
    {
        /* 链表末尾节点指向新节点 */
        ((List)(list->x))->link = new;
    }
    if (!list->link)
        /* 指向首个放入链表的节点 */
        list->link = new;
    /* 指向新节点（链表新的末尾节点） */
    list->x = new;

    return new;
}

/* 统计链表长度 */
int list_length(List list)
{
    int n = 0;
    List lp = list->link;

    while (lp != NULL)
    {
        n++;
        lp = lp->link;
    }

    return n;
}

/* ltov - convert list to an NULL-terminated vector allocated in arena */
void **list_ltov(List list, unsigned arena)
{
    int i = 0;
    /* 在指定内存区域分配内存，至少分配一个用来存储NULL符号 */
    void **array = (void **)newarray(list_length(list) + 1, sizeof array[0], arena);

    if (list)
    {
        List lp = (list)->link;
        while (lp != NULL)
        {
            /* 初始化数组项，指向list数据所在位置 */
            array[i++] = lp->x;
            /* 指向下一个list对象 */
            lp = lp->link;
        }
    }

    /* 最后一个array项指向NULL */
    array[i] = NULL;
    return array;
}

void list_clear(List list)
{
    list->link = NULL;
    list->x = NULL;
}

