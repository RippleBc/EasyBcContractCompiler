#include "common.h"

static List freenodes;

/* x为DAG节点或者AST节点 */
List list_append(List list, void *x)
{

    List new;

    /* new指向freenodes指向的区域，只有当调用过list_clear之后，
     freenodes才可能不为空，这样做的目的是为了节省一部分的内存空间。 */
    if ((new = freenodes) != NULL)
        /* 重新定义freenodes，指向list指针对象new的link字段，也就是NULL */
        freenodes = freenodes->link;
    else
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

/* list_clear - clear list */
void list_clear(List list)
{
    /* 记录下清空了的list */
    freenodes = list->link;
    list->link = NULL;
    list->x = NULL;
}

