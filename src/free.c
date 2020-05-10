/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarko <jdarko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:39:01 by jdarko            #+#    #+#             */
/*   Updated: 2020/05/10 16:39:02 by jdarko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/ft_malloc.h"

allocInfo *concatFree(allocInfo *actual)
{
	allocInfo *tmp;
	allocInfo *tmpNext;

	tmp = actual;
	tmpNext = actual->next;
	while (tmpNext != NULL && tmpNext->isFree == 1)
	{
			actual->size += tmpNext->size;
			tmpNext = tmpNext->next;
	}
	actual->next = tmpNext;
	return (actual);
}

allocInfo *splitFree(allocInfo *actual, size_t size)
{
	allocInfo *next;
	allocInfo new;

	new.size = actual->size - (size + structSize);
	new.isFree = 1;
	new.next = actual->next;
	actual->isFree = 0;
	actual->size = size + structSize;
	actual->next = (void*)actual + size + structSize;
	ft_memcpy(actual->next, &new, structSize);
	return (actual);
}

allocInfo *previousZone(allocInfo *map, allocInfo *actual)
{
	allocInfo *prev;

	prev = map;
	if (prev == actual)
		return 0;
	while (prev->next != NULL && prev->next != actual)
		prev = prev->next;
	return (prev);
}

void free(void *ptr)
{
	allocInfo *prev;

	if (ptr == NULL)
		return;
	allocInfo *freed = ptr - structSize;
	if (freed->size <= 4096)
		freed->isFree = 1;
	else
	{
		prev = previousZone(PAGES.large, freed);
		if (prev)
			prev->next = freed->next;
		else
			PAGES.large = freed->next;
		munmap(freed, freed->size);
	}
}
