/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarko <jdarko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:39:39 by jdarko            #+#    #+#             */
/*   Updated: 2020/05/10 16:39:40 by jdarko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_allocinfo	*next_zone(t_allocinfo *actual_zone, size_t size)
{
	if (actual_zone->is_free == 1)
	{
		concat_free(actual_zone);
		if (actual_zone->size >= size + STRUCTSIZE * 2)
			return (split_free(actual_zone, size));
	}
	while (actual_zone->next != NULL)
	{
		actual_zone = actual_zone->next;
		if (actual_zone->is_free == 1)
		{
			concat_free(actual_zone);
			if (actual_zone->size >= size + STRUCTSIZE * 2)
				return (split_free(actual_zone, size));
		}
	}
	init_struct(actual_zone, size);
	return (actual_zone->next);
}

void		map_length(t_allocinfo *map, int pages, size_t size)
{
	size_t	total_length;

	total_length = map->size;
	if (map->is_free == 1 && map->size >= size + STRUCTSIZE)
		return ;
	while (map->next != NULL)
	{
		map = map->next;
		total_length += map->size;
		if (map->is_free == 1 && map->size >= size + STRUCTSIZE)
			return ;
	}
	total_length -= (total_length / (pages * getpagesize()))
			* (pages * getpagesize());
	if ((total_length + size + STRUCTSIZE) > (pages * getpagesize()))
		map->next = (t_allocinfo *)call_mmap(map, pages, size);
}

void		*call_mmap(t_allocinfo *zone, int nb_pages, size_t size)
{
	size_t	page;

	page = getpagesize() * nb_pages;
	zone = mmap(NULL, page, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	zone->is_free = 0;
	zone->size = size + STRUCTSIZE;
	zone->next = NULL;
	return (zone);
}

t_allocinfo	*init_struct(t_allocinfo *zone, size_t size)
{
	t_allocinfo new_zone;

	new_zone.size = size + STRUCTSIZE;
	new_zone.is_free = 0;
	new_zone.next = NULL;
	zone->next = (void*)zone + zone->size;
	ft_memcpy(zone->next, &new_zone, STRUCTSIZE);
	return (zone);
}

size_t		align_number(size_t size)
{
	size_t result;
	size_t r;

	r = size % 16;
	if (r == 0)
		result = size;
	else
		result = size + (16 - r);
	return (result);
}
