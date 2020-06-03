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
	allocInfo	*zone;
	allocInfo	*actual;

	zone = ptr - structSize;
	if (exists(zone))
		return (NULL);
	if (zone->size >= size + structSize * 2)
		zone = split_zone(zone, size);
	else
	{
		actual = zone;
		zone = malloc(size);
		ft_memcpy(zone, actual, actual->size);
		actual->isFree = 1;
	}
	return ((void*)zone + (sizeof(allocInfo)));
}

allocInfo	*split_zone(allocInfo *actual, size_t size)
{
	allocInfo	new;

	new.size = actual->size - (size + structSize);
	new.next = actual->next;
	new.isFree = 1;
	actual->size = size + structSize;
	actual->next = (void*)actual + actual->size;
	ft_memcpy(actual->next, &new, structSize);
	return (actual);
}

int			exists(allocInfo *map)
{
	allocInfo *reel;

	reel = PAGES.tiny;
	while (reel != NULL)
	{
		if (reel == map)
			return (0);
		reel = reel->next;
	}
	reel = PAGES.small;
	while (reel != NULL)
	{
		if (reel == map)
			return (0);
		reel = reel->next;
	}
	reel = PAGES.large;
	while (reel != NULL)
	{
		if (reel == map)
			return (0);
		reel = reel->next;
	}
	return (1);
}
