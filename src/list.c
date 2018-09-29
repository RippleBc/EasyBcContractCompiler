#include "common.h"

static List freenodes;		/* free list nodes */

/* append - append x to list, return new list */
List list_append(List list, void *x)
{
    List new;

    if ((new = freenodes) != NULL)
        freenodes = freenodes->link;
    else
        NEW(new, PERM);

    if (list->x)
    {
        ((List)(list->x))->link = new;
    }

    if (!list->link)
        list->link = new;

    list->x = new;
    new->link = NULL;
    new->x = x;

    return new;
}

/* length - # elements in list */
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
    void **array = (void **)newarray(list_length(list) + 1, sizeof array[0], arena);

    if (list)
    {
        List lp = (list)->link;
        while (lp != NULL)
        {
            array[i++] = lp->x;
            lp = lp->link;
        }
    }

    array[i] = NULL;
    return array;
}

/* list_clear - clear list */
void list_clear(List list)
{
    freenodes = list->link;
    list->link = NULL;
    list->x = NULL;
}

