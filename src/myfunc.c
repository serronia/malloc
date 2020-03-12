#include "ft_malloc.h"

int myfunct(char *b)
{
    write(1, b, strlen(b));
    return(0);
}

void *callMmap(int nbPages)
{
    void *p;
    size_t size;

    printf("entrée dans callmap\n");
    p = NULL;
    size = getpagesize() * nbPages; // la taille de l'allocation est de la taille demandée + 16 Bytes de struct

    p = mmap(p, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
    return (p);

}

allocInfo initStruct(size_t size) //en cours
{
    allocInfo actual;

    actual.size = 1;
    actual.isFree = 0;
    return (actual);
};

void *tiny(size_t size)
{
    printf("tiny\n");
    if (PAGES.tiny == NULL) //si allocInfo tiny n'a jamais été créé
    {

        printf("tiny est null\n");
        PAGES.tiny = (struct allocInfo*)callMmap(3); //j'appelle mmap avec n pages (3 pour les tiny)

        *(PAGES.tiny) = initStruct(size);
    }
    else
        {
//            PAGES.tiny = PAGE.tiny->next;
//            PAGES.tiny->size = size + structSize;
//            PAGES.tiny->next += PAGES.tiny->size;
//            PAGES.tiny->isFree = 0;
            printf("tiny n'est pas nul\n");
        }
//    PAGES.tiny->next += PAGES.tiny->size;

//    return (PAGES.tiny + structSize);
    return (NULL);
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