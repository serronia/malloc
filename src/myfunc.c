#include "../includes/ft_malloc.h"

int myfunct(char *b)
{
    write(1, b, strlen(b));
    return(0);
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

    newZone.size = size + 16;
    newZone.isFree = 0;
    newZone.next = NULL;
    zone->next = (void*)zone + size + structSize;
    memcpy(zone->next, &newZone, structSize);
    return (zone);
}


allocInfo *initStructFree(allocInfo *zone, size_t size) //en cours
{
    allocInfo newZone;

    newZone.size = size;
    newZone.isFree = 0;
    newZone.next = NULL;
//    zone->next = (void*)zone + size;
    zone->next = (void*)zone + size + structSize;
    memcpy(zone->next, &newZone, structSize);
    return (zone);
}

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


    new.size = actual->size - (size + 16);
    new.isFree = 1;
    new.next = actual->next;
    actual->isFree = 0;
    actual->size = size + 16;
    actual->next = (void*)actual + size + structSize;

    memcpy(actual->next, &new, new.size);


    // les pointeurs
    printf("actual %p\n", actual);
//    printf("new %p\n", new);
    printf("actual next %p\n", actual->next);
//    printf("new next %p\n", new.next);

    //les size
//    printf("actual size %d\n", actual->size);
    printf("new size %d\n", new.size);
    allocInfo* tmp;
    tmp = actual->next;
    printf("actual next size %d\n", tmp->size);
    printf("actual next size %d\n", tmp->isFree);
//    tmp = new.next;
//    printf("new next size %d\n", tmp->size);

    return (actual);
}




allocInfo *oldSplitFree(allocInfo *actual, size_t size)
{
    allocInfo *next;
    allocInfo *tmp;

    next = actual->next;

    printf("size demandé %lu\n", size + 16);
    printf("actual au début %p\n", actual);
    printf("actual size au début %d\n", actual->size);
    printf("next au début %p\n", next);

    initStructFree(actual, actual->size - (size +16));

    tmp = actual->next;

    printf("actual apres inistructfree %p\n", actual);
    printf("next apres inistructfree %p\n", next);
    printf("tmp apres inistructfree %p\n", tmp);
    printf("tmp size apres inistructfree %d\n", tmp->size);
    printf("actual size apres inistructfree %d\n", actual->size);

    actual->size = size + structSize;

    printf("actual size apres calcul %d\n", actual->size);

    actual->isFree = 0;

    actual = actual->next;

    actual->isFree = 1;
    actual->next = next;

    return (actual);
}

allocInfo *nextZone(allocInfo *actualZone, size_t size)
{

    while (actualZone->next != NULL)
    {
        actualZone = actualZone->next;
        if (actualZone->isFree == 1)
        {
            if (actualZone->size >= size + structSize)
                return (splitFree(actualZone, size));
            concatFree(actualZone);
            if (actualZone->size >= size + structSize)
                return (splitFree(actualZone, size));
        }
    }
    initStruct(actualZone, size); //initialisation de la nouvelle zone (je créé le next dans initstruct)
    if (size == 55)
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
    if (map->isFree == 1 && map->size >= size + 16)
        return;
    while (map->next != NULL) //parcours toute la chaine
    {
        map = map->next;
        totalLength += map->size;
        if (map->isFree == 1 && map->size >= size + 16)
        {
            return;
        }
    }

    totalLength -= (totalLength / (pages * getpagesize())) * (pages * getpagesize()); //calcule la taille du dernier mmap appelé

    if ((totalLength + size + 16) > (pages * getpagesize())) // verifie qu'il reste de la place
    {
        map->next =(allocInfo *)callMmap(map, pages, size); // sinon mmap a la suite de la derniere zone allouée
    }
}


void printAll()
{
    allocInfo *map = PAGES.tiny;
    printf("pointeur actuel : %p \n", map);
    printf("la size         : %d\n", map->size);
    printf("free            : %d\n", map->isFree);
    printf("next            : %p\n", map->next);
    while (map->next != NULL)
    {
        map = map->next;
        printf("\npointeur actuel : %p \n", map);
        printf("la size         : %d\n", map->size);
        printf("free            : %d\n", map->isFree);
        printf("next            : %p\n", map->next);
    }
        printf("\n");
}
void *tiny(size_t size)
{
    allocInfo *zone;
    if (PAGES.tiny == NULL) //si allocInfo tiny n'a jamais été créé
    {
        PAGES.tiny = (allocInfo *)callMmap(PAGES.tiny, 3, size); //j'appelle mmap avec n pages (3 pour les tiny)
        zone = PAGES.tiny;
    }
    else
    {
        mapLength(PAGES.tiny, 3, size); //je verifie qu'il reste de la place
        zone = nextZone(PAGES.tiny, size); //je recupere une zone libre avec la bonne size
      }

//    printAll();
    return ((void*)zone + sizeof(allocInfo));
}

void *small(size_t size) // en cours
{
    printf("small\n");
    return (NULL);
}

void *large(size_t size) // en cours
{
    printf("large\n");
    return (NULL);
}

void *malloc(size_t size)
{ // on verifie la taille
    void *allocation;

    allocation = NULL;
    if (size <= 0)
        return (allocation);
    if (structSize + size <= ts)
    {
        allocation = tiny(size); //on va allouer un tiny si size + 16 <= 112
    }
    else if (structSize + size <= ss)
    {
        allocation = small(size); //on va allouer un tiny si size + 16 <= 1536
    }
    else {
        allocation = large(size); //sinon c'est un large
    }
    return (allocation);
}
//re

