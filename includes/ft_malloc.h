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

# define TS 128
# define SS	1024
# define STRUCTSIZE	16

typedef struct	s_allocinfo
{
	void			*next;
	size_t			size : 63;
	unsigned int	is_free : 1;
}				t_allocinfo;

typedef struct	s_pages
{
	t_allocinfo	*tiny;
	t_allocinfo	*small;
	t_allocinfo	*large;
}				t_pages;

t_pages			g_pages;
int				exists(t_allocinfo *map);
void			*malloc(size_t size);
void			free(void *ptr);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);
void			*tiny(size_t size);
void			*small(size_t size);
void			*large(size_t size);
void			print_all(t_allocinfo *map);
void			print_addr(void *addr);
void			*calloc(size_t nb_element, size_t size_element);
int				map_length(t_allocinfo *map, int nb_pages, size_t size);
t_allocinfo		*map_length_large(t_allocinfo *map, int nb_pages, size_t size);
void			*call_mmap(t_allocinfo *zone, int nb_pages, size_t size);
size_t			align_number(size_t size);
t_allocinfo		*init_struct(t_allocinfo *zone, size_t size);
t_allocinfo		*next_zone(t_allocinfo *actual_zone, size_t size);
t_allocinfo		*split_zone(t_allocinfo *actual, size_t size);
t_allocinfo		*split_free(t_allocinfo *actual, size_t size);
t_allocinfo		*concat_free(t_allocinfo *actual);

#endif
