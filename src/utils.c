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

allocInfo *nextZone(allocInfo *actualZone, size_t size)
{
	if (actualZone->isFree == 1)
	{
		concatFree(actualZone);
		if (actualZone->size >= size + structSize * 2)
			return (splitFree(actualZone, size));
	}
	while (actualZone->next != NULL)
	{
		actualZone = actualZone->next;
		if (actualZone->isFree == 1)
		{
			concatFree(actualZone);
			if (actualZone->size >= size + structSize * 2)
				return (splitFree(actualZone, size));
		}
	}
	initStruct(actualZone, size);
	return (actualZone->next);
}


void mapLength(allocInfo *map, int pages, size_t size)
{
	size_t totalLength;
	totalLength = map->size;
	if (map->isFree == 1 && map->size >= size + structSize)
		return;
	while (map->next != NULL)
	{
		map = map->next;
		totalLength += map->size;
		if (map->isFree == 1 && map->size >= size + structSize)
			return;
	}
	totalLength -= (totalLength / (pages * getpagesize())) * (pages * getpagesize());
	if ((totalLength + size + structSize) > (pages * getpagesize()))
		map->next = (allocInfo *)callMmap(map, pages, size);
}

void *callMmap(allocInfo *zone, int nbPages, size_t size)
{
	size_t page;

	page = getpagesize() * nbPages;
	zone = mmap(NULL, page, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
	zone->isFree = 0;
	zone->size = size + structSize;
	zone->next = NULL;
	return (zone);
}

allocInfo *initStruct(allocInfo *zone, size_t size)
{
	allocInfo newZone;

	newZone.size = size + structSize;
	newZone.isFree = 0;
	newZone.next = NULL;
	zone->next = (void*)zone + zone->size;
	ft_memcpy(zone->next, &newZone, structSize);
	return (zone);
}

size_t align_number(size_t size)
{
	size_t result;
	size_t r;

	r = size % 16;
	if (r == 0)
		result = size;
	else
		result = size +(16 - r);
	return (result);
}
