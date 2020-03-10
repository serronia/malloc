
#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <string.h>

# define ts             112
# define ss             1536
# define structSize     16

typedef struct          s_allocInfo
{
    struct allocInfo    *next;
    size_t              size : 7;
    int                 isFree : 1;
}                       allocInfo;

typedef struct          s_pages
{
    struct allocInfo    *tiny;
    struct allocInfo    *small;
    struct allocInfo    *large;
}                       pages;

int myfunct(char *str);
