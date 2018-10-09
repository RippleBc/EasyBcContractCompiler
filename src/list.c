#include "common.h"

static List freenodes;

/* 新建一个list指针对象，挂到list后面 */
List list_append(List list, void *x)
{
    /* 定义一个list的指针对象 */
    List new;

    /* new指向freenodes指向的区域，只有当调用过list_clear之后，
     freenodes才可能不为空，这样做的目的是为了节省一部分的内存空间。 */
    if ((new = freenodes) != NULL)
        /* 重新定义freenodes，指向list指针对象new的link字段，也就是NULL */
        freenodes = freenodes->link;
    else
        /* 给指针在permanent区域分配内存 */
        NEW(new, PERM);

    /* 列表的数据不为空 */
    if (list->x)
    {
        /* 列表的数据的link字段指向new */
        ((List)(list->x))->link = new;
    }

    /* 列表的link字段不存在，link字段指向new */
    if (!list->link)
        list->link = new;

    /* 列表的数据指向new */
    list->x = new;

    /* 初始化list对象的link和x字段 */
    new->link = NULL;
    new->x = x;

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

