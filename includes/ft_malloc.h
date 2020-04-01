
#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/mman.h>

# define ts             112
# define ss             1536
# define structSize     16

typedef struct          s_allocInfo allocInfo;
struct s_allocInfo
{
    void    *next;
    size_t                       size : 63;
    unsigned int                 isFree : 1;
};

typedef struct          s_pages
{
    allocInfo    *tiny;
    size_t          tSize;
    allocInfo    *small;
    allocInfo    *large;
}                       pages;

pages PAGES;
void *start;

void *malloc(size_t size);
void *tiny(size_t size);
void *small(size_t size);
void *large(size_t size);
void printAll();
void mapLength(allocInfo *map, int pages, size_t size);
allocInfo *nextZone(allocInfo *actualZone, size_t size);
allocInfo *splitFree(allocInfo *actual, size_t size);
allocInfo *concatFree(allocInfo *actual);
allocInfo *initStruct(allocInfo *zone, size_t size);
void *callMmap(allocInfo *zone, int nbPages, size_t size);

#endif
