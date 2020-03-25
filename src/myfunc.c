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

//allocInfo concatFree(allocInfo actual)
//{
//    allocInfo next = actual;
//    while (next.next != NULL && next.next->isFree != 1)
//    {
//        next = *next.next;
//        actual.size += next.size;
//    }
//    actual.next = next.next;
//    return (actual);
//}

//size_t checkFree(allocInfo actualZone)
//{
//    int count;
//
//    count = actualZone.size;
//    while (actualZone.next != NULL && actualZone.next->isFree == 1)
//    {
//        actualZone = *actualZone.next;
//        count += actualZone.size;
//    }
//    return (count);
//}

allocInfo *nextZone(allocInfo *actualZone, size_t size)
{
    while (actualZone->next != NULL)
    {
        actualZone = actualZone->next;
//        if (actualZone->isFree == 1)
//        {
//            printf("really");
//            *actualZone = concatFree(*actualZone);
//            if (actualZone.size >= size)
//                return (*actualZone);
//        }
    }
    initStruct(actualZone, size); //initialisation de la nouvelle zone (je créé le next dans initstruct)
    return (actualZone->next);
}

void mapLength(allocInfo *map, int pages, size_t size)
{
    size_t totalLength;
    totalLength = map->size;
    while (map->next != NULL) //parcours toute la chaine
    {
        map = map->next;
        totalLength += map->size;
    }
    printf("la length totale de tiny est de %zu\n", totalLength);

    totalLength -= (totalLength / (pages * getpagesize())) * (pages * getpagesize()); //calcule la taille du dernier mmap appelé

    printf("la length de la map actuelle est de %zu\n", totalLength);
    if ((totalLength + size + 16) > (pages * getpagesize())) // verifie qu'il reste de la place
    {
        printf("faut une nouvelle page\n");
        map->next =(allocInfo *)callMmap(PAGES.tiny, 3, size); // sinon mmap a la suite de la derniere zone allouée
    }
}

void *tiny(size_t size)
{
    allocInfo *zone;
    if (PAGES.tiny == NULL) //si allocInfo tiny n'a jamais été créé
    {
        PAGES.tiny = (allocInfo *)callMmap(PAGES.tiny, 3, size); //j'appelle mmap avec n pages (3 pour les tiny)
        zone = PAGES.tiny;
        printf("tiny vaut %p\n", PAGES.tiny);
    }
    else
    {
        printf("tiny vaut %p\n", PAGES.tiny);
        mapLength(PAGES.tiny, 3, size); //je verifie qu'il reste de la place
        zone = nextZone(PAGES.tiny, size); //je recupere une zone libre avec la bonne size
      }
    printf("zone d'ecriture vaut %p\n", zone);
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