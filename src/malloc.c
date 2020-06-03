/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarko <jdarko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:39:09 by jdarko            #+#    #+#             */
/*   Updated: 2020/05/10 16:39:10 by jdarko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/ft_malloc.h"

void *tiny(size_t size)
{
	allocInfo *zone;

	if (PAGES.tiny == NULL)
	{
		PAGES.tiny = (allocInfo *)callMmap(PAGES.tiny, 4, size);
		zone = PAGES.tiny;
	}
	else
	{
		mapLength(PAGES.tiny, 4, size);
		zone = nextZone(PAGES.tiny, size);
	}
	return ((void*)zone + sizeof(allocInfo));
}

void *small(size_t size)
{
	allocInfo *zone;

	if (PAGES.small == NULL)
	{
		PAGES.small = (allocInfo *)callMmap(PAGES.small, 26, size);
		zone = PAGES.small;
	}
	else
	{
		mapLength(PAGES.small, 26, size);
		zone = nextZone(PAGES.small, size);
	}
	return ((void*)zone + sizeof(allocInfo));
}

void *large(size_t size)
{
	size_t	  nbPage;
	allocInfo   *zone;
	allocInfo   *map;

	map = PAGES.large;
	nbPage = ((size + structSize) / getpagesize()) + 1;
	if (PAGES.large == NULL)
	{
		PAGES.large = (allocInfo *)callMmap(PAGES.large, nbPage, size);
		zone = PAGES.large;
	}
	else
	{
		zone = PAGES.large;
		while (zone->next != NULL)
			zone = zone->next;
		if (zone->next == NULL)
		{
			zone->next =(allocInfo *)callMmap(PAGES.large, nbPage, size);
			zone = zone->next;
		}
	}
	return ((void*)zone + sizeof(allocInfo));
}

void *malloc(size_t size)
{
	void *allocation;

	size = align_number(size);
	allocation = NULL;
	if (size <= 0)
		return (allocation);
	if (structSize + size <= ts)
		allocation = tiny(size);
	else if (structSize + size <= ss)
		allocation = small(size);
	else
		allocation = large(size);
	return (allocation);
}
