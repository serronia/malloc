/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarko <jdarko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:42:50 by jdarko            #+#    #+#             */
/*   Updated: 2020/05/10 16:42:52 by jdarko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/mman.h>
# include "../Libft/includes/libft.h"

# define ts 128
# define ss	1024
# define structSize	16

typedef struct	s_allocInfo
{
	void			*next;
	size_t			size : 63;
	unsigned int	isFree : 1;
}				allocInfo;

typedef struct	s_pages
{
	allocInfo	*tiny;
	size_t		tSize;
	allocInfo	*small;
	allocInfo	*large;
}				pages;

pages		PAGES;
int			exists(allocInfo *map);
void		*malloc(size_t size);
void		free(void *ptr);
void		*realloc(void *ptr, size_t size);
void		show_alloc_mem(void);
void		*tiny(size_t size);
void		*small(size_t size);
void		*large(size_t size);
void		print_all(allocInfo *map);
void		print_addr(void *addr);
void        *calloc(size_t nbElement, size_t sizeElement);
void		map_length(allocInfo *map, int pages, size_t size);
void		*call_mmap(allocInfo *zone, int nb_pages, size_t size);
size_t		align_number(size_t size);
allocInfo	*init_struct(allocInfo *zone, size_t size);
allocInfo	*next_zone(allocInfo *actual_zone, size_t size);
allocInfo	*split_zone(allocInfo *actual, size_t size);
allocInfo	*split_free(allocInfo *actual, size_t size);
allocInfo	*concat_free(allocInfo *actual);

#endif
