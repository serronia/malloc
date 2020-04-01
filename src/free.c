#include "../includes/ft_malloc.h"

allocInfo *concatFree(allocInfo *actual)
{
    allocInfo *tmp;
    allocInfo *tmpNext;

    tmp = actual;
    tmpNext = actual->next;
    while (tmpNext != NULL && tmpNext->isFree == 1)
    {
            actual->size += tmpNext->size;
            tmpNext = tmpNext->next;
    }
    actual->next = tmpNext;
    return (actual);
}

allocInfo *splitFree(allocInfo *actual, size_t size)
{
    allocInfo *next;
    allocInfo new;

    new.size = actual->size - (size + structSize);
    new.isFree = 1;
    new.next = actual->next;
    actual->isFree = 0;
    actual->size = size + structSize;
    actual->next = (void*)actual + size + structSize;
    memcpy(actual->next, &new, structSize);
    return (actual);
}

