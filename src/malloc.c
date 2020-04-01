#include "../includes/ft_malloc.h"

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
//    printf("small\n");
    allocInfo *zone;
    if (PAGES.small == NULL)
    {
        PAGES.small = (allocInfo *)callMmap(PAGES.small, 6, size);
        zone = PAGES.small;
    }
    else
    {
        mapLength(PAGES.small, 6, size);
        zone = nextZone(PAGES.small, size);
    }
//    printAll();
    return ((void*)zone + sizeof(allocInfo));
}

void *large(size_t size) // en cours
{
//    printf("large\n");
    return (NULL);
}

void *malloc(size_t size)
{
    void *allocation;

    allocation = NULL;
    if (size <= 0)
        return (allocation);
    if (structSize + size <= ts)
        allocation = tiny(size); //on va allouer un tiny si size + 16 <= 112
    else if (structSize + size <= ss)
        allocation = small(size); //on va allouer un tiny si size + 16 <= 1536
    else
        allocation = large(size); //sinon c'est un large
    return (allocation);
}