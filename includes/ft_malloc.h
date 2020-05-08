/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarko <jdarko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 18:11:12 by jdarko            #+#    #+#             */
/*   Updated: 2020/05/07 18:11:17 by jdarko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/mman.h>
# include "../Libft/includes/libft.h"


# define ts             128
# define ss             1024
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


void        *malloc(size_t size);
void        free(void *ptr);
void        *realloc(void *ptr, size_t size);
void        show_alloc_mem();
void        *tiny(size_t size);
void        *small(size_t size);
int         exists(allocInfo *map);
void        *large(size_t size);
void        print_all(allocInfo *map);
void        print_addr(void *addr);
void *calloc(size_t nbElement, size_t sizeElement);
void        mapLength(allocInfo *map, int pages, size_t size);
void        *callMmap(allocInfo *zone, int nbPages, size_t size);
size_t      align_number(size_t size);
allocInfo   *initStruct(allocInfo *zone, size_t size);
allocInfo   *nextZone(allocInfo *actualZone, size_t size);
allocInfo   *splitZone(allocInfo *actual, size_t size);
allocInfo   *splitFree(allocInfo *actual, size_t size);
allocInfo   *concatFree(allocInfo *actual);

#endif
