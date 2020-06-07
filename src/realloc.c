/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarko <jdarko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:39:17 by jdarko            #+#    #+#             */
/*   Updated: 2020/05/10 16:39:19 by jdarko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void		*realloc(void *ptr, size_t size)
{
	t_allocinfo	*zone;
	t_allocinfo	*next;
	t_allocinfo	*next_tmp;

//	t_allocinfo	*actual;

	zone = ptr - STRUCTSIZE;
	if (exists(zone))
		return (NULL);
	if (zone->size >= size + STRUCTSIZE * 2)
		zone = split_zone(zone, size);
	else
	{

		show_alloc_mem();

		next = (void *)malloc(size) - 16;

		show_alloc_mem();

		next_tmp = next->next;

		ft_memcpy(next, zone,  zone->size - 16);

		

		next->size = size;
		next->next = next_tmp;
		show_alloc_mem();
		zone->is_free = 1;
		zone = next;
	}
	return ((void*)zone + 16);
}

t_allocinfo	*split_zone(t_allocinfo *actual, size_t size)
{
	t_allocinfo	new;

	new.size = actual->size - (size + STRUCTSIZE);
	new.next = actual->next;
	new.is_free = 1;
	actual->size = size + STRUCTSIZE;
	actual->next = (void*)actual + actual->size;
	ft_memcpy(actual->next, &new, STRUCTSIZE);
	
	return (actual);
}

int			exists(t_allocinfo *map)
{
	t_allocinfo *reel;

	reel = g_pages.tiny;
	while (reel != NULL)
	{
		if (reel == map)
			return (0);
		reel = reel->next;
	}
	reel = g_pages.small;
	while (reel != NULL)
	{
		if (reel == map)
			return (0);
		reel = reel->next;
	}
	reel = g_pages.large;
	while (reel != NULL)
	{
		if (reel == map)
			return (0);
		reel = reel->next;
	}
	return (1);
}
