//
// Created by Darko Jevtic on 2020-04-01.
//

#include "../includes/ft_malloc.h"

allocInfo *nextZone(allocInfo *actualZone, size_t size)
{
    while (actualZone->next != NULL)
    {
        actualZone = actualZone->next;
        if (actualZone->isFree == 1)
        {
            if (actualZone->size >= size + structSize * 2)
                return (splitFree(actualZone, size));
            concatFree(actualZone);
            if (actualZone->size >= size + structSize * 2)
                return (splitFree(actualZone, size));
        }
    }
    initStruct(actualZone, size); //initialisation de la nouvelle zone (je créé le next dans initstruct)
    if (size == 55 || size == 555)
    {
        actualZone = actualZone->next;
        actualZone->isFree = 1;
    }
    return (actualZone->next);
}


void mapLength(allocInfo *map, int pages, size_t size)
{
    size_t totalLength;
    totalLength = map->size;
    if (map->isFree == 1 && map->size >= size + structSize)
        return;
    while (map->next != NULL) //parcours toute la chaine
    {
        map = map->next;
        totalLength += map->size;
        if (map->isFree == 1 && map->size >= size + structSize)
        {
            return;
        }
    }
    totalLength -= (totalLength / (pages * getpagesize())) * (pages * getpagesize()); //calcule la taille du dernier mmap appelé
    if ((totalLength + size + structSize) > (pages * getpagesize())) // verifie qu'il reste de la place
    {
        map->next =(allocInfo *)callMmap(map, pages, size); // sinon mmap a la suite de la derniere zone allouée
    }
}

void printAll()
{
    allocInfo *map = PAGES.small;
    printf("pointeur actuel : %p \n", map);
//    printf("la size         : %d\n", map->size);
    printf("free            : %d\n", map->isFree);
    printf("next            : %p\n", map->next);
    while (map->next != NULL)
    {
        map = map->next;
        printf("\npointeur actuel : %p \n", map);
//        printf("la size         : %d\n", map->size);
        printf("free            : %d\n", map->isFree);
        printf("next            : %p\n", map->next);
    }
    printf("\n");
}

void *callMmap(allocInfo *zone, int nbPages, size_t size)
{
    size_t page;

    page = getpagesize() * nbPages;
    zone = mmap(NULL, page, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
    zone->isFree = 0;
    zone->size = size + structSize;
    zone->next = NULL;
    return (zone);
}

allocInfo *initStruct(allocInfo *zone, size_t size) //en cours
{
    allocInfo newZone;

    newZone.size = size + structSize;
    newZone.isFree = 0;
    newZone.next = NULL;
    zone->next = (void*)zone + zone->size;
    memcpy(zone->next, &newZone, structSize);
    return (zone);
}